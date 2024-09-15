#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
#include <threading.h>
#if ENABLE_TESTING
    String file_name, user_choice;
    int settings;
#endif
extern template struct std::tuple<int, std::pair<String, Shared<ExprVariant>>>; // Create the underlying of the astTree
typedef astTree<int, String, ExprVariant> treeStructure;
namespace AbstractionTreeSyntax {
    template<class Type>
    class generateAst: public catcher<Type> {
        /* ---------------------------------------------------------------------
         * @brief A disorienated class object isolating its behavior. It will write data to a file by getting the literals from each expression it visits. 
         * ---------------------------------------------------------------------
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
            inline static Unique<Atomic<const char*>> accessCodeStr;
            inline static String codeStr;
            inline static String compactedTreeStr;
            inline static logTable<Map<String, Vector<String>>> logs_;
            inline static Vector<treeStructure> compactedTreeNodes;
            inline static String ext;
    };
    class ast: public generateAst<ast> {
        /* ---------------------------------------------------------------------
         * @brief This class creates an abstraction syntax tree by storing each expression instance inside a vector. 
         *        for the intepreter class to evaulaute each instance using the visitor technique
         * ---------------------------------------------------------------------
        */
        public:
            friend class generateAst<ast>; // Link the generateAst together with the ast 
            ast(std::vector<treeStructure>& expr_);
            ~ast() noexcept = default;
            inline static Table getTable() { return table; };
            inline static Unique<Atomic<const char*>> getCode() { return std::move(accessCodeStr); };
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
            inline static Map<int, String> getAnalyzedCodeMap() { return std::move(analyzeCode); };
        protected:
            inline static const char* what(const char* msg = catcher<analyzeSemantics>::getMsg()) throw() { return msg; };
            /** ----------------------------------------------------------------
                * @brief A method that creates a thread for the class analyzeSemantics
                * 
                * @details Spawns in the thread. Main thread will allow this thread to access it.
                *          It uses a getter method to get an atomic object wrapped in a unique_ptr and loads gets the value
                * @details The average/worse case for this method would be O(n)
                * --------------------------------------------------------------
            */
            inline static void run(Shared<ast> Ast) {
                // Want this: memory_order_release or memory_order_relaxed
                if (auto thread_id = strToId.find("treeThread"); thread_id != strToId.end()) {
                    int node = 0;
                    // Expression that indexes at the specific thread 
                    // Once removed this expression should break out
                    std::thread::id default_id; // default constructor id 
                    while (thread_id->second != default_id) {
                        // Might have to check and see if it is not null
                        String stringLiteral = Ast.get()->getCode()->load(std::memory_order_release);
                        analyzeCode[node] = stringLiteral;
                        node++;
                    }
                }
            };
        private:
            inline static Map<int, String> analyzeCode;
    };
    class intermediateRepresentation: public catcher<intermediateRepresentation>, public ThreadTracker<intermediateRepresentation> {
        // This class Translates AST to intermediate representation (IR)public ThreadTracker<analyzeSemantics>
        public:
            friend class catcher<intermediateRepresentation>;
            explicit intermediateRepresentation(Weak<analyzeSemantics> as_);
            ~intermediateRepresentation() noexcept = default;
            static void generate();
        protected:
            inline static const char* what(const char* msg = catcher<intermediateRepresentation>::getMsg()) throw() { return msg; };
            inline static void run(Weak<analyzeSemantics> as_weak) { 
                if (auto thread_id = strToId.find("semanticThread"); thread_id != strToId.end()) {
                    int node = 0;
                    // Expression that indexes at the specific thread 
                    // Once removed this expression should break out
                    std::thread::id default_id;
                    while (thread_id->second != default_id) {
                        if (auto aSLocked = as_weak.lock()) {
                            // Might have to check and see if it is not null
                            //String stringLiteral = Ast.get()->getCode()->load(std::memory_order_release);
                            //analyzeCode[node] = stringLiteral;
                            node++;
                        } else {
                            // If the analyzeSemantic thread dies before this is done 
                            // Move the map over and continue creating the graph
                        }
                    }
                }
            };
        private:
            void adjacent(auto& G, int x, int y);
            void neighbors(auto& G, int x);
            void add_vertex(auto& G, int x);
            void remove_vertex(auto& G, int x);
            void add_edge(auto& G, int x, int y, int z);
            void remove_edge(auto& G, int x, int y);
            void get_vertex_value(auto& G, int x);
            void set_vertex_value(auto& G, int x, int v);
    };
};
using namespace AbstractionTreeSyntax;
#endif
