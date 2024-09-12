#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
extern template struct std::tuple<int, std::pair<String, Shared<ExprVariant>>>;
typedef astTree<int, String, ExprVariant> treeEntry;
namespace AbstractionTreeSyntax {
    template<class Type>
    class generateAst: public catcher<Type> {
        /* ------------------------------------------------------------------------------------------
         * @brief A disorienated class object isolating its behavior. It will write data to a file by getting the literals from each expression it visits. 
         * ------------------------------------------------------------------------------------------
         */
        public:
            friend class ast;
            friend class catcher<Type>;
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
                        outputDir_ = std::move(pp);
                    } else { 
                        catcher<Type> c("Failed to set the default path to write the ast to aka the file!");
                        throw c;
                    }
                }
            };
            virtual ~generateAst() noexcept = default;
            inline void tree_(const generateAst<Type>& gA) { return static_cast<Type*>(this)->tree_(gA); };
        protected:
            inline static const char* what(const char* msg = catcher<Type>::getMsg()) throw() { return msg; };
            std::string nameOfFile = std::move(file_name);
            inline void writeFile(std::string& ext) { return static_cast<Type*>(this)->writeFile(ext); };
        private:
            std::string outputDir_;
            static String codeStr;
            static String compactedTreeStr;
            static logTable<Map<String, Vector<String>>> logs_;
            static Vector<treeEntry> compactedTreeNodes;
            static String ext;
    };
    class ast: public generateAst<ast> {
        /* --------------------------------------------------------------------------------------------
         * @brief This class creates an abstraction syntax tree by storing each expression instance inside a vector, for the intepreter class to evaulaute each instance using the visitor technique
         * -------------------------------------------------------------------------------------------
        */
        public:
            friend class generateAst<ast>; // Link the generateAst together with the ast 
            ast(std::vector<treeEntry>& expr_);
            ~ast() noexcept = default;
            inline static Table getTable() { return table; };
            /** ---------------------------------------------------------------
             * @brief Is a simple getter method. but once used, it will move the resources over to the new variable 
             *
             * @param None
             *
             * @return compactedTreeNodes resources
             *
             * ----------------------------------------------------------------
             */
            inline static const std::vector<treeEntry>& getTree() { return std::move(compactedTreeNodes); };
        private:
            static void tree_(const generateAst<ast>& gA);
            static void writeFile(std::string& ext);
            static Table table;
    };
    class analyzeSemantics: public catcher<analyzeSemantics> {
        // This class performs the semantic analysis 
        public: 
            friend class catcher<analyzeSemantics>;
            explicit analyzeSemantics(ast &Ast_);
            ~analyzeSemantics() noexcept = default;
        protected:
            inline static const char* what(const char* msg = catcher<analyzeSemantics>::getMsg()) throw() { return msg; };
        private:
            ast&& Ast; // Use list initializer to initialize this value 
    };
    class intermediateRepresentation: public catcher<intermediateRepresentation> {
        // This class Translates AST to intermediate representation (IR)
        public:
            friend class catcher<intermediateRepresentation>;
            explicit intermediateRepresentation(analyzeSemantics &as_);
            ~intermediateRepresentation() noexcept = default;
            static void generate();
        private:
            analyzeSemantics&& as;
    };
};
using namespace AbstractionTreeSyntax;
#endif
