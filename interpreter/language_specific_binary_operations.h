#ifndef _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#include <catch.h>
#include <token.h>
#include <typeinfo>
class binaryOperations: public Check, public NonMemberConv<binaryOperations>, public virtual catcher {
    public:
        template<class Binary>
        auto arithmeticOperations(Binary* expr, Binary& left, Binary& right);
        bool isEqual(auto& a, auto& b);
    private:
        void checkNumberOperands(auto& expr, auto& left, auto& right);
        binaryOperations *b;
    protected:
        inline bool isString(const Type& value) override { return value.type() == typeid(std::string);};
};
#endif 
