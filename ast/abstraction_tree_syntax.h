#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
typedef astTree<int, std::string, ExprVariant> treeEntry;
//TODO: Need to remove the wrapper around the ExprVariant 
extern template struct std::tuple<int, std::pair<std::string, ExprTypes<std::monostate, ListOfType<ExprVariant>>>>;
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
            static std::string codeStr;
            static std::string compactedTreeStr;
            static logTable<std::map<std::string, std::vector<std::string>>> logs_;
            static std::vector<treeEntry> compactedTreeNodes;
            static std::string ext;
    };
    class ast: public generateAst<ast> {
        /* --------------------------------------------------------------------------------------------
         * @brief This class creates an abstraction syntax tree by storing each expression instance inside a vector, for the intepreter class to evaulaute each instance using the visitor technique
         * -------------------------------------------------------------------------------------------
        */
        public:
            ast(std::vector<treeEntry>& expr_);
            ~ast() noexcept = default;
            inline void setTable(const std::unordered_map<std::string, std::vector<std::string>> languageExtensions, const std::unordered_map<std::string, std::string> downloads) { 
                table = initTable(languageExtensions, downloads); 
            };
            inline Table getTable() { return table; };
            //inline static treeEntry getTree() { return compactedTreeNodes; };
        //private:
            static void tree_(const generateAst<ast>& gA);
            static void writeFile(std::string& ext);
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
