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
 * @brief ...
 *
 * ---------------------------------------------------------------------------
*/
template<typename T, typename U, typename V>
inline astTree<T, U, V> compressedAstTree(T first, U second, V third) {
    return std::make_tuple(first, std::make_pair(second, third));
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
