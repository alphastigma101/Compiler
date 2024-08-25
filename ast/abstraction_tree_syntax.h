#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
#include <catch.h>
template<typename T, typename U, typename V>
inline astTree<T, U, V> compressedAstTree(T first, U second, V third) {
    return std::make_tuple(first, std::make_pair(second, third));
};
template<typename B, typename U, typename G, typename L>
ExprTypes<B, U, G, L>* expr = new std::variant<Binary, Unary, Grouping, Literal>(nullptr); // externally link expr
namespace AbstractionTreeSyntax {
    template<class Type>
    class generateAst: public std::filesystem::path, public catcher<Type> {
        /* ------------------------------------------------------------------------------------------
         * (Generate Abstraction Syntax Tree) Description:
            A diorienated class object isolating its behavior. It will output the expressions it visits inside a .txt file 
         * ------------------------------------------------------------------------------------------
         */
        public:
            explicit generateAst() {
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
                    } else { throw catcher<Type>("Failed to set the default path to write the ast to aka the file!");}
                }
            };
            virtual ~generateAst() noexcept = default;
            void writeFile();
            friend class ast;
        private:
            std::string file_name, user_choice;
            std::string outputDir;
            std::string nameOfFile = file_name; // language_types.h 
    };
    class ast: public generateAst<ast> {
        /* --------------------------------------------------------------------------------------------
         * (Abstraction Syntax Tree) Description:
            This class creates an abstraction syntax tree by storing each expression instance inside a vector, for the intepreter class to evaulaute each instance using the visitor technique
         *
         * -------------------------------------------------------------------------------------------
         */
        public:
            ast(ExprTypes<Binary, Unary, Grouping, Literal>& expr);
            ~ast(){};
            inline void setTable() {this->table = initTable();};
            inline Table getTable() {return table;};
            friend class analyzeSemantics;
        private:
            Table table;
            ExprTypes<Binary, Unary, Grouping, Literal> expr;
    };
    class analyzeSemantics: public ast {
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
