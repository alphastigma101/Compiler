#pragma once
#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_
#include <utility>
#include <languages.h>
/** ------------------------------------------------------------------------
 * @brief Used to control the programs behavior based on the user choice of language
 *
 * @details setI and setC are declared in declarations.h and defined in definitions.h.
*/
static int setI(const int val...);
static int setC(const int val...); 
extern int settings;

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

//template<typename T>
//using Mutex = std::mutex<T>;


/** --------------------------------------------------------------------------
 * @brief Initialized in main.cc and is copy-initialized in abstraction_syntax_tree.cc
 * ---------------------------------------------------------------------------
*/
extern String user_choice; // get the user choice of language from the begining 
extern String file_name;
/** ---------------------------------------------------------------------------
 * @brief Used in abstranction_tree_syntax.h
 * -----------------Templates Objects-----------------------------------------
 * @detials 'InitializerListType' is represents a container type using an initializer list
 * @detials 'ListOfType' is an alias template to InitalizerListType
 * @detials 'externalList' is a external declare of a template variable
 * @detials 'ExprTypes' used alot in parser.cc 
 * ---------------------------------------------------------------------------
 *  ----------------Data structures------------------------------------------
 * @detials 'astTree' Represents a tree structure with a type T, a pair of type U and ListOfType<V>
 * ---------------------------------------------------------------------------
*/
template<typename... Derived>
using ExprTypes = Shared<Variant<Derived...>>;
template<typename T, typename U, typename V>
using astTree = std::tuple<T, std::pair<U, Shared<V>>>;
template<typename T, typename U, typename V>
static astTree<T, U, Shared<V>> compressedAstTree(T first, U second, V third);
//TODO: Make an expanded astTree struct. so something like: expandAstTree(T firstNode, U secondNode, V thirdNode, X fourthNode, W stringLiteral, Y ExprTypes)


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

/**---------------------------------------------------------------------------
 * @brief Defined in context_free_grammar.h
 *
 * @details This is a forward declaration which will be very useful for later on.
 *
 * --------------------------------------------------------------------------
*/
namespace ContextFreeGrammar {
    template<class Derived>
    class Expr;
    class Binary;
    class Unary;
    class Grouping;
    class Literal;
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


#endif 
