#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
#include <catch.h>
#include <memory>

namespace AbstractionTreeSyntax {
    class generateAst: public std::filesystem::path, public virtual catcher {
        /* ------------------------------------------------------------------------------------------
         * class represents a generated abstraction syntax tree
         * It will output the code data structure
         * It will inherit from the base class using the virtual keyword which makes it an disorienated object 
         * This will isolate the objects behavior 
         * -----------------------------------------------------------------------------------------
         */
        public:
            generateAst() {
                try {
                    path pp = path(getenv("Public-Projects"));
                    path outputDir = pp;
                    // Check if the path exists and is in user space
                    if (std::filesystem::exists(outputDir) && std::filesystem::equivalent(outputDir.root_path(), pp.root_path())) {
                        // Check if we have write permissions
                        if (std::filesystem::is_directory(outputDir) && std::filesystem::status(outputDir).permissions() & std::filesystem::perms::owner_write) {
                            // Set the outputDir
                            this->outputDir = outputDir;
                        } else { throw std::runtime_error("No write permission for the output directory");}
                    } 
                    else {
                            // If the directory doesn't exist, try to create it
                            if (std::filesystem::create_directories(outputDir)) { this->outputDir = outputDir;} 
                            else { throw std::runtime_error("Failed to create output directory");}
                        }
                }
                catch(const std::exception& e) {
                    std::cerr << "Error in generateAst(): " << e.what() << std::endl;
                }
            };
            inline std::string getOutPutDir() { return outputDir; };
            virtual ~generateAst() = default;
        private:
            std::string outputDir;
    };
    class ast: public virtual generateAst {
        // This class defines the tree for a specific programming language 
        public:
            ast(const std::string nameOfFile);
            ~ast(){};
            inline std::string parenthesize(std::string& name, const std::vector<std::reference_wrapper<Expr>>& expressions) {
                 for (const auto& expr : expressions) {
                     result += " ";
                     result += expr.accept(*this);
                 }
                 result += ")";
                 // Add expressions to the exprs vector
                 for (const auto& expr : expressions) {
                    exprs.push_back(std::make_shared<Expr>(expr));
                 }
                return result;
            };
            inline std::string visitBinaryExpr(Binary& binary) { return parenthesize(binary::Expr::op::lexeme, {binary::Expr});};
            inline std::string visitGroupingExpr(Grouping& grouping) { return parenthesize("group", {grouping::Expr});};
            inline std::string visitLiteralExpr(Literal& literal) { 
                if (expr.value == NULL) return "nil";
                literal::Expr->op = literal.value;
                return literal::Expr::op::toString();
            };
            inline std::string visitUnaryExpr(Unary& unary) { return parenthesize(unary::Exp::op::lexeme, {unary::Expr});};
            inline void setTable(const Table& table) {table = initTable();};
            inline Table getTable() {return table;};
        private:
            Table table;
            static std::string nameOfFile = file_name; // language_types.h 
            static std::string outputDir = getOutPutDir();
            std::vector<std::shared_ptr<Expr>> exprs;
    };
    class analyzeSemantics: public virtual catcher {
        // This class performs the semantic analysis 
        public: 
            analyzeSemantics(ast &Ast);
            ~analyzeSemantics();
        private:
            ast Ast; // Use list initializer to initialize this value 
    };
    class intermediateRepresentation: public analyzeSemantics {
        // This class Translates AST to intermediate representation (IR)
        public:
            intermediateRepresentation(analyzeSemantics &as);
            ~intermediateRepresentation();
            void generate();
        private:
            analyzeSemantics as;
    };
};

using namespace AbstractionTreeSyntax; // make it global so inheriting the classes are easier

#endif
