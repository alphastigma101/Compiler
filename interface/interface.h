#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <declarations.h>

template<class Type>
class NonMemberConv {
    // An abstract class used for converting object types that are not a member object of the class 
    public:
        virtual ~NonMemberConv() = default;
        virtual std::any toNumeric(std::any& value) = 0;
        virtual char* toString(std::any& left, std::any& right) = 0;
};
template<class Type>
class Check {
    public:
        virtual ~Check() = default;
        virtual bool isNumeric(const std::any value) = 0; 
        virtual bool isString(const std::any value) = 0;
};
template<class Type>
class MemberConv {
    // An abstract class is used to convert member types of a class object into a string 
    public:
        virtual ~MemberConv() = default;
        virtual std::any toString() = 0;
};
#endif 
