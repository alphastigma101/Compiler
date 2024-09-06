#pragma once
#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_
#include <declarations.h>
/**---------------------------------------------------------------------------
 * @brief ...
 *
 * ---------------------------------------------------------------------------
*/
template<>
struct currentType<LanguageTokenTypes> {
    void setTokenLanguage(const LanguageTokenTypes& value);
    LanguageTokenTypes getTokenLanguage();
    LanguageType<LanguageTokenTypes> currentLanguage;
};                                                                                
/**---------------------------------------------------------------------------
 * @brief ...
 *
 * ---------------------------------------------------------------------------
*/
inline void currentType<LanguageTokenTypes>::setTokenLanguage(const LanguageTokenTypes& value) { currentLanguage = value; };
/**---------------------------------------------------------------------------
 * @brief ...
 *
 * ---------------------------------------------------------------------------
*/
inline LanguageTokenTypes currentType<LanguageTokenTypes>::getTokenLanguage() { return currentLanguage; };
/**---------------------------------------------------------------------------
 * @brief Custom function that creates a tuple for later use.
 * ----------------Generic Arguments-------------------------------------------
 * @param T: Is a type int to indicate the position of the tree (first)
 * @param U: The name of the node which is paired with a initializer_list (second)
 * @param V: Object type variants  (third)
 * --------------------Detials-------------------------------------------------
 * @detials The arguments are generic, therefore they can be reused with other types. Templates are more flexible than any 
*/
// Returns this type: tuple(int, string, shared_ptr(initializer_list(variant,variant)))
template<typename T, typename U, typename V>
astTree<T, U, V> compressedAstTree(T first, U second, InitializerListType<V> third) {
    return std::make_tuple(
        first,
        std::make_pair(
            second,
            std::make_shared<InitializerListType<V>>(third)
        )
    );
};
/**---------------------------------------------------------------------------
 * @brief ...
 *
 * ---------------------------------------------------------------------------
*/
const inline Table initTable(const std::unordered_map<std::string, std::vector<std::string>> languageExtensions, const std::unordered_map<std::string, std::string> downloads) {
    Table languageTable;
    for (auto it = languageExtensions.begin(); it != languageExtensions.end(); ++it) {
        const Key& key = it->first;
        const Extension& extension = it->second;
        auto downloadIt = downloads.begin();
        if (downloadIt != downloads.end()) {
            const LanguageLinks& Links{downloadIt->second};
            languageTable[key] = std::make_pair(extension, Links);
        }
    }
    return languageTable;
};
#endif
