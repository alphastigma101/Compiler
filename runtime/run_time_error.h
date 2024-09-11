#ifndef _RUN_TIME_ERROR_H_
#define _RUN_TIME_ERROR_H_
#include <token.h>
namespace RunTimeError {
    template<class Type>
    class runtimeerror {
        public:
            // Constructor with token and message
            explicit runtimeerror(const TokenType& type, const std::string& message): type_(type), message_(message) {};

            // Default constructor
            runtimeerror() : message_("Unspecified runtime error") {};

            // Virtual destructor
            virtual ~runtimeerror() = default;

            // Get the error message
            virtual const char* what() const throw() { return message_.c_str(); };

            // Get the token associated with the error
            const TokenType& getType() const { return type_; };
        private:
            TokenType type_;
            std::string message_;
    };
};
using namespace RunTimeError;
#endif

