#ifndef _RUN_TIME_ERROR_H
#define _RUN_TIME_ERROR_H
#include <token.h>
namespace RunTimeError {
    template<class Type>
    class runtimeerror {
        public:
            // Constructor with token and message
            explicit runtimeerror(const Token& token, const std::string& message): Token::Token(), token_(token), message_(message) {};

            // Default constructor
            runtimeerror() : token_(), message_("Unspecified runtime error") {};

            // Virtual destructor
            virtual ~runtimeerror() = default;

            // Get the error message
            virtual const char* what() const noexcept { return message_.c_str(); };

            // Get the token associated with the error
            const Token& getToken() const { return token_; };
        private:
            Token token_;
            std::string message_;
    };
};
using namespace RunTimeError;
#endif

