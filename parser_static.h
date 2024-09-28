#ifndef _PARSER_H_
#define _PARSER_H_
#include <abstraction_tree_syntax.h>
namespace Parser {
    template<class Derived>
    class parseError: public catcher<Derived> {
        public:
            friend class parser;
            explicit parseError<Derived>(const Token& t, const std::string& msg) {
                try {
                    token = std::move(t);
                    message = std::move(msg);
                }
                catch(...) {
                    
                }
            };
            ~parseError() = default;
            /** --------------------------------------------------------------------------------------
             * @brief A method that calls in the report method the error
             * -------------------------------------------------------------------------------------- 
            */
            inline std::string error() { return static_cast<Derived*>(this)->error();};
            /** --------------------------------------------------------------------------------------
             * @brief A method that calls in logging to store the error that occured
             * 
             * @param line: The line it occured 
             * @param where: The literal 
             * @param message: The error message
             * -------------------------------------------------------------------------------------- 
            */                   
            inline std::string report(int line, const std::string where, const std::string message) throw() {
                return static_cast<Derived*>(this)->report(line, where, message);
            };
        protected:
            parseError<Derived>() = default;
        private:
            inline static deepCopy<treeStructure> dc;
            inline static Token token;
            inline static std::string message;
    };
    class parser: public parseError<parser>, public logging<parser> {
        /** ----------------------------------------------------------------------------------------------------------------------------
         * @brief  object that represents a parser. 
         * @details To add more to the parser, you need to add the new rules to the existing grammar, and define it them inside the class field 
         * ----------------------------------------------------------------------------------------------------------------------------
        */
        public:
            friend class parseError;
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Copy constructor. You will need a default constructor if you want to inherit from this constructor
             * 
             * @param tokens: A vector that holds a list of Token instances
             * 
             * @details moves data over to tokens_  from tokens
             * ----------------------------------------------------------------------------------------------------------
            */
            explicit parser(std::vector<Token>& tokens) { 
                tokens_ = std::move(tokens); 
            };
            // Current rules that were made from a grammar 
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> equality();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> comparison();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> expression();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> term();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> factor();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> unary();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> primary();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> identifier();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> arguments();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> methods();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> ecosystem();
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> debug();
            ~parser() noexcept {};
            inline static Vector<deepCopy<treeStructure>> nodes;
            static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> parse();
            static void printNodes();
        protected:
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Get the previous TokenType
             * ----------------------------------------------------------------------------------------------------------
             */
            inline static Token previous() { return tokens_.at(current - 1); };
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Peek at the current TokenType.
             * ----------------------------------------------------------------------------------------------------------
             */
            inline static Token peek() { return tokens_.at(current); }; 
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Copy constructor. You will need a default constructor if you want to inherit from this constructor
             * ----------------------------------------------------------------------------------------------------------
             */
            inline static bool isAtEnd() { return peek().getType() == TokenType::END_OF_FILE; };
            /** ----------------------------------------------------------------------------------------------------------
             * @brief Advance the vector's iterator by one when it isn't at the end 
             * ----------------------------------------------------------------------------------------------------------
            */
            inline static Token advance() {
                if (!isAtEnd()) current++;
                return previous();
            };
             /** ----------------------------------------------------------------------------------------------------------
             * @brief Sync.
             * ----------------------------------------------------------------------------------------------------------
            */
            inline static void synchronize() {
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
            inline static bool check(const TokenType type) {
                if (isAtEnd()) return false;
                return peek().getType() == type;
            };
            /** --------------------------------------------------------------------------------------------------------------
             * @brief Calls in protected methods to match certain tokens. If a match exists, returns true. Otherwise, return false
             * ---------------------------------------------------------------------------------------------------------------
            */
            template<typename... Args>
            inline static bool match(Args... types) { 
                return (... || (check(types) ? (advance(), true) : false)); 
            };
            inline static Token consume(const TokenType type, const std::string message) {
                if (check(type)) return advance();
                parseError<parser> pp(peek(), message);
                throw pp;
            };
        private:
            inline static std::vector<Token> tokens_;
            inline static ExprTypes<Binary, Unary, Grouping, Literal, Methods, Arguments, EcoSystem> expr;
            inline static logTable<std::map<std::string, std::vector<std::string>>> logs_;
            inline static int current = 0;
            inline static int idx = 0;
            static std::string error();
            static std::string report(int line, const std::string where, const std::string message) throw();
    };
};
using namespace Parser;
#endif
