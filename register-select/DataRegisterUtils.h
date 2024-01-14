#pragma once
#include "RegisteredVariable.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Comment.h"

namespace data_registration
{
    /// traverses the children of comment. BlockCommandComment and ParagraphComment are recursive
    /// \param [in] comment to be traversed
    /// \param [in] context used to obtain command names
    /// \param [out] varInfo registered variable information
    /// \param [in] isParagraphComment indicator when called on self
    void readComments(clang::comments::Comment* comment, clang::ASTContext& context, data_registration::RegisteredVariable& varInfo,
                      bool isParagraphComment = false);


    /// processes a field declaration traversing children if not a built-in type
    /// \param [in] list name this is being registered as
    /// \param [in] fd the field being processed
    /// \param [in] parent used by recursive calls when (field) is a compound type
    void _migrate_registerFieldDecl(const std::string& listName, const clang::FieldDecl* fd,
                                    const data_registration::RegisteredVariable* parent = nullptr);
}  // namespace data_registration