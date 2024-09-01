#pragma once
#include <abstraction_tree_syntax.h>
#include <lookup_language.h>
template<>
std::string generateAst<ast>::ext;
template<>
logTable<std::map<std::string, std::vector<std::string>>> generateAst<ast>::logs_;
template<>
std::vector<std::tuple<int, std::pair<std::string, std::any>>> generateAst<ast>::expr;
template<>
void generateAst<ast>::writeFile(std::string& ext);
template<>
void generateAst<ast>::tree_();
/**-----------------------------------------------------------------------------------------
 * @brief The default constructor that calls in generateAst to start creating the .txt file 
 * 
 * @param expr: The data structure that represents the compacted abstraction syntax tree 
 * -----------------------------------------------------------------------------------------
*/
ast::ast(std::vector<std::tuple<int, std::pair<std::string, std::any>>>& expr_) {
    std::string ext;
    if (file_name == "\0" || user_choice == "\0") {
        catcher<generateAst<ast>> c("User is running a custom language!");
        throw c;
    }
    else {
        auto pair = table.at(user_choice); // pair->first is the extensions, pair->ssecond is the download links for the program
        //ext = pair.first // TODO: THis needs to be fixed 
        setTable(languageExtensions, downloads);
    }
    expr = expr_;
    try {
        generateAst<ast> gA;
        gA.ext = ext;
        gA.tree_();
    }
    catch(catcher<ast>& e) {
        std::cout << "Logs folder has been updated!" << std::endl;
        std::string temp = e.what();
        logging<Literal> logs(logs_, temp); // Keep the logs updated throughout the whole codebase
        logs.update();
        logs.write();
        logs.rotate();
    }
}

template<>
void generateAst<ast>::writeFile(std::string& ext) {
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

template<>
void generateAst<ast>::tree_()  {
    try {
        for (int i = 0; i < expr.size(); i++) {
            auto temp = expr.at(i);
            if (std::get<1>(temp).first == "Binary") { 
                auto value = static_cast<Binary&&>(std::any_cast<Binary>(std::get<1>(temp).second)).visit(std::any_cast<Binary>(std::get<1>(temp).second));
                compactedTreeStr += std::any_cast<std::string>(std::move(value));
            }
            else if (std::get<1>(temp).first == "Unary") { 
                auto value = static_cast<Unary&&>(std::any_cast<Unary>(std::get<1>(temp).second)).visit(std::any_cast<Unary>(std::get<1>(temp).second)); 
                compactedTreeStr += std::any_cast<std::string>(std::move(value));
            }
            else if (std::get<1>(temp).first == "Grouping") { 
                auto value = static_cast<Grouping&&>(std::any_cast<Grouping>(std::get<1>(temp).second)).visit(std::any_cast<Grouping>(std::get<1>(temp).second));
                compactedTreeStr += std::any_cast<std::string>(std::move(value));
            }
            else if (std::get<1>(temp).first == "Literal") { 
                auto value = static_cast<Literal&&>(std::any_cast<Literal>(std::get<1>(temp).second)).visit(std::any_cast<Literal>(std::get<1>(temp).second));
                compactedTreeStr += std::any_cast<std::string>(std::move(value));
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
