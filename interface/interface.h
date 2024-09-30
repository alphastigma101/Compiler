#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <definitions.h>
// TODO: Assembly will be added here eventually 
template<class Type>
class NonMemberConv {
    // An abstract class used for converting object types that are not a member object of the class 
    public:
        ~NonMemberConv() noexcept = default;
        inline std::any toNumeric(std::any& value) { return static_cast<Type*>(this)->toNumeric(value); };
        inline char* toString(std::any& left, std::any& right) { return static_cast<Type*>(this)->toString(left, right); };
};
template<class Type>
class Check {
    public:
        ~Check() noexcept = default;
        inline bool isNumeric(const std::any value) { return static_cast<Type*>(this)->isNumeric(value); };
        inline bool isString(const std::any value) {return static_cast<Type*>(this)->isString(value); };
};
template<class Type>
class MemberConv {
    // An abstract class is used to convert member types of a class object into a string 
    public:
        ~MemberConv() noexcept = default;
        inline std::any toString() { return static_cast<Type*>(this)->toString(); };
};
template<class Type>
class Visitor {
    public:
        inline String visit(Type&& visitor) { return static_cast<Type*>(this)->accept(*this); };
        inline String accept(Type& expr) { return static_cast<Type*>(this)->visit(std::move(expr)); };
        inline String parenthesize(String name, ContextFreeGrammar::Expr& expr) { return static_cast<Type*>(this)->parenthesize(name, expr); };
};
#endif 
