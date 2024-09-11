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
            void setExpr(const std::any& visitor);
        private:
            LanguageTokenTypes currentLanguage;
            std::vector<std::tuple<int, std::pair<std::string, std::any>>> expr;
            logTable<std::map<std::string, std::vector<std::string>>> logs_;
        protected:
            // temp is a representation of the class node ie Binary, Unary, Grouping, and literal
            // Cast temp the correct abstract type 
            // expr is a global variable: ExprTypes<Binary, Unary, Grouping, Literal>
            inline auto evaluate(auto& temp) -> std::any {
                const std::type_info& ti = typeid(temp);
                if (ti == static_cast<const std::type_info&>(typeid(Binary))) {
                    // check to see if place holder is Binary
                    auto binary = std::any_cast<Binary*>(temp);
                    auto exprBinaryPtr = std::any_cast<Expr<Binary>*>(temp);
                    return binary->accept(*exprBinaryPtr);
                }
                else if (ti == static_cast<const std::type_info&>(typeid(Unary))) { 
                    auto unary = std::any_cast<Unary*>(temp);
                    auto exprUnaryPtr = std::any_cast<Expr<Unary>*>(temp);
                    return unary->accept(*exprUnaryPtr); 
                }
                else if (ti == static_cast<const std::type_info&>(typeid(Grouping))) {
                    auto grouping = std::any_cast<Grouping*>(temp);
                    auto exprGroupingPtr = std::any_cast<Expr<Grouping>*>(temp);
                    return grouping->accept(*exprGroupingPtr); 
                }
                else if (ti == static_cast<const std::type_info&>(typeid(Literal))) { 
                    auto literal = std::any_cast<Literal*>(temp);
                    auto exprLiteralPtr = std::any_cast<Expr<Literal>*>(temp);
                    return literal->accept(*exprLiteralPtr); 
                }
                else { throw catcher<interpreter>("Unexpected type in evaluate function"); }
                return nullptr;
            };
    };
};
using namespace Interpreter;
#endif
