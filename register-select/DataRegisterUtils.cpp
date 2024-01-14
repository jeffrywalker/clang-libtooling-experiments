#include "DataRegisterUtils.h"

#include "clang/AST/CommentVisitor.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/RawCommentList.h"
#include "clang/AST/RecursiveASTVisitor.h"

#include "Logger.h"

using namespace data_registration;
using namespace clang;

void data_registration::readComments(clang::comments::Comment* comment, ASTContext& context,
                                     data_registration::RegisteredVariable& varInfo, bool isParagraphComment /*= false*/)
{
    // DEBUG comment->dumpColor();

    bool isInlineCommandCmt = false;
    for (comments::Comment::child_iterator I = comment->child_begin(), E = comment->child_end(); I != E; ++I)
    {
        if (comments::InlineCommandComment* IC = dyn_cast<comments::InlineCommandComment>(*I))
        {
            isInlineCommandCmt = true;
            std::string cmd    = context.getCommentCommandTraits().getCommandInfo(IC->getCommandID())->Name;
            std::string value;
            // obtain the value
            comments::Comment::child_iterator _I = I;
            ++_I;
            if (comments::TextComment* TC = dyn_cast<comments::TextComment>(*_I))
            {
                value = TC->getText().str();
            }
            varInfo.processKeyword(cmd, value);
        }
        if (comments::BlockCommandComment* BC = dyn_cast<comments::BlockCommandComment>(*I))
        {
            std::string blockCmd = context.getCommentCommandTraits().getCommandInfo(BC->getCommandID())->Name;
            readComments(BC, context, varInfo);
        }
        if (comments::ParagraphComment* PC = dyn_cast<comments::ParagraphComment>(*I))
        {
            readComments(PC, context, varInfo, true);
        }
        if (!isInlineCommandCmt && isParagraphComment)
        {
            /// NOTE: this condition expects the description to appear first
            /// one would need to check the line number to allow it after a "\units ft" entry
            if (comments::TextComment* TC = dyn_cast<comments::TextComment>(*I))
            {
                varInfo.setDescriptionFromText(TC->getText().str());
            }
        }
    }
}

/// TODO needs to be part of class for the recursive handling
/// TODO need to support derived classes
/// TODO need "binder" equivalent class that checks for ability to register. For example, protected/private base classes.
void data_registration::_migrate_registerFieldDecl(const std::string& listName, const clang::FieldDecl* fd,
                                                   const data_registration::RegisteredVariable* parent /*= nullptr*/)
{
    const clang::RecordDecl* rd         = fd->getParent();
    const clang::QualType qt            = fd->getType();
    const clang::Type* t                = qt.getTypePtr();
    const clang::RecordDecl* typeRecord = t->getAsRecordDecl();
    bool isBuiltIn                      = t->isBuiltinType();
    bool isClassOrStruct                = t->isStructureType() || t->isClassType();  /// NOTE: probably better than 'isCompoundType'
    bool isCompoundType                 = !t->isBuiltinType() && !t->isEnumeralType();

    ASTContext& context = fd->getASTContext();
    // register entry for this field
    data_registration::RegisteredVariable regVar;
    regVar.listName = listName;
    regVar.setName(fd->getName().str());
    if (parent != nullptr)
    {
        regVar.setParent(parent);
    }

    if (isBuiltIn)
    {
        if (const clang::BuiltinType* bit = t->getAs<clang::BuiltinType>())
        {
            clang::PrintingPolicy pp(context.getLangOpts());
            regVar.typeName = bit->getName(pp).str();
        }
    }
    else if (t->isEnumeralType())
    {
        if (const clang::EnumType* et = t->getAs<clang::EnumType>())
        {
            regVar.enumName = et->getAsTagDecl()->getNameAsString();
            // add enumerated values as convention to demonstrate reading enum
            std::string enumConvention      = "";
            const clang::EnumDecl* enumDecl = et->getDecl();
            for (auto it = enumDecl->enumerator_begin(); it != enumDecl->enumerator_end(); it++)
            {
                enumConvention += it->getNameAsString() + "(" + std::to_string(it->getInitVal().getSExtValue()) + ") ";
            }
            regVar.convention = enumConvention;
        }
    }
    else
    {
        regVar.typeName = typeRecord->getNameAsString();
    }

    if (auto comment = context.getLocalCommentForDeclUncached(fd))
    {
        readComments(comment, context, regVar);
    }
    if (regVar.units == data_registration::INHERIT_UNIT && parent != nullptr)
    {
        regVar.units = parent->units;
    }

    if (isCompoundType)
    {
        regVar.dump();

        // check for base classes
        const clang::CXXRecordDecl* tcxx = t->getAsCXXRecordDecl();
        if (tcxx->getNumBases() > 0)
        {
            for (const auto itr : tcxx->bases())
            {
                const clang::RecordDecl* baseType = itr.getType().getTypePtr()->getAsRecordDecl();
                std::string baseName              = baseType->getNameAsString();
                std::stringstream ss;
                ss << "base: " << baseName;
                bool canRegisterBase = false;
                if (itr.getAccessSpecifierAsWritten() == clang::AccessSpecifier::AS_public)
                {
                    ss << " is public\n";
                    canRegisterBase = true;
                }
                else if (itr.getAccessSpecifierAsWritten() == clang::AccessSpecifier::AS_protected)
                {
                    ss << " is protected\n";
                    canRegisterBase = true;
                }
                else if (itr.getAccessSpecifierAsWritten() == clang::AccessSpecifier::AS_private)
                {
                    ss << " is private\n";
                    /// TODO would require check for public/protected register method
                }
                Logger::get().debug(ss.str());
                if (canRegisterBase)
                {
                    for (const auto* childField : baseType->fields())
                    {
                        _migrate_registerFieldDecl(listName, childField, &regVar);
                    }
                }
            }
        }

        // traverse the children
        for (const auto* childField : typeRecord->fields())
        {
            _migrate_registerFieldDecl(listName, childField, &regVar);
        }
    }
    else
    {
        regVar.isBasicType = true;
        regVar.dump();
    }
}