#pragma once
#ifndef _CONTEXT_FREE_GRAMMAR_H_
#define _CONTEXT_FREE_GRAMMAR_H_
#include <token.h>
#include <filesystem>

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
    class Expr: public std::filesystem::path  {
        /* ------------------------------------------------------------------------------------------
         * A representation of an abstraction classs which is also considered as a disoriented object
         * ------------------------(Additional Info Below)-------------------------------------------
         * By creating an abstraction class, and allowing a class to inherit it, you basically are allowing them to communicate with eachother
         * Which allows it to not be associated with any type of behavior which usually methods/functions etc are what defined the behavior of an object
         * ------------------------------------------------------------------------------------------
         */
        public:
            virtual ~Expr() = default;
            void accept(Expr& expr); // let the derived classes overload this method
            Expr* right;
            Expr* left;
            Token* op;
    };
    class Binary: public virtual Expr {
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
            Binary(Expr* left, Token op, Expr* right): left(this->left), right(this->right), op(this->op) {};
            ~Binary() {};
            void visit(Binary& expr) {
                 expr->left->accept(*this);
                 expr->right->accept(*this);
            };
            void accecpt(Binary& binary) { binary.visit(*this);};
        private:
            Expr* left;
            Expr* right;
            Token op;
    };
    class Unary: public virtual Expr {
        public:
            Unary(Expr* right, Token op): right(this->right) op(this->op){};
            ~Unary(){};
            void visit(Unary& expr) {
                expr->left->accept(*this);
                expr->right->accept(*this);
            };
            void accecpt(Unary& unary) {unary.vist(*this);};  
        private:
            Expr* right;
            Token op;
    };
    class Grouping: public virtual Expr {
        public:
            Grouping(Expr* expression): expression(this->expression) {};
            ~Grouping() {};
            void visit(Grouping& expr) {
                expr->left->accept(*this);
                expr->right->accept(*this);
            };
            void accept(Grouping& group) {group.visit(*this);};
        private:
            Expr* expression;
    };
    class Literal: public MemberConv, public virtual Expr {
        public:
            template<class Type>
            Literal(Type& value): value(this->value){};
            ~Literal(){};
            std::string visit(Literal& expr) {
                if (expr.value == NULL) return "nil";
                return expr.value.toString();
            };
            void accept(Literal& literal) {literal.visit(*this);};
            char * toString() override {
                static std::string cast = static_cast<std::string>(value);
                return &cast[0];
            };
        private:
            Type value;
    };
};
using namespace ContextFreeGrammar;
#endif 
