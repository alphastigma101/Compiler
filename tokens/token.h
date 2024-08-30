#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <interface.h>
#include <catch.h>


class Token: public MemberConv<Token>, catcher<Token>  {
    public:
        /**
         * @brief default constructor is needed only for initialization, (Instantiation) of the member vairables
         *
         */
        explicit Token() = default;
        ~Token() noexcept = default;
        // Other Constructor
        explicit Token(const TokenType type, const std::string lexeme, const std::string literal, const int line);
        TokenType getType();
        std::string getLexeme();
        std::string getLiteral();
        int getLine();
        inline std::any toString() override {
            return std::make_any<std::string>(tokenTypeToString() + " " + lexeme + " " + literal);
        };
    protected:
        inline std::string tokenTypeToString() {
            auto it = tokenTypeStrings.find(type);
            if (it != tokenTypeStrings.end()) { return it->second;}
            throw catcher<Token>("Unknown TokenType");
        };
    private:
        TokenType type;
        std::string lexeme;
        std::string literal; 
        int line;
    };
#endif
