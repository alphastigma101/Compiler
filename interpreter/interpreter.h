#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <language_specific_truthy_operations.h> 
#include <abstraction_tree_syntax.h>
/* ----------------------------------------------------------------------
 * This is how the headers are formatted:
 * expression     → literal
               | unary
               | binary
               | grouping ;
 * So that means binary will have to include the grouping header file 
*/

namespace Interpreter {
    class interpreter: public unaryOperations, public binaryOperations, public truthyOperations, public runtimeerror<interpreter>, public catcher<interpreter> {
        // A class object that visits Binary, Unary, Grouping, or Literal.
        public:
            interpreter(std::vector<std::tuple<int, std::pair<std::string, std::any>>>& expr, const LanguageTokenTypes lang);
            ~interpreter() noexcept = default;
            inline Literal visitLiteralExpr(Literal& expr) { return expr.getValue(); };
            Unary visitUnaryExpr(Unary& expr);
            Binary visitBinaryExpr(Binary& expr);
            Grouping visitGroupingExpr(Grouping& expr);
            char* toString(std::any& left, std::any& right) override {
                return NULL;
            };
        private:
            LanguageTokenTypes currentLanguage;
            std::vector<std::tuple<int, std::pair<std::string, std::any>>> expr;
        protected:
            inline auto evaluate(auto& expr) -> std::any {
                // Check if expr is an instance of Expr<Binary>
                if (expr.type() == typeid(Expr<Binary>)) { 
                    auto binary = std::any_cast<Expr<Binary>&>(expr);
                    return binary.accept(binary);
                }
                // Check if expr is an instance of Expr<Unary>
                else if (expr.type() == typeid(Expr<Unary>)) { 
                    auto unary = std::any_cast<Expr<Unary>&>(expr);
                    return unary.accept(unary); 
                }
                // Check if expr is an instance of Expr<Grouping>
                else if (expr.type() == typeid(Expr<Grouping>)) { 
                    auto grouping = std::any_cast<Expr<Grouping>&>(expr);
                    return grouping.accept(grouping); 
                }
                // Check if expr is an instance of Expr<Literal>
                else if (expr.type() == typeid(Expr<Literal>)) { 
                    auto literal = std::any_cast<Expr<Literal>&>(expr);
                    return literal.accept(literal); 
                }
                // If none of the above, throw an error or handle the unexpected type
                else { 
                    //throw catcher("Unexpected type in evaluate function");
                    
                }
                return NULL;
            };
    };
};
using namespace Interpreter;
#endif
