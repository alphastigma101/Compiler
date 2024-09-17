#pragma once
#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_
#include <utility>
#include <any>
#include <cstdint>
#include <optional>
#include <variant>
#include <complex>
#include <functional>
#include <set>
#include <chrono>
#include <regex>
#include <time.h>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <list>
#include <deque>
#include <future>
#include <iostream>
#include <initializer_list>
#include <atomic>
#include <mutex>
#include <cstdarg>
#include <addon.h>
/** ------------------------------------------------------------------------
 * @brief Used to control the programs behavior based on the user choice of language
 *
 * @details setI and setC are declared in declarations.h and defined in definitions.h.
 *
 * -------------------------------------------------------------------------
*/
static int setI(const int val...);
static int setC(const int val...); 
extern int settings;
/** --------------------------------------------------------------------------
 * @brief All this alias templates are needed to avoid 
 *        using namespace std repetiviely which will make the code look more cleaner.
 * ---------------------------------------------------------------------------       
*/        
typedef std::string String;
template<typename K, typename V>
// Containers
using Map = std::map<K, V>;
template<typename K, typename V>
using Unordered = std::unordered_map<K, V>;
template<typename... T>
using Variant = std::variant<T...>;
template<typename T>
using Vector = std::vector<T>;
template<typename T>
// Pointers
using Shared = std::shared_ptr<T>;
template<typename T>
using Unique = std::unique_ptr<T>;
template<typename T>
using Weak = std::weak_ptr<T>;
// Threading/Atomic/Mutex
template<typename T>
using Atomic = std::atomic<T>;
template<typename T>
using Set = std::set<T>;
/** --------------------------------------------------------------------------
 * @brief Initialized in main.cc and is copy-initialized in abstraction_syntax_tree.cc
 * ---------------------------------------------------------------------------
*/
extern String user_choice;
extern String file_name;
/** ---------------------------------------------------------------------------
 * @brief Defined in context_free_grammar.h
 *
 * @details This is a forward declaration which will be very useful for later on.
 *
 * --------------------------------------------------------------------------
*/
namespace ContextFreeGrammar {
    template<class Derived>
    class VisitExpr;
    class Binary;
    class Unary;
    class Grouping;
    class Literal;
    class Methods;
    class Arguments;
    class EcoSystem;
};
/** --------------------------------------------------------------------------
 * @brief Used in context_free_grammar.h and in parser.cc
 *
 * @details Used immensly in parser.cc for recrusive parsing 
 * ---------------------------------------------------------------------------
*/
typedef std::variant<
    ContextFreeGrammar::Binary,
    ContextFreeGrammar::Unary,
    ContextFreeGrammar::Grouping,
    ContextFreeGrammar::Literal
> ExprVariant;
/** ---------------------------------------------------------------------------
 * @detials 'ExprTypes' used alot in parser.cc and context_free_grammar.h
 *                      Needed for returning multiple user defined class instances
 *
 * @brief Details that explain the custom data structures and there purpose
 *
 * @detials 'astTree' Represents a tree structure with a type T, a pair of type U and Shared<V>
 * @details 'Vertices' Known as nodes which represent the lines/links of a directed/undirected graph
 *                     It will use templates so it can be reused somewhere in the codebase if needed
 * @details 'Vertex' Known as the dot/point in a directed/undirected graph
 *                   It will use templates so it can be reused somewhere else in the codebase if needed
 * ---------------------------------------------------------------------------
*/
template<typename... Derived>
using ExprTypes = Shared<Variant<Derived...>>;
template<typename T, typename U, typename V>
using astTree = std::tuple<T, std::pair<U, Shared<V>>>;
template<typename T, typename U, typename V>
static astTree<T, U, Shared<V>> compressedAstTree(T first, U second, V third);
using treeStructure = astTree<int, String, ExprVariant>;
//template<typename X, typename Y, typename Z>
//using Vertices =
//template<typename X, typename Y, typename Z>
//using Vertex = std::tuple<

/** ---------------------------------------------------------------------------
 * @brief setTokenLanguage method is initialized in main.cc
 * @details getTokenLanguage is used in:
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
struct currentType;
template<typename T>
extern T currentLanguage;
template<typename T>
static void setTokenLanguage(const LanguageType<T>& value);
template<typename T>
static LanguageType<T> getTokenLanguage();
/**---------------------------------------------------------------------------
 * @brief static logger. It is used by every single concrete class that is avialable
 *
 * @detials Use grep -R 'logEntries' <root-path> replace root-path that will search through all the files that have logEntries  
 * ---------------------------------------------------------------------------
*/
template<typename T>
using logTable = T;
extern logTable<std::map<std::string, std::vector<std::string>>> logEntries; 
/**---------------------------------------------------------------------------
 * @brief Used to create a specific file with a specific extension. Is used  by interpreter.cc 
 * ---------------------------------------------------------------------------
*/
typedef std::map<String, std::pair<String, String>> Table;
static Table initTable(const Unordered<String, Vector<String>> languageExtensions, const Unordered<std::string, String> downloads);

/**---------------------------------------------------------------------------
 * @brief defined in parser.h 
 *
 * ---------------------------------------------------------------------------
*/
namespace Parser {
    template<class Derived>
    class parseError;
    class parser;
};
/** --------------------------------------------------------------------------
 * @brief A forward declaration of the namespace Interpreter
 * 
 * ---------------------------------------------------------------------------
*/
namespace Interpreter {
    class interpreter;
};



#endif 
