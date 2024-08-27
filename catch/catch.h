#ifndef _CATCH_H_
#define _CATCH_H_
#include <exception>
template<class Type>
class catcher: public std::exception {
    public:
        explicit catcher() {};
        explicit catcher(const char* message): message(this->message) {};
        virtual const char* what() const throw() override { return message; };
        virtual ~catcher() = default;
    private:
        const char* message;
};
#endif
