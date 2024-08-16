#include <abstraction_tree_syntax.h>
/*
 * (ast): The default constructor that creates the..
 * Arguments:
 * outputDir: Is the name of the file that will hold the ast structure 
 * baseName: The name of the file code is getting written to 
*/
ast::ast() {
    ast::setTable(); // Get the look up table
    auto pair = table.at(user_choice); // pair->first is the extensions, pair->ssecond is the download links for the program
    try {
        ast::generateAst(outputDir);
    }
    catch(ast::catcher& e) {
        std::cout << e.what();
    }
    // TODO: include a rich eco system based on the file extension the user chooses and add 
}

