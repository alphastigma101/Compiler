#include <cxxabi.h>
#include <abstraction_tree_syntax.h>
#include <scanner.h>
#include <parser.h>

/*template<class T>                                                                      
class Debug {
    public:
        Debug<T>();
        ~Debug<T>();
        std::string demangle<T>(const char* name);
};
template<class T>
Debug<T>::Debug() { }
Debug::~Debug() {}*/

/*std::string Debug::demangle(const char* name) {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return (status == 0) ? res.get() : name;
}*/

static void debugReturnsCorrectTuple() {
    //Debug D;
    Scanner scanner("((45 > 67) + (67 / 70))");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.parse();
    /*for (size_t i = 0; i < p.nodes.size(); ++i) {
        const auto& [intValue, pairValue] = p.nodes[i];
        const auto& [stringValue, exprValue] = pairValue;

        std::cout << "Node " << i << ":\n";
        std::cout << "  Int value: " << intValue << "\n";
        std::cout << "  String value: " << stringValue << "\n";
        std::cout << "  ExprVariant address: " << exprValue.get() << "\n";
        
        // If ExprVariant has a method to represent itself as a string, use it here
        // For example: std::cout << "  ExprVariant value: " << exprValue->toString() << "\n";
        
        std::cout << "\n";
        if (p.nodes.empty()) {
            std::cout << "Not good!" << std::endl;
        }
    }*/
    ast aT(p.nodes);
    /*std::cout << "( " << std::get<0>(result)
              << ", " << std::get<1>(result).first 
              << " " << D.demangle(typeid(std::any_cast<Binary>(std::get<1>(result).second)).name())
              << " )\n";*/
    return;
}

// Test generateAst constructor Tree method
/*void debugGenerateAstConstructor() {
    // Expecting it to throw an exception
    // Because file_name and user_choice should be both null
    generateAst<ast> gA;
    gA.tree_();
    return;
}*/

/*void debugAstConstructor() {
    auto res =  Debug::B();
    astTree<int, std::string, std::any> result = compressedAstTree(3, "Binary", std::make_any<Binary>(res));
    std::vector<astTree<int, std::string, std::any>> v;
    v.push_back(result);
    // Dynamically allocate memory for `ast`
    ast at(v);
    return;
}*/


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
    return;
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
    //debugAstConstructor();
    //debugGenerateAstConstructorInvalidPath();
    //debugAstConstructor();
    //debugAstSetAndGetTable();
    //debugAnalyzeSemanticsConstructor();
    //debugIntermediateRepresentationConstructorAndGenerate();
    return 0;
}
