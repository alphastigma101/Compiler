#include <cxxabi.h>
#include <abstraction_tree_syntax.h>
#include <scanner.h>
#include <parser.h>
 Vector<deepCopy<treeStructure>> temp;
static void debugTree() {
    Vector<String> test_strs = {
        "(((45 > 67) + (67 / 70)) * ((99 <= 100) - (88 == 88)) + ((34 * 2) / (16 % 5)) + ((23 != 24) && (56 >= 12)) || ((15 + 19) < (7 * 3)))"
    };
    Scanner scanner("((45 > 67) + (67 / 70))");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.beginParse();
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
