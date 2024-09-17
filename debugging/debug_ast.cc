#include <cxxabi.h>
#include <abstraction_tree_syntax.h>
#include <scanner.h>
#include <parser.h>

static void debugTree() {
    Scanner scanner("((45 > 67) + (67 / 70))");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.parse();
    for (size_t i = 0; i < p.nodes.size(); ++i) {
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
    }
    return;
}

static void debugAnalyzeSemantics() {
  //ast aT(p.nodes);
    /*std::cout << "( " << std::get<0>(result)
              << ", " << std::get<1>(result).first 
              << " " << D.demangle(typeid(std::any_cast<Binary>(std::get<1>(result).second)).name())
              << " )\n";*/
    return;
}


static void debugIntermediateRepresentation() {

    return;
}
int main(void) {
    debugTree();
    return 0;
}
