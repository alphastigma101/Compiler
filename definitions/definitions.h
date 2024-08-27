#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_
#include <declarations.h>

template<>
struct currentType<LanguageTokenTypes> {
    void setTokenLanguage(const LanguageTokenTypes& value);
    LanguageTokenTypes getTokenLanguage();
    LanguageType<LanguageTokenTypes> currentLanguage;
};                                                                                

inline void currentType<LanguageTokenTypes>::setTokenLanguage(const LanguageTokenTypes& value) {
    currentLanguage = value;
};

inline LanguageTokenTypes currentType<LanguageTokenTypes>::getTokenLanguage() { return currentLanguage; };

template<typename T, typename U, typename V>
inline astTree<T, U, V> compressedAstTree(T first, U second, V third) {
    return std::make_tuple(first, std::make_pair(second, third));
};
#endif



