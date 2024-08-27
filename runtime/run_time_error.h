#ifndef _RUN_TIME_ERROR_H_
#define _RUN_TIME_ERROR_H_
#include <token.h>
namespace RunTimeError {
    template<class Type>
    class runtimeerror: public Token {
        public:
            // Constructor with token and message
            explicit runtimeerror(const auto& token, const std::string& message): token_(token), message_(message) {};

            // Default constructor
            runtimeerror() : token_(), message_("Unspecified runtime error") {};

            // Virtual destructor
            virtual ~runtimeerror() = default;

            // Get the error message
            virtual const char* what() const throw() { return message_.c_str(); };

            // Get the token associated with the error
            const Token& getToken() const { return token_; };
        private:
            Token token_;
            std::string message_;
    };
};
using namespace RunTimeError;
#endif

