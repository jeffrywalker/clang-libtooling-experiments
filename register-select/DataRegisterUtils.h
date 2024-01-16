#pragma once
#include "RegisteredVariable.h"
#include <vector>

namespace clang
{
    namespace comments
    {
        class Comment;
    }
    class ASTContext;
    class ConstantArrayType;
    class Type;
}  // namespace clang

namespace data_registration
{
    /// traverses the children of comment. BlockCommandComment and ParagraphComment are recursive
    /// \param [in] comment to be traversed
    /// \param [in] context used to obtain command names
    /// \param [out] varInfo registered variable information
    /// \param [in] isParagraphComment indicator when called on self
    void readComments(clang::comments::Comment* comment, clang::ASTContext& context, data_registration::RegisteredVariable& varInfo,
                      bool isParagraphComment = false);
    /// This is a helper function for `getConstantValFromConstArrayInitializer`.
    ///
    /// Return an array of extents of the declared array type.
    ///
    /// E.g. for `int x[1][2][3];` returns { 1, 2, 3 }.
    std::vector<uint64_t> getConstantArrayExtents(const clang::ConstantArrayType* CAT);

    /// \returns the Type of the underlying element. E.g., obtained from last array dimension
    const clang::Type* getConstArrayType(const clang::ConstantArrayType* CAT);
    const clang::QualType getConstArrayQualType(const clang::ConstantArrayType* CAT);

    /// converts linear index to multiple subscript access
    /// \note this has not been tested to produce the expected row/col sorted order
    std::vector<uint64_t> sub2ind(uint64_t index, std::vector<uint64_t> dimensions);

    /// \returns [i][j][k] for the given vector
    std::string getArrayAccess(const std::vector<uint64_t>& v);

}  // namespace data_registration