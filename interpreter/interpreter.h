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
            inline std::any visitLiteralExpr(auto& expr) { return expr.getValue(); };
            std::any visitUnaryExpr(auto& expr);
            std::any visitBinaryExpr(auto& expr);
            inline std::any visitGroupingExpr(auto& expr) { return evaluate(expr.expression); };
            inline char* toString(std::any& left, std::any& right) override {
                return NULL;
            };
        private:
            LanguageTokenTypes currentLanguage;
            std::vector<std::tuple<int, std::pair<std::string, std::any>>> expr;
        protected:
            inline auto evaluate(auto& expr) -> std::any {
                const std::type_info& ti = typeid(expr);
                if (ti == static_cast<const std::type_info&>(typeid(Expr<Binary>))) { 
                    auto binary = std::any_cast<Expr<Binary>&>(expr);
                    return binary.accept(binary);
                }
                else if (ti == static_cast<const std::type_info&>(typeid(Expr<Unary>))) { 
                    auto unary = std::any_cast<Expr<Unary>&>(expr);
                    return unary.accept(unary); 
                }
                else if (ti == static_cast<const std::type_info&>(typeid(Expr<Grouping>))) { 
                    auto grouping = std::any_cast<Expr<Grouping>&>(expr);
                    return grouping.accept(grouping); 
                }
                else if (ti == static_cast<const std::type_info&>(typeid(Expr<Literal>))) { 
                    auto literal = std::any_cast<Expr<Literal>&>(expr);
                    return literal.accept(literal); 
                }
                else { throw catcher<interpreter>("Unexpected type in evaluate function"); }
                return NULL;
            };
    };
};
using namespace Interpreter;
#endif
