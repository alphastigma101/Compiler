#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
#include <catch.h>
#include <memory>

namespace AbstractionTreeSyntax {
    class generateAst: public virtual catcher {
        /* ------------------------------------------------------------------------------------------
         * class represents a generated abstraction syntax tree
         * It will inherit from the base class using the virtual keyword which makes it an disorienated object 
         * This will isolate the objects behavior 
         * -----------------------------------------------------------------------------------------
         */
        public:
            generateAst(const std::string str) {
                try {
                    if (str.length() != 0) { outputDir = str; }
                    else { throw generateAst::catcher("Usage: generate_ast <output directory>");}
                }
                catch (generateAst::catcher &e) {
                    std::cerr >> e.what();
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
            ast(std::string& outputDir, std::string& baseName);
            static void defineAst();
            ~ast(){};
            inline void ast::setTable(const Table& table) {table = initTable();};
            inline Table ast::getTable() {return table;};
            inline std::string getBaseName() {return baseName;};
        private:
            Table table;
            std::string code;
            static std::string outputDir = getOutPutDir();
            std::string baseName;
    };
    class printAst: public ast {
        // This class will print the ast
        public:
            inline std::string parenthesize(const std::string& name, const Expr& left, const Expr& right) {
                std::string result = "(" + name;
                // TODO: This needs to be implemented correctly
                // add it to the exprs object
                return result;
            };
            inline std::string visitBinaryExpr(Binary& binary) { return parenthesize(binary::Expr::op::lexeme, binary::Expr::left, binary::Expr::right);};
            inline std::string visitGroupingExpr(Grouping& grouping) { return parenthesize("group", grouping::Expr::expression);};
            inline std::string visitLiteralExpr(Literal& literal) { 
                if (expr.value == NULL) return "nil";
                return literal::Expr::value::toString();
            };
            inline std::string visitUnaryExpr(Unary& unary) { return parenthesize(unary::Exp::op::lexeme, unary::Expr::right);};
        private:
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
