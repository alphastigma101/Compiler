#include <abstraction_tree_syntax.h>
#include <lookup_language.h> // get the file extensions 
//template struct std::tuple<int, std::pair<String, Expr>>; // Explicit initialize the underyling of astTree type

/** ------------------------------------
 * @brief An abstraction class that checks to see if it allowed to create a .txt flie
 * 
 * --------------------------------------
 */
template<>
//generateAst<ast>::generateAst(Expr& expr) 
generateAst<ast>::generateAst() noexcept {
    
}
/** -----------------------------------------------------------------------------------------
 * @brief The default constructor that calls in generateAst to start creating the .txt file 
 * 
 * @param expr: The data structure that represents the compacted abstraction syntax tree 
 * -----------------------------------------------------------------------------------------
*/
ast::ast(Vector<treeStructure>& expr_) {
    generateAst<ast> gA;
    if (user_choice.empty()) {
        // Subject to change. Have not decided if I want to compile the custom languyage or not
        ENABLE_COMPILER(); // set it to zero by default
        ENABLE_INTERPRETER(); // set it to one by default
        user_choice = "Custom";
    }
    else {
        table = initTable(languageExtensions, downloads); 
        auto getPair = table.at(user_choice);
        ext = getPair.first;
        if (auto search = languageTypes.find(user_choice); search != languageTypes.end()) {
            if (search->first == "Compiled") {
                settings = ENABLE_COMPILER(1); // Set it to true 
                ENABLE_INTERPRETER(0); // Set it to false
            }
            else {
                ENABLE_COMPILER(); // Set it to false
                ENABLE_INTERPRETER(); // Set it to true
            }
        }
    }
    compactedTreeNodes = std::move(expr_);
    try {
        //ThreadTracker<generateAst<ast>> createTree;
        if (settings) { 
            ThreadTracker<generateAst<ast>> createTree([&]() { gA.tree_(std::move(gA)); });
            createTree.detach(); // detach main
            analyzeSemantics aS(Shared<ast>(this)); // Create thread one
            analyzeSemantics* rawAS = &aS;
            intermediateRepresentation iR(Weak<analyzeSemantics>(Shared<analyzeSemantics>(rawAS,  [](analyzeSemantics*){}))); // Create thread two
            aS.detach(); // Detach one
            iR.detach(); // Detach two
            createTree.join(); // TODO: Haven't decided if I should detach or not... 
        }
        else {
            //createTree = std::thread(gA.tree_(std::move(gA)));
        }
    }
    catch(catcher<ast>& e) {
        std::cout << "Logs folder has been updated!" << std::endl;
        std::string temp = e.what();
        logging<generateAst<ast>> logs(logs_, temp); // Keep the logs updated throughout the whole codebase
        logs.update();
        logs.write();
        logs.rotate();
    }
}
/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/
void ast::writeFile(std::string& ext) {
    std::string Ast = "Ast.txt";
    std::ofstream fAst(Ast);
    fAst << compactedTreeStr;
    fAst.close();

    if (ext.empty()) { ext = std::string(".custom");}
    if (file_name.empty()) { file_name = std::string("change_name_please"); }
    std::ofstream fs(file_name + ext);
    fs << codeStr;
    fs.close();
    return;
}
/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/
void ast::tree_(const generateAst<ast>& gA)  {
    /*try {
        for (int i = 0; i < compactedTreeNodes.size(); i++) {
            auto temp = compactedTreeNodes.at(i); // Grab the tuple
            if (std::get<1>(temp).first == "Binary") {
                auto shr_binary = std::get<1>(temp).second; // Grabs the shared_ptr
                if (auto binary = std::get_if<Binary>(std::move(shr_binary.get()))) {
                    // TODO: Ast.txt must be created somewhere else and not here. It will interfere with the threading
                    //auto value = static_cast<Binary&&>(*binary).visit(static_cast<Binary&&>(*binary)); // create a temp object
                    //compactedTreeStr += static_cast<std::string>(std::move(value));
                    String lexeme = !binary->getToken().getLexeme().empty() ? binary->getToken().getLexeme() : "";
                    String literal = !binary->getToken().getLiteral().empty() ? binary->getToken().getLiteral() : "";
                    if (!lexeme.empty() && !literal.empty()) {
                        codeStr = lexeme + literal;
                        accessCodeStr = std::make_unique<Atomic<const char*>>(codeStr.c_str());
                    }
                }
            }
            else if (std::get<1>(temp).first == "Unary") {
                auto shr_unary = std::get<1>(temp).second; // Grabs the shared_ptr
                if (auto unary = std::get_if<Unary>(std::move(shr_unary.get()))) {
                    //auto value = static_cast<Unary&&>(*unary).visit(static_cast<Unary&&>(*unary)); // create a temp object
                    //compactedTreeStr += static_cast<std::string>(std::move(value));
                    String lexeme = !unary->getToken().getLexeme().empty() ? unary->getToken().getLexeme() : "";
                    String literal = !unary->getToken().getLiteral().empty() ? unary->getToken().getLiteral() : "";
                    if (!lexeme.empty() && !literal.empty()) {
                        codeStr = lexeme + literal;
                        accessCodeStr = std::make_unique<Atomic<const char*>>(codeStr.c_str());
                    }
                }
            }
            else if (std::get<1>(temp).first == "Grouping") {
                // Probably just need the lexeme and nothing more
                // But test if that is really the case
                auto shr_group = std::get<1>(temp).second; // Grabs the shared_ptr
                if (auto grouping = std::get_if<Grouping>(std::move(shr_group.get()))) {
                    //auto value = static_cast<Grouping&&>(*grouping).visit(static_cast<Grouping&&>(*grouping)); // create a temp object
                    //compactedTreeStr += static_cast<std::string>(std::move(value));
                    String lexeme = !grouping->getToken().getLexeme().empty() ? grouping->getToken().getLexeme() : "";
                    if (!lexeme.empty()) {
                        codeStr = lexeme;
                        accessCodeStr = std::make_unique<Atomic<const char*>>(codeStr.c_str());
                    }
                }
            }
            else if (std::get<1>(temp).first == "Literal") { 
                auto shr_literal = std::get<1>(temp).second; // Grabs the shared_ptr
                if (auto literal = std::get_if<Literal>(std::move(shr_literal.get()))) {
                    //auto value = static_cast<Literal&&>(*literal).visit(static_cast<Literal&&>(*literal)); // create a temp object
                    //compactedTreeStr += static_cast<std::string>(std::move(value));
                    String lexeme = !literal->getToken().getLiteral().empty() ? literal->getToken().getLiteral() : "";
                    if (!lexeme.empty()) {
                        codeStr = lexeme;
                        accessCodeStr = std::make_unique<Atomic<const char*>>(codeStr.c_str());
                    }
                }
            }
            else {
                catcher<ast> c("Unexpected behavior in ast!");
                throw c;
            }
        }
    } 
    catch (runtimeerror<ast>& e) {
        std::cout << "Logs have been updated!" << std::endl;
        //logging<ast> logs(logs_, e.what());
        //logs.update();
        //logs.rotate();
    }*/                           
    return writeFile(ext);
}


/** ----------------------------------------------------------------------------
 * @brief Maps the characters from the source code string to a semantic map.
 *
 * @param Ast_ Alias for the abstract syntax tree (AST) instance, which is moved to this class for analysis.
 *
 * @details Semantic analysis involves interpreting the source code and mapping idioms (expressions) 
 *          for further processing. Idioms represent meaningful expressions within the source code, 
 *          and are not necessarily sequences of literal words.
 *
 * @return None
 * -----------------------------------------------------------------------------
*/
analyzeSemantics::analyzeSemantics(Shared<ast> Ast_): ThreadTracker([this, Ast_]() { this->run(Ast_); }) {
    if (!getActiveThreads().empty()) {
        strToId["treeThread"] = std::move(getActiveThreads()[0]);
    }
}
/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/
intermediateRepresentation::intermediateRepresentation(Weak<analyzeSemantics> as_): ThreadTracker([this, as_]() { this->run(as_); }) {
    if (!getActiveThreads().empty()) {
        strToId["semanicThread"] = std::move(getActiveThreads()[1]);
    }
}
/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/
void intermediateRepresentation::adjacent(auto& G, int x, int y) { 
    // tests whether there is an edge from the vertex x to the vertex y;
}
/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/
void  intermediateRepresentation::neighbors(auto& G, int x) { 
    // lists all vertices y such that there is an edge from the vertex x to the vertex y;
}
/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/
void intermediateRepresentation::add_vertex(auto& G, int x) { 
    // adds the vertex x, if it is not there;
}
/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/

void intermediateRepresentation::remove_vertex(auto& G, int x) { 
    // removes the vertex x, if it is there;
}

/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/
void  intermediateRepresentation::add_edge(auto& G, int x, int y, int z) { 
    // adds the edge z from the vertex x to the vertex y, if it is not there;
}
/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/
void intermediateRepresentation::remove_edge(auto& G, int x, int y) { 
    // removes the edge from the vertex x to the vertex y, if it is there;
}
/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/
void intermediateRepresentation::get_vertex_value(auto& G, int x) { 
    // returns the value associated with the vertex x;
}
/** -------------------------------------------------------------------------
 * @brief Writes the code to target file
 *
 * @param ext Is an string object that is implicitly initalized with the targeted extension
 *
 * @return None
 *
 * --------------------------------------------------------------------------
*/
void intermediateRepresentation::set_vertex_value(auto& G, int x, int v) { 
    // sets the value associated with the vertex x to v.
}

