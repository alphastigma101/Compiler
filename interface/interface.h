#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <logging.h>
#include <assembly_visitor_access.h>
template<class Type>
class NonMemberConv {
    // An abstract class used for converting object types that are not a member object of the class 
    public:
        virtual ~NonMemberConv() noexcept = default;
        inline std::any toNumeric(std::any& value) { return static_cast<Type*>(this)->toNumeric(value); };
        inline char* toString(std::any& left, std::any& right) { return static_cast<Type*>(this)->toString(left, right); };
};
template<class Type>
class Check {
    public:
        virtual ~Check() noexcept = default;
        inline bool isNumeric(const std::any value) { return static_cast<Type*>(this)->isNumeric(value); };
        inline bool isString(const std::any value) {return static_cast<Type*>(this)->isString(value); };
};
template<class Type>
class MemberConv {
    // An abstract class is used to convert member types of a class object into a string 
    public:
        virtual ~MemberConv() noexcept = default;
        inline std::any toString() { return static_cast<Type*>(this)->toString(); };
};
#endif 
