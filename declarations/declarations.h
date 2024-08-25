#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_
#include <tuple>
#include <utility>
#include <string>
#include <memory>
#include <any>
#include <iostream>
#include <variant>


// used in abstraction_syntax_tree.h
template<typename B, typename U, typename G, typename L>
using ExprTypes = std::variant<B, U, G, L>;
template<typename B, typename U, typename G, typename L>
extern ExprTypes<B, U, G, L>* expr;

template<typename T, typename U, typename V>
using astTree = std::tuple<T, std::pair<U, V>>;
// Declare the extern template for the underlying type  
extern template struct std::tuple<int, std::pair<std::string, std::any*>>;


template<typename T, typename U, typename V>
astTree<T, U, V> compressedAstTree(T first, U second, V third);
//TODO: Make an expanded astTree struct. so something like: expandAstTree(T firstNode, U secondNode, V thirdNode, X fourthNode, W stringLiteral, Y ExprTypes)


#endif 
