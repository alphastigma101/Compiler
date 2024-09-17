#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <language_specific_truthy_operations.h> 
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
            // Let the catcher and runtimeerror have access to the method what()
            friend class catcher<interpreter>;
            friend class runtimeerror<interpreter>;
            interpreter(Vector<treeStructure>&& expr, const LanguageTokenTypes lang);
            ~interpreter() noexcept = default;
            inline static std::any visitLiteralExpr(auto& expr) { return expr.getValue(); };
            std::any visitUnaryExpr(auto& expr);
            std::any visitBinaryExpr(auto& expr);
            inline static std::any visitGroupingExpr(auto& expr) { return evaluate(expr.expression); };
            inline static char* toString(std::any& left, std::any& right) {
                return NULL;
            };
            static void setExpr(const std::any& visitor);
        private:
            LanguageTokenTypes currentLanguage;
            inline static logTable<std::map<std::string, std::vector<std::string>>> logs_;
        protected:
            // temp is a representation of the class node ie Binary, Unary, Grouping, and literal
            // Cast temp the correct abstract type 
            // expr is a global variable: ExprTypes<Binary, Unary, Grouping, Literal>
            static String evaluate(ExprVariant& temp);
            inline static const char* what(const char* msg = runtimeerror<interpreter>::getMsg()) throw() {
                return msg;
            };

            inline static const char* what(TokenType&& type = runtimeerror<interpreter>::getType(), const char* msg = runtimeerror<interpreter>::getMsg()) throw() {
                return msg;
            };
    };
};
using namespace Interpreter;
#endif
