#include <tokens/token.h>

/*
 * (Token) is a default constructor is using list-initializing 
 */
Token::Token(TokenType type, std::string lexeme, const std::string literal, int line): type(this->type), lexeme(this->lexeme), literal(this->literal), line(this->line) {}


TokenType Token::getType() { return type; } 

std::string Token::getLexeme() { return lexeme; }

std::string Token::getLiteral() { return literal; }

int Token::getLine() { return line; }

