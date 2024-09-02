#include <cxxabi.h>
#include <abstraction_tree_syntax.h>
logTable<std::map<std::string, std::vector<std::string>>> logEntries; // declare variable globally
class AbstractionTreeSyntaxTest: public ContextFreeGrammar::Binary {
    public:
        AbstractionTreeSyntaxTest();
        ~AbstractionTreeSyntaxTest();
        std::string demangle(const char* name);
        static Binary B();
};
Binary AbstractionTreeSyntaxTest::B() { 
    return Binary(); 
}
AbstractionTreeSyntaxTest::AbstractionTreeSyntaxTest() { }
AbstractionTreeSyntaxTest::~AbstractionTreeSyntaxTest() {}
std::string AbstractionTreeSyntaxTest::demangle(const char* name) {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return (status == 0) ? res.get() : name;
}

static void debugReturnsCorrectTuple() {
    AbstractionTreeSyntaxTest atst;
    auto res =  AbstractionTreeSyntaxTest::B();
    astTree<int, std::string, std::any> result = compressedAstTree(1, "test", std::make_any<Binary>(res));
     std::cout << "( " << std::get<0>(result)
              << ", " << std::get<1>(result).first 
              << " " << atst.demangle(typeid(std::any_cast<Binary>(std::get<1>(result).second)).name())
              << " )\n";
       
    /*for (int i = 0; i < std::tuple_size<result>; i++) {
        std::cout << it << std::endl;
    }*/
    astTree<std::string, std::string, std::string> test = compressedAstTree("1", "test", "3.1");
    //std::vector<astTree> v;
    return;
}

// Test generateAst constructor Tree method
void debugGenerateAstConstructor() {
    // Expecting it to throw an exception
    // Because file_name and user_choice should be both null
    generateAst<ast> gA;
    gA.tree_();
    return;
}

void debugGenerateAstConstructorInvalidPath() {
    // Temporarily set an invalid environment variable
    setenv("Public-Projects", "/invalid/path", 1);
    generateAst<ast> gA;
    return;
}

// Test ast constructor
void debugAstConstructor() {
    //ExprTypes expr; // You need to define this type and provide a valid instance
    // ast tree(expr);
    return;
}

// Test ast setTable and getTable methods
void debugAstSetAndGetTable() {
    //ExprTypes expr; // You need to define this type and provide a valid instance
    //ast tree(expr);
    //tree.setTable();
    //Table table = tree.getTable();
    return;
}


void debugAnalyzeSemanticsConstructor() {
    //ExprTypes expr; // You need to define this type and provide a valid instance
    //ast tree(expr);
    //analyzeSemantics semantics(tree);
}

// Test intermediateRepresentation constructor and generate method
void debugIntermediateRepresentationConstructorAndGenerate() {
    //ExprTypes expr; // You need to define this type and provide a valid instance
    //ast tree(expr);
    //analyzeSemantics semantics(tree);
    //intermediateRepresentation ir(semantics);
    //ir.generate();
    return;
}

int main(void) {
    debugReturnsCorrectTuple();
    //debugGenerateAstConstructor();
    //debugGenerateAstConstructorInvalidPath();
    //debugAstConstructor();
    //debugAstSetAndGetTable();
    //debugAnalyzeSemanticsConstructor();
    //debugIntermediateRepresentationConstructorAndGenerate();
    return 0;
}
