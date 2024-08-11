#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <stdexcept> // runtime_error can be used
#include <language_specific_unary_operations.h> // declares the Vistor template
#include <language_specific_binary_operations.h>
#include <language_specific_truthy_operations.h> 

namespace Interpreter {
    class RunTimeError: public std::runtime_error {
        // Class that represents a custom runtime_error object 
        public:
            final Token token;
            RuntimeError(Token& token, std::string& message): token(this->token), message(this->message){};
            ~RunTimeError(){};
        private:
            Token token;
            std::string message;
    };
    class interpreter: public unaryOperations, public binaryOperations, public isTruthyOperations, public RunTimeError {
        // A class object that visits Binary, Unary, Grouping, or Literal.
        public:
            interpreter(Vistor* expr, LanguageTypes& lang): expr(this->expr) lang(currentLanguage) {
                 try {
                     auto value = evaluate(expr);
                    //TODO: Add print debugging here 
                 } catch (RuntimeError& error) {}
            };
            ~interpreter(){};
            Visitor visitLiteralExpr(Visitor* expr) {return expr->value;};
            auto visitUnaryExpr(Visitor* expr);
            auto visitBinaryExpr(Visitor* expr);
        private:
            using Any = std::any; 
            Vistor* expr;
            bool isTruthy(Visitor* object);
            LanguageTypes currentLanguage;
        protected:
            inline auto evaluate(Visitor* expr) -> Visitor {return expr->accept(*this);};
    };
};
using namespace Interpreter;
#endif
