#include <abstraction_tree_syntax.h>


void debugReturnsCorrectTuple() {
    auto result = compressedAstTree(1, "test", 3.14);
    /*for (auto &it: result) {
        std::cout << it << std::endl;
    }*/
    return;
}

// Test generateAst constructor
void debugGenerateAstConstructor() {
    generateAst ast;
    return;
}

void debugGenerateAstConstructorInvalidPath() {
    // Temporarily set an invalid environment variable
    setenv("Public-Projects", "/invalid/path", 1);
    generateAst ast;
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
    debugGenerateAstConstructor();
    debugGenerateAstConstructorInvalidPath();
    debugAstConstructor();
    debugAstSetAndGetTable();
    debugAnalyzeSemanticsConstructor();
    debugIntermediateRepresentationConstructorAndGenerate();
    return 0;
}
