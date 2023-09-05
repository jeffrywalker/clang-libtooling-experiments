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

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...\n");

// https://stackoverflow.com/a/25103360
DeclarationMatcher FieldDeclMatcher = clang::ast_matchers::fieldDecl().bind("field_decl");
class LoopPrinter : public MatchFinder::MatchCallback
{
        public:
    virtual void run(const MatchFinder::MatchResult& result)
    {
        if (const clang::FieldDecl* fd = result.Nodes.getNodeAs<clang::FieldDecl>("field_decl"))
        {
            std::cout << "======== FieldDecl found ======" << std::endl;

            const clang::RecordDecl* rd = fd->getParent();
            const clang::QualType qt    = fd->getType();
            const clang::Type* t        = qt.getTypePtr();

            // https://stackoverflow.com/a/25294210
            // SourceManager& sm      = ctx.getSourceManager();
            // const RawComment* rc   = fd->getASTContext().getRawCommentForDeclNoCache(fd);
            // if (rc)
            // {
            //     // Found comment!
            //     SourceRange range = rc->getSourceRange();

            //     PresumedLoc startPos = sm.getPresumedLoc(range.getBegin());
            //     PresumedLoc endPos   = sm.getPresumedLoc(range.getEnd());

            //     std::string raw   = rc->getRawText(sm).str();
            //     std::string brief = rc->getBriefText(ctx);
            //     std::cout << "raw: " << raw << "\nbrief: " << brief << "\n";

            //     // ... Do something with positions or comments
            // }

            ASTContext& context = fd->getASTContext();
            if (auto comment = context.getLocalCommentForDeclUncached(fd))
            {
                comment->dumpColor();
                // referencing ASTNodeTraverse.h line:259
                int i = 0;
                for (comments::Comment::child_iterator I = comment->child_begin(), E = comment->child_end(); I != E; ++I)
                {
                    if (comments::InlineCommandComment* IC = dyn_cast<comments::InlineCommandComment>(*I))
                    {
                        std::cout << "inline command comment\n";
                        std::cout << IC->getCommentKindName() << "\n";
                    }
                    if (comments::BlockCommandComment* IC = dyn_cast<comments::BlockCommandComment>(*I))
                    {
                        std::cout << "block command comment: "
                                  << context.getCommentCommandTraits().getCommandInfo(IC->getCommandID())->Name << "\n";
                    }
                    /// TODO need some recursion similar to the native dump command.
                    /// The desired commands are nested in the ParagraphComments.

                    std::cout << "iterating " << i << "\n";
                    ++i;
                }
            }

            std::cout << "FieldDecl found '" << fd->getQualifiedNameAsString() << " " << fd->getName().str() << "' in '"
                      << rd->getName().str() << "'. "
                      << "is Builtintype = " << t->isBuiltinType() << " " << std::endl
                      << std::endl;
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