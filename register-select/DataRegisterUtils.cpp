#include <cassert>

#include "DataRegisterUtils.h"

#include "clang/AST/ASTContext.h"
#include "clang/AST/Comment.h"
#include "clang/AST/CommentVisitor.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/RawCommentList.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/Type.h"

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


std::vector<uint64_t> data_registration::getConstantArrayExtents(const clang::ConstantArrayType* CAT)
{
    assert(CAT && "ConstantArrayType should not be null");
    CAT = cast<ConstantArrayType>(CAT->getCanonicalTypeInternal());
    std::vector<uint64_t> Extents;
    do
    {
        Extents.push_back(CAT->getSize().getZExtValue());
    } while ((CAT = dyn_cast<ConstantArrayType>(CAT->getElementType())));
    return Extents;
}

const clang::QualType data_registration::getConstArrayQualType(const clang::ConstantArrayType* CAT)
{
    assert(CAT && "ConstantArrayType should not be null");
    CAT                = cast<ConstantArrayType>(CAT->getCanonicalTypeInternal());
    clang::QualType qt = CAT->getElementType();
    do
    {
        clang::QualType qt = CAT->getElementType();
    } while ((CAT = dyn_cast<ConstantArrayType>(CAT->getElementType())));

    return qt;
}

const clang::Type* data_registration::getConstArrayType(const clang::ConstantArrayType* CAT)
{
    assert(CAT && "ConstantArrayType should not be null");
    const clang::Type* CT;
    CAT = cast<ConstantArrayType>(CAT->getCanonicalTypeInternal());
    CT  = dyn_cast<clang::Type>(CAT->getElementType());
    do
    {
        CT = dyn_cast<clang::Type>(CAT->getElementType());
    } while ((CAT = dyn_cast<ConstantArrayType>(CAT->getElementType())));

    return CT;
}

std::vector<uint64_t> data_registration::sub2ind(uint64_t index, std::vector<uint64_t> dimensions)
{
    uint64_t numElem = 1;
    for (const auto& i : dimensions)
    {
        numElem *= i;
    }
    assert(index <= numElem && "attempted to index out of range");

    std::vector<uint64_t> v;
    // 1D
    if (dimensions.size() == 1)
    {
        v.push_back(index);
        return v;
    }
    // create the output for n-d
    for (int i = 0; i < dimensions.size(); i++)
    {
        v.push_back(0);
    }

    uint64_t vi, vk;
    if (dimensions.size() > 2)
    {
        // cumulative product
        std::vector<uint64_t> k;
        k.push_back(dimensions[0]);
        for (int i = 1; i < dimensions.size(); i++)
        {
            k.push_back(k[i - 1] * dimensions[i]);
        }
        for (int i = (dimensions.size() - 1); i > 1; i--)
        {
            vi    = index % k[i - 1];
            vk    = (index - vi) / k[i - 1];
            v[i]  = vk;
            index = vi;
        }
    }

    vi   = index % dimensions[0];
    v[1] = (index - vi) / dimensions[0];
    v[0] = vi;
    return v;
}

std::string data_registration::getArrayAccess(const std::vector<uint64_t>& v)
{
    std::string s = "";
    for (const auto& i : v)
    {
        s += "[" + std::to_string(i) + "]";
    }
    return s;
}