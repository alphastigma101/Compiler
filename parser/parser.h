#ifndef _PARSER_H_
#define _PARSER_H_
/*--------------------------------------------------------------------------------------------------------------------------
 * This is the current grammar that parser.h, parser.cc, and abstraction_syntax_tree.cc and abstraction_syntax_tree.h use:
 * expression     → literal
               | unary
               | binary
               | grouping ;

   literal        → NUMBER | STRING | "true" | "false" | "nil" ;
   grouping       → "(" expression ")" ;
   unary          → ( "-" | "!" ) expression ;
   binary         → expression operator expression ;
   operator       → "==" | "!=" | "<" | "<=" | ">" | ">=" | "+"  | "-"  | "*" | "/" ;
 * --------------------------------------------------------------------------------------------------------------------------
 *  //TODO: enhance your parser by adding these features:
     *
     * 1. Function Calls:
     * expression → literal
     *            | unary
     *            | binary
     *            | grouping
     *            | function_call ;
     *
     * function_call → IDENTIFIER "(" argument_list ")" ;
     * argument_list → expression ("," expression)* ;
     *
     * 2. Variables:
     * expression → literal
     *            | unary
     *            | binary
     *            | grouping
     *            | function_call
     *            | variable
     *            | assignment ;
     *
     * variable     → IDENTIFIER ;
     * assignment   → IDENTIFIER "=" expression ;
     *
     * 3. Arrays:
     * expression → literal
     *            | unary
     *            | binary
     *            | grouping
     *            | function_call
     *            | variable
     *            | assignment
     *            | array
     *            | array_indexing ;
     *
     * array        → "[" (expression ("," expression)*)? "]" ;
     * array_indexing → expression "[" expression "]" ;
     *
     * 4. Member Access:
     * expression → literal
     *            | unary
     *            | binary
     *            | grouping
     *            | function_call
     *            | variable
     *            | assignment
     *            | array
     *            | array_indexing
     *            | member_access ;
     *
     * member_access → expression "." IDENTIFIER ;
     *
     * 5. Control Flow (if applicable):
     * statement  → expression
     *            | print_statement
     *            | if_statement
     *            | while_statement
     *            | block
     *            | return_statement ;
     *
     * print_statement → "print" expression ";" ;
     * if_statement    → "if" "(" expression ")" block ("else" block)? ;
     * while_statement → "while" "(" expression ")" block ;
     * block           → "{" (statement)* "}" ;
     * return_statement → "return" expression ";" ;
     *
     * 6. Logical Operators:
     * operator   → "==" | "!=" | "<" | "<=" | ">" | ">="
     *            | "+"  | "-"  | "*" | "/"
     *            | "and" | "or" ;
     *
     * Note: Consider managing operator precedence and associativity
     *       in your parsing logic to handle operator priority correctly.
 */

#include <abstraction_tree_syntax.h>
namespace Parser {
    template<class Type>
    class parseError: public Token {
        public:
            virtual ~parseError() = default;
            virtual std::string error(Token token, const std::string message) = 0;                   
            virtual std::string report(int line, const std::string where, const std::string message) const throw() = 0;
    };
    class parser: public parseError<parser> {
        /* ----------------------------------------------------------------------------------------------------------------------------
         * An object that represents a parser. 
         * To add more to the parser, you need to add the new rules to the existing grammar, and define it them inside the class field 
         * ----------------------------------------------------------------------------------------------------------------------------
         */
        public:
            parser(std::vector<Token>& tokens): tokens(this->tokens) {};
            ~parser() noexcept {};
            ExprTypes<Binary, Unary, Grouping, Literal>* expr;
            std::vector<std::tuple<int, std::pair<std::string, std::any>>> node;
            ExprTypes<Binary, Unary, Grouping, Literal>* parse();
        protected:
            // Current rules that were made from a grammar 
            ExprTypes<Binary, Unary, Grouping, Literal>* equality();
            ExprTypes<Binary, Unary, Grouping, Literal>* comparison();
            ExprTypes<Binary, Unary, Grouping, Literal>* expression();
            ExprTypes<Binary, Unary, Grouping, Literal>* term();
            ExprTypes<Binary, Unary, Grouping, Literal>* factor();
            ExprTypes<Binary, Unary, Grouping, Literal>* unary();
            ExprTypes<Binary, Unary, Grouping, Literal>* primary();     
        private:
            inline Token previous() { return tokens.at(current - 1); };
            inline Token peek() { return tokens.at(current); }; 
            inline bool isAtEnd() { return peek().getType() == TokenType::END_OF_FILE; };
            inline Token advance() {
                if (!isAtEnd()) current++;
                return previous();
            };
            inline void synchronize() {
                advance();
                while (!isAtEnd()) {                                                        
                    // TODO: Need to capture other boundaries that will simulate a new statement
                    // So instead of semicolons, other programming languages most likely do not use ; to indicate a new statement
                    if (previous().getType() == TokenType::SEMICOLON) return;               
                    switch (peek().getType()) {                                             
                        case TokenType::CLASS:                                              
                        case TokenType::FUN:                                                
                        case TokenType::VAR:                                                
                        case TokenType::FOR:                                                
                        case TokenType::IF:                                                 
                        case TokenType::WHILE:                                              
                        case TokenType::PRINT:                                              
                        case TokenType::RETURN:                                             
                        return;                                                             
                    }                                                                       
                    advance();
                }
            };
            int current = 0;
            int idx = 0;
            std::vector<Token> tokens;
            inline std::string error(Token token, const std::string message) override {
                if (token.getType() == TokenType::END_OF_FILE) { return report(token.getLine(), " at end", message);}
                return report(token.getLine(), " at '" + token.getLexeme() + "'", message);
            };
            inline std::string report(int line, const std::string where, const std::string message) const throw() override {
                std::string err = "[line " + std::to_string(line) + "] Error" + where +  ": " + message;
                std::cout << "[line " <<  line << "] Error" << where << ": " + message;
                return err;
            };
            inline bool check(const TokenType type) {
                if (isAtEnd()) return false;
                return peek().getType() == type;
            };
            template<typename... Args>
            inline bool match(Args... types) {
                for (auto &it: tokens) {
                    if (check(it.getType())) {
                        advance();
                        return true;
                    }
                }
                return false;
            };
            inline Token consume(const TokenType type, const std::string message) {
                if (check(type)) return advance();
                throw error(peek(), message);
            };
    };
};
using namespace Parser;
#endif
