#include <abstraction_tree_syntax.h>
#include <lookup_language.h> // get the file extensions 
// TODO: You need to check based on what the user types if the language needs to be interpreted or compiled 
// For example, python cannot be compiled it needs to be interpreted 

// Define static members
template<class T>
logTable<std::map<std::string, std::vector<std::string>>> generateAst<T>::logs_;
template<class T>
std::vector<treeEntry> generateAst<T>::compactedTreeNodes;
template<class T>
std::string generateAst<T>::ext;
template<class T>
std::string generateAst<T>::codeStr;
template<class T>
std::string generateAst<T>::compactedTreeStr;
// declare the global variables types here
std::string file_name, user_choice;
template<typename T>
struct std::tuple<int, std::pair<std::string, ExprTypes<ListOfType<T>>>>; // Explicit initialize the underyling of astTree type

/**-----------------------------------------------------------------------------------------
 * @brief The default constructor that calls in generateAst to start creating the .txt file 
 * 
 * @param expr: The data structure that represents the compacted abstraction syntax tree 
 * -----------------------------------------------------------------------------------------
*/
ast::ast(std::vector<treeEntry>& expr_) {
    generateAst<ast> gA;
    std::string ext_;
    if (file_name == "\0" || user_choice == "\0") {
        catcher<ast> c("User is running a custom language!");
        throw c;
    }
    else {
        auto pair = table.at(user_choice); // pair->first is the extensions, pair->ssecond is the download links for the program
        //ext = pair.first // TODO: THis needs to be fixed 
        setTable(languageExtensions, downloads);
    }
    //compactedTreeNodes = expr_;
    try {
        generateAst<ast> gA;
        ext = ext_;
        gA.tree_(gA);
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

void ast::writeFile(std::string& ext) {
    //codeStr += value.getLexeme();
    std::string Ast = "Ast.txt";
    std::ofstream fAst(Ast);
    fAst << compactedTreeStr;
    fAst.close();
    if (ext == "\0") { 
        ext = std::string(".custom");
    }
    std::ofstream fs(file_name + ext);
    fs << codeStr;
    fs.close();
    return;
}

void ast::tree_(const generateAst<ast>& gA)  {
    /*try {
        for (int i = 0; i < compactedTreeNodes.size(); i++) {
           auto temp = compactedTreeNodes.at(i);
            if (std::get<1>(temp).first == "Binary") { 
                //auto value = static_cast<Binary&&>(std::any_cast<Binary>(std::get<1>(temp).second)).visit(std::any_cast<Binary>(std::get<1>(temp).second));
                //compactedTreeStr += std::any_cast<std::string>(std::move(value));
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
    }*/                           
    return writeFile(ext);
}
