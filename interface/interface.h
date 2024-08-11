#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <any>
#include <iostream>
class NonMemberConv {
    // An abstract class used for converting object types that are not a member object of the class 
    public:
        virtual ~NonMemberConv() = default;
        virtual std::any toNumeric(std::any& value) = 0;
        virtual char* toString(std::any& left, std::any& right) = 0;
};

class Check {
    public:
        virtual ~Check() = default;
        virtual bool isNumeric(const std::any value) = 0; 
        virtual bool isString(const std::any value) = 0;
};

class MemberConv {
    // An abstract class is used to convert member types of a class object into a string 
    public:
        virtual ~MemberConv() = default;
        virtual std::any toString() = 0;
};
#endif 
