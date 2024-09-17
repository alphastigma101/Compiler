#include <language_specific_binary_operations.h>
#include <languages_types.h>
/** ----------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Is a method that calls in isNumeric, the helper function
 * 
 * @param expr: It is an place holder type object that references the abstraction syntax, (ast) that is currently being used. 
 *              In this case, it would be the Binary ast
 * @param left: Is a generic type that must have a concrete type during run time, and will visit the binary abstract syntax tree left side (lh)
 * @param right: Is a generic type that must have a concrete type during run time, and will visit the binary abstract syntax tree right side (rh)
 * 
 * @return True if a and b are equal. Otherwise, return false 
 * ----------------------------------------------------------------------------------------------------------------------------------------------------
*/
void binaryOperations::checkNumberOperands(auto& expr, auto& left, auto& right) {
    if ((isNumeric(left) == true) && (isNumeric(right) == true)) return;
    throw new runtimeerror(expr.op.getType(), "Operands must be numbers.");
}
/** -----------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Is a method that checks to see if one object equals the other
 * 
 * @param a: Is a fancy pointer that points to the object that is passed to at run time. 
 *           If not careful with this, it could lead to segfault
 * @param b: Is a fancy pointer that points to the object that is passed to at run time.
 *           If not careful with this, it could lead to segfault.
 * 
 * @return True if a and b are equal. Otherwise, return false 
 * 
 * -----------------------------------------------------------------------------------------------------------------------------------------------
*/
bool binaryOperations::isEqual(auto& a, auto& b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL) return false;
    return a.equals(b);
}
/** -----------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Is a method that checks to see if there is arithmetic operations
 * 
 * @param cl Is another enum type which represents what the user has chosen
 * @param expr: Is a fancy pointer that points to the object that is passed to at run time. 
 *           If not careful with this, it could lead to segfault
 * @param left: Is a fancy pointer that points to the object that is passed to at run time.
 *           If not careful with this, it could lead to segfault.
 * @param right Is a fancy pointer that points to the object that is passed to at run time.
 *           If not careful with this, it could lead to segfault.
 * 
 * @return True if a and b are equal. Otherwise, return false 
 * 
 * -----------------------------------------------------------------------------------------------------------------------------------------------
*/
auto binaryOperations::arithmeticOperations(auto& cl, auto& expr, auto& left, auto& right) -> auto {
    switch (expr->op->getType()) {
        case TokenType::PLUS:
            try {
                if ((isNumeric(left) == true) && (isNumeric(right) == true)) { return toNumeric(left) + toNumeric(right); }
                if ((isString(left) == true) && (isString(right) == true)) { return (std::string)left + (std::string)right; }
            }
            catch(runtimeerror& e) {
                std::cout << e.what() << std::endl;
                return NULL;
            }
            break;
        case TokenType::MINUS:
            try {if ((isNumeric(left) == true) && (isNumeric(right) == true)) { return toNumeric(left) - toNumeric(right); }}
            catch(runtimeerror& e) {
                std::cout << e.what() << std::endl;
                return NULL;
            }
            break;
        case TokenType::SLASH:
            try {if ((isNumeric(left) == true) && (isNumeric(right) == true)) { return toNumeric(left) / toNumeric(right); }}
            catch(runtimeerror& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        case TokenType::STAR:
            try { if ((isNumeric(left) == true) && (isNumeric(right) == true)) { return toNumeric(left) * toNumeric(right); }}
            catch(runtimeerror& e) {
                std::cout << e.what() << std::endl;
                return NULL;
            }
            break;
        case TokenType::GREATER:
            try {
                checkNumberOperands(expr->op, left, right);
                if ((isNumeric(left) == true) && (isNumeric(right) == true)) { return toNumeric(left) > toNumeric(right); }
            }
            catch(runtimeerror& e) {
                std::cout << e.what() << std::endl;
                return NULL;
            }
            break;
        case TokenType::GREATER_EQUAL:
            try {
                checkNumberOperands(expr->op, left, right);
                if ((isNumeric(left) == true) && (isNumeric(right) == true)) { return toNumeric(left) >= toNumeric(right); }
            } catch(runtimeerror& e) {
                std::cout << e.what() << std::endl;
                return NULL;
            }
        case TokenType::LESS:
            try {
                checkNumberOperands(expr->op, left, right);
                if ((isNumeric(left) == true) && (isNumeric(right) == true)) { return toNumeric(left) < toNumeric(right); }
            } catch(runtimeerror& e) {
                std::cout << e.what() << std::endl;
                return NULL;
            }
            break;
        case TokenType::LESS_EQUAL:
            try {
                checkNumberOperands(expr->op, left, right);
                if ((isNumeric(left) == true) && (isNumeric(right) == true)) { return toNumeric(left) <= toNumeric(right); }
            }
            catch(runtimeerror& e) {
                std::cout << e.what() << std::endl;
                return NULL;
            }
            break;
        case TokenType::BANG_EQUAL: return !isEqual(left, right);
        case TokenType::EQUAL_EQUAL: return isEqual(left, right);
        default: return NULL;
    }
}