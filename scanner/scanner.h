#ifndef _SCANNER_H_
#define _SCANNER_H_
#include <token.h>
class Scanner {
    public:
        Scanner(std::string& Source);
        ~Scanner(){};
        std::vector<Token> ScanTokens();
    protected:
        void number();          
        void String(); 
        bool match(const char expected);
        void identifier();
        void addToken(const TokenType type, const std::string literal);
        void addToken(const TokenType type);
        void scanToken();
    private:
        std::string Source;
        std::vector<Token> tokens; 
        int start = 0;
        int current = 0;
        int line = 1;
        inline bool isAtEnd() { return current >= Source.length();}; 
        inline char advance() { return Source.at(current++); };
        inline bool isDigit(const char c) { return c >= '0' && c <= '9'; };
        inline bool isAlpha(const char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; };
        inline bool isAlphaNumeric(const char c) { return isAlpha(c) || isDigit(c); };
        inline char peek() {
            if (isAtEnd()) return '\0';
            return Source.at(current);
        };
        inline char peekNext() {
            if (current + 1 >= Source.length()) return '\0';
            return Source.at(current + 1);
        };
        static const std::unordered_map<std::string, TokenType> keywords;
};
#endif
