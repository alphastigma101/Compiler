#pragma once
#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_
#include <utility>
#include <languages.h>
/**---------------------------------------------------------------------------
 * @brief Initialized in main.cc and is copy-initialized in abstraction_syntax_tree.cc
 * ---------------------------------------------------------------------------
*/
extern std::string user_choice; // get the user choice of language from the begining 
extern std::string file_name;
/**---------------------------------------------------------------------------
 * @brief Used in abstranction_tree_syntax.h
 * ---------------------------------------------------------------------------
*/
template<typename T, typename U, typename V>
using astTree = std::tuple<T, std::pair<U, V>>;
extern template struct std::tuple<int, std::pair<std::string, std::any>>;
/**---------------------------------------------------------------------------
 * @brief Used in parser.cc to initalize the tree 
 * ---------------------------------------------------------------------------
*/
template<typename T, typename U, typename V>
static astTree<T, U, V> compressedAstTree(T first, U second, V third);
//TODO: Make an expanded astTree struct. so something like: expandAstTree(T firstNode, U secondNode, V thirdNode, X fourthNode, W stringLiteral, Y ExprTypes)

/**---------------------------------------------------------------------------
 * @brief setTokenLanguage method is initialized in main.cc
 * getTokenLanguage is used in:
    * language_specific_binary_operations.h 
    * language_specific_truthy_operations.h 
    * language_specific_unary_operations.h
 * 
 *
 * ---------------------------------------------------------------------------
*/
template<typename T>
using LanguageType = T;
template<typename T>
extern LanguageType<T> currentLanguage; 
template<class T>
struct currentType;
template<typename T>
static void setTokenLanguage(const T& value);
template<typename T>
static T getTokenLanguage();
extern currentType<LanguageTokenTypes> ct;
/**---------------------------------------------------------------------------
 * @brief Defined in languages.cc 
 * ---------------------------------------------------------------------------
*/
extern languages type;
/**---------------------------------------------------------------------------
 * @brief static logger. It is used by every single concrete class that is avialable
 *
 * @detials Use grep -R 'logEntries' <root-path> replace root-path that will search through all the files that have logEntries  
 * ---------------------------------------------------------------------------
*/
template<typename T>
using logTable = T;
extern logTable<std::map<std::string, std::vector<std::string>>> logEntries;  // More descriptive of its purpose
/**---------------------------------------------------------------------------
 * @brief Used to create a specific file with a specific extension. Is used  by interpreter.cc 
 * ---------------------------------------------------------------------------
*/
typedef std::string Key;
typedef std::vector<std::string> Extension;
typedef std::vector<std::string> LanguageLinks;
typedef std::map<Key, std::pair<Extension, LanguageLinks>> Table;
const inline Table initTable(const std::unordered_map<std::string, std::vector<std::string>> languageExtensions, const std::unordered_map<std::string, std::string> downloads);

/**---------------------------------------------------------------------------
 * @brief defined in parser.h 
 *
 * ---------------------------------------------------------------------------
*/
namespace Parser {
    class parser;
};
//#include <definitions.cc> // Link the headers together
#endif 
