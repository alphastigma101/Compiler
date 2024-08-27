#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <definitions.h>
#include <assembly_visitor_access.h>
template<class Type>
class NonMemberConv {
    // An abstract class used for converting object types that are not a member object of the class 
    public:
        virtual ~NonMemberConv() noexcept = default;
        virtual std::any toNumeric(std::any& value) = 0;
        virtual char* toString(std::any& left, std::any& right) = 0; // TODO: Type signature needs to be changed to std::string which means everything that defines it also needs to be updated
};
template<class Type>
class Check {
    public:
        virtual ~Check() noexcept = default;
        virtual bool isNumeric(const std::any value) = 0; 
        virtual bool isString(const std::any value) = 0;
};
template<class Type>
class MemberConv {
    // An abstract class is used to convert member types of a class object into a string 
    public:
        virtual ~MemberConv() noexcept = default;
        virtual std::any toString() = 0;
};
#endif 
