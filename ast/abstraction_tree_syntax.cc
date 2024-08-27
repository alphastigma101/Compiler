#include <abstraction_tree_syntax.h>
/*
 * (ast): The default constructor that calls in generateAst to start creating the .txt file 
 * Arguments:
 * outputDir: Is the name of the file that will hold the ast structure 
 * baseName: The name of the file code is getting written to 
*/
ast::ast(std::vector<std::tuple<int, std::pair<std::string, std::any>>>& expr): expr(this->expr) {
    ast::setTable(); // Get the look up table
    auto pair = table.at(user_choice); // pair->first is the extensions, pair->ssecond is the download links for the program
    try {
        generateAst gA;
    }
    catch(ast::catcher& e) {
        std::cout << e.what();
    }
    // TODO: Now do some threading and call in IR and analyzeSemantics which will need to be created before the interpreters as threading 
    // Must make the multi-threading very robust. Meaning, avoid deadlock, if there's a null or exception occurs in any thread, stop one of them and continue the other ones if possible
    // There should be at least three threads:
    // 1. For the writeFile which will write the ast tree to  a .txt file. This should be the third thread
    // 2. analyzeSemantics which will analze the compressedAstTree by visiting each node and adding to the nodes. refer to the TODO: in declarations.h first thread
    // 3. IR will be the third and final thread
}

template<>
void generateAst<ast>::writeFile() {
    // Take the outputDir and start iterating through exprs from the interpreter.cc file by threading it from the intrerpret.cc
}

