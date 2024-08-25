#pragma once
#ifndef _CONTEXT_FREE_GRAMMAR_H_
#define _CONTEXT_FREE_GRAMMAR_H_
#include <token.h>
#include <filesystem>
#include <stdexcept>
/*
 * A Context Free Grammar consists of a head and a body, which describes what it can generate.
 * The body's purest form will be a list of symbols and these symbols are:
    * (Terminal):
        * letter from the grammar’s alphabet, which you can think of it as a literal value. They are the endpoints in a sense as you only produce one symbol
    * (Nonterminal):
        * is a reference of another grammar rule, which allows you to pick any rules for it 
 * The rule is on the very left side of the ->. On the other side of it are: 
    * Quoted strings which represent the "terminal"
    * Lowercase letters that are  "nonterminal"
*/


namespace ContextFreeGrammar {
    template<typename Derived>
    class Expr  {
        /* ------------------------------------------------------------------------------------------
         * A representation of an abstraction classs which is also considered as a disoriented object
         * ------------------------(Additional Info Below)-------------------------------------------
         * By creating an abstraction class, and allowing a class to inherit it, you basically are allowing them to communicate with eachother
         * Which allows it to not be associated with any type of behavior which usually methods/functions etc are what defined the behavior of an object
         * ------------------------------------------------------------------------------------------
         */
        public:
            virtual ~Expr() noexcept = default;
            std::string accept(Expr& visitor) {
                return static_cast<Derived*>(this)->visit(std::move(static_cast<Derived&>(visitor)));
            };
            Expr* right;
            Expr* left;
            Token* op;
    };
    class Binary: public Expr<Binary> {
        /*
         * A class that represents a binary abstraction syntax tree
         * ------------------------(Additional Info Below)-------------------------------------------
         * The 'visiting design pattern' is crucial for the abstraction syntax tree to work as it will visit the nodes
         * It relies on recrusion to visit every node in a graph or tree 
         * ------------------------(Example of Ast Tree)---------------------------------------------
                  *
                 / \
                /   \
                -   ()
               /      \
              123      45.67
         * Would print out this: (* (- 123) (group 45.67)) Note: Parathesis are always included 
         */
        public:
            Binary(const Expr& left, const Token& op, const Expr& right): left(this->left), op(this->op), right(this->right){};
            ~Binary() {};
            inline std::string visit(Binary&& expr) {
                 std::string leftResult = expr.left->accept(*this);
                 std::string rightResult = expr.right->accept(*this);
                 return " " + leftResult + " " + rightResult;
            };
            inline Token getToken() {return op;};
        private:
            Expr* left;
            Expr* right;
            Token op;
    };
    class Unary: public Expr<Unary> {
        public:
            Unary(const Expr& right, const Token& op): right(this->right), op(this->op) {};
            ~Unary(){};
            inline std::string visit(Unary&& expr) {
                std::string rightResult = expr.right->accept(*this);
                return " " + rightResult;
            };
            inline Token getToken() {return op;};
        private:
            Expr* right;
            Token op;
    };
    class Grouping: public Expr<Grouping> {
        public:
            Grouping(const Expr& expression): expression(this->expression){};
            ~Grouping() noexcept {};
            inline std::string visit(Grouping&& expr) {
                std::string leftResult = expr.left->accept(*this);
                std::string rightResult = expr.right->accept(*this);
                return "(" + leftResult + " " + rightResult + ")";
            };
        private:
            Expr* expression;
    };
    class Literal: public MemberConv<Literal>, public Expr<Literal> {
        public:
            Literal(const auto& value): value(this->value){};
            ~Literal(){};
            inline std::string visit(Literal&& expr) {
                if (!expr.getValue().has_value()) return "nil";
                try {
                    // Cast the std::any to std::string
                    auto val = std::any_cast<std::string>(expr.toString());
                    return val;
                } catch (const std::bad_any_cast& e) {
                    //TODO: Logging needs to be implemented here
                    //log[].push_back("error: " + std::string(e.what()));
                    return "\0";
                }
                return "\0";
            };
            inline std::any toString() override {
                try {
                    return std::any_cast<std::string>(value);
                } 
                catch (const std::bad_any_cast& e) {
                    //TODO: Logging needs to be implemented here 
                    return "error: " + std::string(e.what());
                }
            };
            inline std::any getValue() {return value;};
        private:
            std::any value;
    };
};
using namespace ContextFreeGrammar;
#endif 
