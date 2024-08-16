#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
#include <catch.h>
#include <memory>
using ExprTypes = std::variant<Binary, Unary, Grouping, Literal>; // type-safe union 
extern ExprTypes* expr;                                                                
namespace AbstractionTreeSyntax {
    //template<class Type>
    class generateAst: public std::filesystem::path, public catcher<generateAst> {
        /* ------------------------------------------------------------------------------------------
         * class represents a generated abstraction syntax tree
         * It will output the code data structure
         * It will inherit from the base class using the virtual keyword which makes it an disorienated object 
         * This will isolate the objects behavior 
         * -----------------------------------------------------------------------------------------
         */
        public:
            explicit generateAst(): catcher() {
                path pp = path(getenv("Public-Projects"));
                path outputDir = pp;
                // Check if the path exists and is in user space
                if (std::filesystem::exists(outputDir) && std::filesystem::equivalent(outputDir.root_path(), pp.root_path())) {
                    auto hasPermission = [&](std::filesystem::perms perm) {
                        auto perms = std::filesystem::status(outputDir).permissions();
                        return (perms & perm) == perm;
                    };
                    // Check if we have write permissions
                    if (hasPermission(std::filesystem::perms::owner_write) && hasPermission(std::filesystem::perms::owner_read)) {
                        // Set the outputDir
                        this->outputDir = outputDir;
                    } else { throw generateAst::catcher("Failed to set the default path to write the ast to aka the file!");}
                }
            };
            inline std::string getOutPutDir() { return outputDir; };
            virtual ~generateAst() noexcept = default;
        private:
            std::string outputDir;
    };
    class ast: public virtual generateAst {
        // This class defines the tree for a specific programming language 
        public:
            ast();
            ~ast(){};
            template<class T>
            inline std::string parenthesize(const std::string name, T& expr) {
                std::string result;
                result += "(";
                result += name;
                result += " ";
                result += expr.accept(std::ref(expr));
                result += ")";
                ExprTypes variant_expr = expr;
                exprs.push_back(std::make_shared<ExprTypes>(variant_expr));
                tree.push_back(result); //TODO: The tree needs to be grouped together via paired with T& expr. So a custom data strcuture is going to be needed eventually
                return result;
            };
            inline std::string visitBinaryExpr(Binary& binary) { return parenthesize(binary.getToken().getLexeme(), binary);};
            inline std::string visitGroupingExpr(Grouping& grouping) { return parenthesize(std::string("group"), grouping);};
            inline std::string visitLiteralExpr(Literal& literal) { 
                std::any value = literal.getValue();
                if (!value.has_value()) return "nil";
                return literal.op->getLexeme();
            };
            inline std::string visitUnaryExpr(Unary& unary) { return parenthesize(unary.getToken().getLexeme(), unary);};
            inline void setTable() {this->table = initTable();};
            inline Table getTable() {return table;};
        private:
            Table table;
            std::string nameOfFile = file_name; // language_types.h 
            std::string outputDir = generateAst::getOutPutDir();
            std::vector<std::shared_ptr<ExprTypes>> exprs;
            std::vector<std::string> tree;
    };
    class analyzeSemantics: public catcher<analyzeSemantics> {
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

using namespace AbstractionTreeSyntax;

#endif
