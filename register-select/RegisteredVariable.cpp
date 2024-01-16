#include "RegisteredVariable.h"
#include "DataRegisterUtils.h"
#include "Logger.h"
#include "str_utils.h"
#include <format>
#include <iostream>
#include <sstream>
#include <string_view>

#include "clang/AST/ASTContext.h"
#include "clang/AST/Comment.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/RecursiveASTVisitor.h"

using namespace data_registration;
using namespace str_utils;

void RegisteredVariable::processKeyword(const std::string& keyword, const std::string& value)
{
    if (keyword == UNITS_KEYWORD)
    {
        units = trim(value);
    }
    if (keyword == RANGE_KEYWORD)
    {
        range = trim(value);
    }
    if (keyword == CONVENTION_KEYWORD)
    {
        convention = trim(value);
    }
    if (keyword == DESCRIPTION_KEYWORD)
    {
        description = trim(value);
    }
}

void RegisteredVariable::setDescriptionFromText(const std::string& text)
{
    if (description != "")
    {
        return;
    }
    /// FIXME this doesn't capture tabs
    if (text.find_first_not_of(WHITESPACE) != std::string::npos)
    {
        description = trim(text);
    }
}

void RegisteredVariable::setName(const std::string& name)
{
    m_name         = name;
    m_fullQualName = name;

    m_listName = std::format("{}.{}", listName, getFilteredName());
}

std::string RegisteredVariable::getFilteredName()
{
    std::string _name = m_name;
    if (_name.starts_with("m_"))
    {
        _name = _name.substr(2);
    }
    return _name;
}

void RegisteredVariable::setParent(const RegisteredVariable* parent)
{
    /// FIXME assumes no pointers or methods
    m_fullQualName = parent->getFullName() + "." + m_fullQualName;
    m_listName     = parent->getListVarName() + "." + getFilteredName();
}

const std::string& RegisteredVariable::getName() const
{
    return m_name;
}

std::string RegisteredVariable::getListVarName(const std::string& arrayAccess) const
{
    return m_listName + arrayAccess + m_activeArrayAccess;
}

std::string RegisteredVariable::getFullName(const std::string& arrayAccess) const
{
    return m_fullQualName + arrayAccess + m_activeArrayAccess;
}

std::string RegisteredVariable::getAddRefCode() const
{
    std::stringstream ss;
    ss << tab() << "pvl->addReference(L\"" << getListVarName() << "\",\n"
       << tab(2) << "/*array*/ L\"" << getArrayDesignation() << "\",\n"
       << tab(2) << "/*description*/ L\"" << description << "\",\n"
       << tab(2) << "/*units*/ L\"" << units << "\",\n"
       << tab(2) << "/*convention*/ L\"" << convention << "\",\n"
       << tab(2) << "/*default*/ L\"" << defaultValue << "\",\n"
       << tab(2) << "/*range*/ L\"" << range << "\",\n"
       << tab(2) << "/*structName*/ L\"" << typeName << "\");\n";
    return ss.str();
}

std::string RegisteredVariable::getAddVarCode(const std::string& arrayAccess) const
{
    std::stringstream ss;
    ss << tab() << "pvl->addVar(L\"" << getListVarName(arrayAccess) << "\",\n"
       << tab(2) << "/*description*/ L\"" << description << "\",\n"
       << tab(2) << "/*units*/ L\"" << units << "\",\n"
       << tab(2) << "/*convention*/ L\"" << convention << "\",\n"
       << tab(2) << "/*default*/ L\"" << defaultValue << "\",\n"
       << tab(2) << "/*range*/ L\"" << range << "\",\n"
       << tab(2) << "/*varType*/ " << getVarTypeEnumString() << ",\n"
       << tab(2) << "/*address*/ " << getAddressAccess(arrayAccess);
    if (isEnum)
    {
        ss << ",\n" << tab(2) << "/*enum*/ L\"" << enumName << "\"";
    }
    ss << ");\n";
    return ss.str();
}

std::string RegisteredVariable::getRegistrationCode() const
{
    if (isArray && (isBuiltIn || isEnum))
    {
        std::string s = "";
        // traverse elements of array
        for (uint64_t i = 0; i < getNumArrayElements(); i++)
        {
            s += getAddVarCode(getArrayAccessFromLinearIndex(i));
        }
        s += getAddRefCode();
        return s;
    }
    if (isBuiltIn || isEnum)
    {
        return getAddVarCode();
    }
    if (isClass || isStruct)
    {
        return getAddRefCode();
    }
    return "// ERROR\n";
}

void RegisteredVariable::dump()
{
    std::cout << getRegistrationCode();
}

bool RegisteredVariable::inheritsUnits()
{
    return units == INHERIT_UNIT;
}

bool RegisteredVariable::update(const clang::FieldDecl* fd, const std::string& list_name,
                                const RegisteredVariable* parent /*=nullptr*/)
{
    if (fd == nullptr)
    {
        return false;
    }
    listName = list_name;  // must be set first
    // get type information
    const clang::QualType qt   = fd->getType();
    const clang::Type* t       = qt.getTypePtr();
    clang::ASTContext& context = fd->getASTContext();  // for comments

    setName(fd->getName().str());
    updateTypeInfo(context, t, &qt);
    // isClass   = t->isClassType();
    // isStruct  = t->isStructureType();
    // isEnum    = t->isEnumeralType();
    // isBuiltIn = t->isBuiltinType();
    // isArray   = t->isConstantArrayType();  // cannot register dynamic
    // isPointer = t->isPointerType();

    //    if (isBuiltIn)
    //    {
    //        typeName = getBuiltInTypeStr(t, context);
    //    }
    //    else if (isEnum)
    //    {
    //        if (const clang::EnumType* et = t->getAs<clang::EnumType>())
    //        {
    //            std::string enumConvention = "";
    //            enumName                   = et->getAsTagDecl()->getNameAsString();
    //            // add enumerated values as convention for clarity over all interfaces
    //            const clang::EnumDecl* enumDecl = et->getDecl();
    //            for (auto it = enumDecl->enumerator_begin(); it != enumDecl->enumerator_end(); it++)
    //            {
    //                enumEntries.push_back(std::make_pair(it->getNameAsString(), it->getInitVal().getSExtValue()));
    //                enumConvention += it->getNameAsString() + "(" + std::to_string(it->getInitVal().getSExtValue()) + ") ";
    //            }
    //            convention = enumConvention;
    //        }
    //    }
    //    else if (isArray)
    //    {
    //        Logger::get().debug(m_name + " IS CONST ARRY");
    //        if (const auto* CAT = context.getAsConstantArrayType(qt))
    //        {
    //            // const auto* ET      = dyn_cast<clang::Type>(CAT->getElementType());
    //            const auto* ET      = getConstArrayType(CAT);
    //            std::string typeStr = "UNK";

    //            if (ET->isBuiltinType())
    //            {
    //                typeName  = getBuiltInTypeStr(ET, context);
    //                isBuiltIn = true;
    //            }
    //            else if (ET->isEnumeralType())
    //            {
    //                if (const clang::EnumType* et = t->getAs<clang::EnumType>())
    //                {
    //                    enumName = et->getAsTagDecl()->getNameAsString();
    //                }
    //            }
    //            else
    //            {
    //                typeName = ET->getAsRecordDecl()->getNameAsString();
    //            }

    //            dimensions = getConstantArrayExtents(CAT);
    //            std::string szstr;
    //            for (const auto& i : dimensions)
    //            {
    //                szstr += "[" + std::to_string(i) + "]";
    //            }
    //            Logger::get().debug("ARRAY: " + m_name + " TYPE: " + typeName + " SIZE: " + szstr);
    //        }
    //    }
    //    else
    //    {
    //        typeName = typeRecord->getNameAsString();
    //    }

    if (isPointer)
    {
        Logger::get().debug(m_name + " IS POINTER");
    }
    // note the structName and className are superfluous but exist to promote code readability
    if (isStruct)
    {
        structName = typeName;
    }
    if (isClass)
    {
        className = typeName;
    }

    // populates content from the comments
    if (auto comment = context.getLocalCommentForDeclUncached(fd))
    {
        readComments(comment, context, *this);
    }

    // apply parent after processing the basic entries
    if (parent != nullptr)
    {
        setParent(parent);
        if (inheritsUnits())
        {
            units = parent->units;
        }
    }

    return true;
}

std::string RegisteredVariable::getEnumRegistrationCode() const
{
    if (!isEnum)
    {
        return "";
    }

    std::stringstream ss;
    ss << "{\n"  //
       << tab() << "std::vector<std::pair<std::wstring, int>> entryList = \n"
       << tab() << "{\n";
    for (const auto& it : enumEntries)
    {
        ss << tab(2) << "{L\"" << it.first << "\", " << std::to_string(it.second) << "},\n";
    }
    ss << tab() << "};\n"                                                                             //
       << tab() << "string_utils::registerEnum(std::wstring(L\"" << enumName << "\"), entryList);\n"  //
       << "}\n";
    return ss.str();
}

std::string RegisteredVariable::getVarTypeEnumString(const std::string& arrayAccess) const
{
    if (isEnum)
    {
        return "IVarDef::ENUM";
    }

    return "IVarDef::getVarType(" + getFullName(arrayAccess) + ")";
}

std::string RegisteredVariable::getAddressAccess(const std::string& arrayAccess) const
{
    /// FIXME need to check for when &() is needed
    /// FIXME need to check when arrow access is needed
    return "&(" + getFullName(arrayAccess) + ")";
}

std::string RegisteredVariable::getArrayDesignation() const
{
    if (!isArray)
    {
        return "";
    }
    std::string s;
    for (const auto i : dimensions)
    {
        s += "(" + std::to_string(i) + ")";
    }
    return s;
}

std::string RegisteredVariable::getBuiltInTypeStr(const clang::Type* t, clang::ASTContext& context) const
{
    if (const clang::BuiltinType* bit = t->getAs<clang::BuiltinType>())
    {
        clang::PrintingPolicy pp(context.getLangOpts());
        return bit->getName(pp).str();
    }
    return "";
}

void RegisteredVariable::updateTypeInfo(clang::ASTContext& context, const clang::Type* t, const clang::QualType* qt, bool is_array)
{
    const clang::RecordDecl* typeRecord = t->getAsRecordDecl();

    isClass   = t->isClassType();
    isStruct  = t->isStructureType();
    isEnum    = t->isEnumeralType();
    isBuiltIn = t->isBuiltinType();
    isArray   = t->isConstantArrayType() || is_array;  // cannot register dynamic
    isPointer = t->isPointerType();

    if (isBuiltIn)
    {
        typeName = getBuiltInTypeStr(t, context);
    }
    else if (isEnum)
    {
        if (const clang::EnumType* et = t->getAs<clang::EnumType>())
        {
            std::string enumConvention = "";
            enumName                   = et->getAsTagDecl()->getNameAsString();
            // add enumerated values as convention for clarity over all interfaces
            const clang::EnumDecl* enumDecl = et->getDecl();
            for (auto it = enumDecl->enumerator_begin(); it != enumDecl->enumerator_end(); it++)
            {
                enumEntries.push_back(std::make_pair(it->getNameAsString(), it->getInitVal().getSExtValue()));
                enumConvention += it->getNameAsString() + "(" + std::to_string(it->getInitVal().getSExtValue()) + ") ";
            }
            convention = enumConvention;
        }
    }
    else if (isArray && !is_array)  // block when called from self
    {
        Logger::get().debug(m_name + " IS CONST ARRY");
        if (const auto* CAT = context.getAsConstantArrayType(*qt))
        {
            const clang::Type* ET     = getConstArrayType(CAT);
            const clang::QualType EQT = getConstArrayQualType(CAT);
            std::string typeStr       = "UNK";

            updateTypeInfo(context, ET, &EQT, true);

            dimensions = getConstantArrayExtents(CAT);
            std::string szstr;
            for (const auto& i : dimensions)
            {
                szstr += "[" + std::to_string(i) + "]";
            }
            Logger::get().debug("ARRAY: " + m_name + " TYPE: " + typeName + " SIZE: " + szstr);
        }
    }
    else
    {
        typeName = typeRecord->getNameAsString();
    }
}

size_t RegisteredVariable::getNumArrayElements() const
{
    if (!isArray)
    {
        return 0;
    }
    size_t numElem = 1;  // number of array elements
    for (const auto& i : dimensions)
    {
        numElem *= i;
    }
    return numElem;
}

std::string RegisteredVariable::getArrayAccessFromLinearIndex(size_t index) const
{
    std::vector<uint64_t> v = sub2ind(index, dimensions);
    return getArrayAccess(v);
}

void RegisteredVariable::setActiveArrayAccess(size_t index)
{
    m_activeArrayAccess = getArrayAccessFromLinearIndex(index);
}
void RegisteredVariable::clearActiveArrayAccess()
{
    m_activeArrayAccess = "";
}