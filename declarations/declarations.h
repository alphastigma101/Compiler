#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_
#include <tuple>
#include <utility>
#include <string>
#include <memory>
#include <any>
#include <iostream>
#include <variant>
#include <assembly_visitor_access.h>
// Used in abstraction_syntax_tree.h
extern std::string user_choice; // get the user choice of language from the begining 
extern std::string file_name;

// used in abstraction_syntax_tree.h
template<typename B, typename U, typename G, typename L>
using ExprTypes = std::variant<B, U, G, L>;
template<typename B, typename U, typename G, typename L>
extern ExprTypes<B, U, G, L>* expr;

template<typename T, typename U, typename V>
using astTree = std::tuple<T, std::pair<U, V>>;
// Declare the extern template for the underlying type  
extern template struct std::tuple<int, std::pair<std::string, std::any>>;

// Used in parser.cc
template<typename T, typename U, typename V>
static astTree<T, U, V> compressedAstTree(T first, U second, V third);
//TODO: Make an expanded astTree struct. so something like: expandAstTree(T firstNode, U secondNode, V thirdNode, X fourthNode, W stringLiteral, Y ExprTypes)


// setTokenLanguage is used in main.cc 
// getTokenLanguage is used in language_specific_binary_operations.h, language_specific_truthy_operations.h, language_specific_unary_operations.h
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


#endif 
