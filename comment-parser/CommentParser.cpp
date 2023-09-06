// Declares clang::SyntaxOnlyAction.
#include "clang/AST/ASTDumper.h"
#include "clang/AST/Comment.h"
#include "clang/AST/CommentVisitor.h"
#include "clang/AST/RawCommentList.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"

#include <iostream>

using namespace clang::tooling;
using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;

// #define _VERBOSE // will dump AST

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...\n");

/// traverses the children of comment. BlockCommandComment and ParagraphComment are recursive
/// \param comment to be traversed
/// \param context used to obtain command names
void readComments(clang::comments::Comment* comment, ASTContext& context)
{
#if defined(_VERBOSE)
    comment->dumpColor();
#endif
    for (comments::Comment::child_iterator I = comment->child_begin(), E = comment->child_end(); I != E; ++I)
    {
        if (comments::InlineCommandComment* IC = dyn_cast<comments::InlineCommandComment>(*I))
        {
            std::string cmd = context.getCommentCommandTraits().getCommandInfo(IC->getCommandID())->Name;
            std::string value;
            // obtain the value
            comments::Comment::child_iterator _I = I;
            ++_I;
            if (comments::TextComment* TC = dyn_cast<comments::TextComment>(*_I))
            {
                value = TC->getText().str();
            }
            std::cout << cmd << " = " << value << "\n";
        }
        if (comments::BlockCommandComment* BC = dyn_cast<comments::BlockCommandComment>(*I))
        {
            std::string blockCmd = context.getCommentCommandTraits().getCommandInfo(BC->getCommandID())->Name;
            readComments(BC, context);
        }
        if (comments::ParagraphComment* PC = dyn_cast<comments::ParagraphComment>(*I))
        {
            readComments(PC, context);
        }
    }
}

// https://stackoverflow.com/a/25103360
DeclarationMatcher FieldDeclMatcher = clang::ast_matchers::fieldDecl().bind("field_decl");
class LoopPrinter : public MatchFinder::MatchCallback
{
        public:
    virtual void run(const MatchFinder::MatchResult& result)
    {
        if (const clang::FieldDecl* fd = result.Nodes.getNodeAs<clang::FieldDecl>("field_decl"))
        {
            std::cout << "\n======== FieldDecl found ======\n";
            const clang::RecordDecl* rd = fd->getParent();
            const clang::QualType qt    = fd->getType();
            const clang::Type* t        = qt.getTypePtr();
            std::cout << "found '" << fd->getQualifiedNameAsString() << " " << fd->getName().str() << "' in '"
                      << rd->getName().str() << "' "
                      << "is BuiltinType = " << t->isBuiltinType() << " " << std::endl
                      << std::endl;

            ASTContext& context = fd->getASTContext();
            if (auto comment = context.getLocalCommentForDeclUncached(fd))
            {
                readComments(comment, context);
            }
        }

    }  // end of run()
};

int main(int argc, const char** argv)
{
    auto ExpectedParser = CommonOptionsParser::create(argc, argv, MyToolCategory);
    if (!ExpectedParser)
    {
        // Fail gracefully for unsupported options.
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }
    CommonOptionsParser& OptionsParser = ExpectedParser.get();
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

    LoopPrinter printer;
    MatchFinder finder;

    finder.addMatcher(FieldDeclMatcher, &printer);

    return Tool.run(newFrontendActionFactory(&finder).get());
}