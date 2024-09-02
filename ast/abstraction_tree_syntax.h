#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
#include <catch.h>
namespace AbstractionTreeSyntax {
    template<class Type>
    class generateAst: public catcher<Type> {
        /* ------------------------------------------------------------------------------------------
         * @brief A disorienated class object isolating its behavior. It will write data to a file by getting the literals from each expression it visits. 
         * ------------------------------------------------------------------------------------------
         */
        public:
            friend class ast;
            //generateAst() = default;
            explicit generateAst<Type>() {
                std::filesystem::path pp = std::filesystem::path(getenv("Public-Projects"));
                // Check if the path exists and is in user space
                if (std::filesystem::exists(pp)) {
                    auto hasPermission = [&](std::filesystem::perms perm) {
                        auto perms = std::filesystem::status(pp).permissions();
                        return (perms & perm) == perm;
                    };
                    // Check if we have write permissions
                    if (hasPermission(std::filesystem::perms::owner_write) && hasPermission(std::filesystem::perms::owner_read)) {
                        // Set the outputDir
                        outputDir_ = pp;
                    } else { 
                        catcher<Type> c("Failed to set the default path to write the ast to aka the file!");
                        throw c;
                    }
                }
            };
            virtual ~generateAst() noexcept = default;
            static void tree_();
        protected:
            std::string nameOfFile = file_name;
            static void writeFile(std::string& ext);
        private:
            std::string outputDir_;
            static std::string codeStr;
            static std::string compactedTreeStr;
            static logTable<std::map<std::string, std::vector<std::string>>> logs_;
            static std::vector<std::tuple<int, std::pair<std::string, std::any>>> compactedTreeNodes;
            static std::string ext;

    };
    class ast: public generateAst<ast> {
        /* --------------------------------------------------------------------------------------------
         * (Abstraction Syntax Tree) Description:
            This class creates an abstraction syntax tree by storing each expression instance inside a vector, for the intepreter class to evaulaute each instance using the visitor technique
         *
         * -------------------------------------------------------------------------------------------
         */
        public:
            ast(std::vector<std::tuple<int, std::pair<std::string, std::any>>>& expr_);
            ~ast() noexcept = default;
            inline void setTable(const std::unordered_map<std::string, std::vector<std::string>> languageExtensions, const std::unordered_map<std::string, std::string> downloads) { 
                table = initTable(languageExtensions, downloads); 
            };
            inline Table getTable() { return table; };
            friend class analyzeSemantics;
        private:
            Table table;
            
    };
    class analyzeSemantics: public ast {
        // This class performs the semantic analysis 
        public: 
            analyzeSemantics(ast &Ast);
            ~analyzeSemantics() noexcept = default;
        private:
            ast Ast; // Use list initializer to initialize this value 
    };
    class intermediateRepresentation: public analyzeSemantics {
        // This class Translates AST to intermediate representation (IR)
        public:
            intermediateRepresentation(analyzeSemantics &as);
            ~intermediateRepresentation() noexcept = default;
            void generate();
        private:
            analyzeSemantics as;
    };
};
using namespace AbstractionTreeSyntax;
#endif
