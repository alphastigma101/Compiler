#ifndef _PARSER_H_
#define _PARSER_H_
#include <abstraction_syntax_tree.h> // includes context_free_grammar.h, token.h, languages.h

namespace Parser {
    class parseError {
        virtual ~parseError() = default;
        virtual void error(const Token token, const std::string message) = 0;                   
        virtual void report(const int line, const std::string where, const std::string message) = 0;
    };
    class parser: public parseError, public printAst, public {
        /* 
         * An object that represents a parser. 
         * To add more to the parser, you need to add the new rules to the existing grammar, and define it them inside the class field 
         * 
         */
        public:
            parser::parser(std::vector<Token> tokens): tokens(this->tokens){};
            parser::~parser(){};
        protected:
            // Current rules that were made from a grammar 
            Expr equality();
            Expr comparison();
            Expr expression();
            Expr term();
            Expr factor();
            Expr parse();
        private:
            int current = 0;
            final std::vector<Token> tokens;
            inline Token previous() {return tokens.at(current - 1);};
            inline Token peek() {return tokens.at(current);};
            inline boolean isAtEnd() {return peek().type == EOF;};
            inline Token advance() {
                if (!isAtEnd()) current++;
                return previous();
            };
            inline bool check(TokenType type) {
                if (isAtEnd()) return false;
                return peek().type == type;
            };
            inline bool match(std::vector<TokenType> types) {
                for (TokenType type : types) {
                    if (check(type)) {
                        advance();
                        return true;
                    }
                }
                return false;
            };
            inline Token consume(TokenType type, std::string message) {
                if (check(type)) return advance();
                throw error(peek(), message);
            };
            static void synchronize();
    };
};
using namespace Parser
#endif
