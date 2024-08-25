#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <stdexcept> // runtime_error can be used
#include <language_specific_unary_operations.h> // declares the Vistor template
#include <language_specific_binary_operations.h>
#include <language_specific_truthy_operations.h> 

namespace Interpreter {
    template<class Type>
    class RunTimeError: public std::runtime_error {
        // Class that represents a custom runtime_error object 
        public:
            explicit RuntimeError(Token& token, std::string& message): token(this->token), message(this->message){};
            ~RunTimeError(){};
        private:
            Token token;
            std::string message;
    };
    class interpreter: public unaryOperations, public binaryOperations, public isTruthyOperations, public RunTimeError<interpreter> {
        // A class object that visits Binary, Unary, Grouping, or Literal.
        public:
            interpreter(std::vector<std::any>& expr, LanguageTypes& lang);
            ~interpreter() noexcept {};
            inline auto visitLiteralExpr(std::any& expr) -> std::any {return expr.value;};
            auto visitUnaryExpr(std::any& expr);
            auto visitBinaryExpr(std::any& expr);
            auto visitGroupingExpr(std::any& expr);
            auto visitLiteralExpr(std::any& expr);
        private:
            std::vector<std::any> expr;
            bool isTruthy(Visitor* object);
            LanguageTypes currentLanguage;
        protected:
            inline auto evaluate(std::any& expr) -> std::any {return expr.accept(*this);};
    };
};
using namespace Interpreter;
#endif
