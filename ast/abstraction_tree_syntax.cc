#include <abstraction_tree_syntax.h>
#include <lookup_language.h> // get the file extensions 
/** ------------------------------------------------------------------
 * @brief this macro will be set to one if the executable that start with 'exec_debug_...' during compilation. Otherwise, will remain off
 *
*/
#if ENABLE_TESTING
    String file_name, user_choice;
    int settings;
#else 
    //std::cout << "Testing is enabled!" << std::endl;
#endif

// Define static members for generateAst
template<class T>
logTable<Map<String, Vector<String>>> generateAst<T>::logs_;
template<class T>
Vector<treeEntry> generateAst<T>::compactedTreeNodes;
template<class T>
String generateAst<T>::ext;
template<class T>
String generateAst<T>::codeStr;
template<class T>
String generateAst<T>::compactedTreeStr;

template struct std::tuple<int, std::pair<String, ExprVariant>>; // Explicit initialize the underyling of astTree type
Table ast::table;


/** -----------------------------------------------------------------------------------------
 * @brief The default constructor that calls in generateAst to start creating the .txt file 
 * 
 * @param expr: The data structure that represents the compacted abstraction syntax tree 
 * -----------------------------------------------------------------------------------------
*/
ast::ast(Vector<treeEntry>& expr_) {
    generateAst<ast> gA;
    String ext_;
    if (user_choice.empty()) {
        // Subject to change. Have not decided if I want to compile the custom languyage or not
        ENABLE_COMPILER(); // set it to zero by default
        ENABLE_INTERPRETER(); // set it to one by default
        user_choice = "Custom";
        // TODO: This shouldn't be here, but for now, it will be used for the test cases 
        catcher<ast> c("User is running a custom language!");
        throw c;
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
        generateAst<ast> gA;
        ext_ = ext;
        gA.tree_(std::move(gA));
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
    //codeStr += value.getLexeme();
    std::string Ast = "Ast.txt";
    std::ofstream fAst(Ast);
    fAst << compactedTreeStr;
    fAst.close();
    if (ext.empty() ) { 
        ext = std::string(".custom");
    }
    std::ofstream fs(file_name + ext);
    fs << codeStr;
    fs.close();
    return;
}

void ast::tree_(const generateAst<ast>& gA)  {
    try {
        for (int i = 0; i < compactedTreeNodes.size(); i++) {
           auto temp = compactedTreeNodes.at(i); // Grab the tuple
            if (std::get<1>(temp).first == "Binary") { 
                auto value = static_cast<Binary&&>(std::any_cast<Binary>(std::get<1>(temp).second)).visit(std::any_cast<Binary>(std::get<1>(temp).second));
                compactedTreeStr += std::any_cast<std::string>(std::move(value));
            }
            else if (std::get<1>(temp).first == "Unary") { 
                //auto value = static_cast<Unary&&>(std::any_cast<Unary>(std::get<1>(temp).second)).visit(std::any_cast<Unary>(std::get<1>(temp).second)); 
                //compactedTreeStr += std::any_cast<std::string>(std::move(value));
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
