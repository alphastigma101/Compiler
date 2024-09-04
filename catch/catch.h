#ifndef _CATCH_H_
#define _CATCH_H_
#include <exception>
template<class Type>
class catcher: public std::exception {
    public:
        explicit catcher() = default;
        explicit catcher(const char* message): message_(message) {};
        virtual const char* what() const throw() override { return message_; };
        virtual ~catcher() = default;
    private:
        const char* message_;
};
#endif
