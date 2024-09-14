#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
#include <threading.h>
#if ENABLE_TESTING
    String file_name, user_choice;
    int settings;
#else 
    //std::cout << "Testing is enabled!" << std::endl;
#endif
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
            explicit generateAst<Type>();
            virtual ~generateAst<Type>() noexcept = default;
            inline void tree_(const generateAst<Type>& gA) { return static_cast<Type*>(this)->tree_(gA); };
        protected:
            inline static const char* what(const char* msg = catcher<Type>::getMsg()) throw() { return msg; };
            std::string nameOfFile = std::move(file_name);
            inline void writeFile(std::string& ext) { return static_cast<Type*>(this)->writeFile(ext); };
        private:
            std::string outputDir_;
            inline static String codeStr;
            inline static String compactedTreeStr;
            inline static logTable<Map<String, Vector<String>>> logs_;
            inline static Vector<treeEntry> compactedTreeNodes;
            inline static String ext;
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
            inline static const String& getCode() { return codeStr; };
        private:
            static void tree_(const generateAst<ast>& gA);
            static void writeFile(std::string& ext);
            inline static Table table;
    };
    class analyzeSemantics: public catcher<analyzeSemantics>,  public ThreadTracker<analyzeSemantics> {
        // This class performs the semantic analysis 
        public: 
            friend class catcher<analyzeSemantics>;
            analyzeSemantics(Shared<ast> Ast_);
            ~analyzeSemantics() noexcept = default;
            inline static Map<String, String> getAnalyzedCodeMap() { return std::move(analyzeCode); };
        protected:
            inline static const char* what(const char* msg = catcher<analyzeSemantics>::getMsg()) throw() { return msg; };
            /** ---------------------------------------------------------------------------------
                * @brief A method that creates a thread for the class analyzeSemantics
                * 
                * @details Spawns in the thread. Main thread will allow this thread to access it.
                *          It targets a certain method called getCodeStr which returns a string type 
                * 
                * --------------------------------------------------------------------------------
            */
            inline static void run(Shared<ast> Ast) {
                String temp = Ast->getCode();
                for (int i = 0; i < temp.size(); i++) {
                    // TODO: Start mapping the every character into the map or change the map into a vector 
                } 
            };
        private:
            inline static Map<String, String> analyzeCode;
    };
    class intermediateRepresentation: public catcher<intermediateRepresentation>, public ThreadTracker<intermediateRepresentation> {
        // This class Translates AST to intermediate representation (IR)public ThreadTracker<analyzeSemantics>
        public:
            friend class catcher<intermediateRepresentation>;
            explicit intermediateRepresentation(Shared<analyzeSemantics> as_);
            ~intermediateRepresentation() noexcept = default;
            static void generate();
        protected:
            inline static const char* what(const char* msg = catcher<analyzeSemantics>::getMsg()) throw() { return msg; };
            inline static void run(Shared<analyzeSemantics> as_) { 

            };
       
    };
};
using namespace AbstractionTreeSyntax;
#endif
