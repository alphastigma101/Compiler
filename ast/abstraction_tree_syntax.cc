#include <abstraction_tree_syntax.h>
#include <lookup_language.h> // get the file extensions 
template struct std::tuple<int, std::pair<String, ExprVariant>>; // Explicit initialize the underyling of astTree type

/** ------------------------------------
 * @brief An abstraction class that checks to see if it allowed to create a .txt flie
 * 
 * --------------------------------------
 */
template<>
generateAst<ast>::generateAst() {
    // TODO: SegFault Occurs on Line 13
    std::filesystem::path pp = std::filesystem::path(getenv("Private-Projects"));
    // Check if the path exists and is in user space
    if (std::filesystem::exists(pp)) {
        auto hasPermission = [&](std::filesystem::perms perm) {
            auto perms = std::filesystem::status(pp).permissions();
            return (perms & perm) == perm;
        };
        // Check if we have write permissions
        if (hasPermission(std::filesystem::perms::owner_write) && hasPermission(std::filesystem::perms::owner_read)) {
            // Set the outputDir
            outputDir_ = std::move(pp);
        } else { 
            catcher<generateAst<ast>> c("Failed to set the default path to write the ast to aka the file!");
            throw c;
        }
    }
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
            createTree.detach(); // detach it
            analyzeSemantics aS(Shared<ast>(this)); // Create thread one 
            aS.detach(); // Detach it so it works on it's own 
            //intermediateRepresentation iR(std::make_shared<analyzeSemantics>(aS));
            //t.join();
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
    try {
        for (int i = 0; i < compactedTreeNodes.size(); i++) {
            auto temp = compactedTreeNodes.at(i); // Grab the tuple
            if (std::get<1>(temp).first == "Binary") {
                auto shr_binary = std::get<1>(temp).second; // Grabs the shared_ptr
                if (auto binary = std::get_if<Binary>(std::move(shr_binary.get()))) {
                    auto value = static_cast<Binary&&>(*binary).visit(static_cast<Binary&&>(*binary)); // create a temp object
                    compactedTreeStr += static_cast<std::string>(std::move(value));
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
                    auto value = static_cast<Unary&&>(*unary).visit(static_cast<Unary&&>(*unary)); // create a temp object
                    compactedTreeStr += static_cast<std::string>(std::move(value));
                    String lexeme = !unary->getToken().getLexeme().empty() ? unary->getToken().getLexeme() : "";
                    String literal = !unary->getToken().getLiteral().empty() ? unary->getToken().getLiteral() : "";
                    if (!lexeme.empty() && !literal.empty()) {
                        codeStr = lexeme + literal;
                        accessCodeStr = std::make_unique<Atomic<const char*>>(codeStr.c_str());
                    }
                }
            }
            else if (std::get<1>(temp).first == "Grouping") { 
                //auto value = static_cast<Grouping&&>(std::any_cast<Grouping>(std::get<1>(temp).second)).visit(std::any_cast<Grouping>(std::get<1>(temp).second));
                //compactedTreeStr += std::any_cast<std::string>(std::move(value));
            }
            else if (std::get<1>(temp).first == "Literal") { 
                //auto value = static_cast<Literal&&>(std::any_cast<Literal>(std::get<1>(temp).second)).visit(std::any_cast<Literal>(std::get<1>(temp).second));
                //compactedTreeStr += std::any_cast<std::string>(std::move(value));
            }
            else {
                catcher<generateAst<ast>> c("Unexpected behavior in ast!");
                throw c;
            }
        }
    } 
    catch (runtimeerror<generateAst<ast>>& e) {
        std::cout << "Logs have been updated!" << std::endl;
        logging<generateAst<ast>> logs(logs_, e.what());
        logs.update();
        logs.rotate();
    }                           
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
        strToId["semanticThread"] = std::move(getActiveThreads()[1]); // tree_() is the main thread so move the element out 
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
intermediateRepresentation::intermediateRepresentation(Shared<analyzeSemantics> as_): ThreadTracker([this, as_]() { this->run(as_); }) {}
