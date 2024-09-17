#ifndef _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#include <language_specific_unary_operations.h>
namespace TruthyOperations {
    class truthyOperations: public runtimeerror<truthyOperations> {
        public:
            friend class ::Interpreter::interpreter;
            truthyOperations() = default;
            ~truthyOperations() noexcept = default;
        private:
            bool isTruthy(auto& object);
            logTable<std::map<std::string, std::vector<std::string>>> logs_;
            cT* user_language;
        protected:
            inline static const char* what(const char* msg = catcher<truthyOperations>::getMsg()) throw() { return msg; }; 
    };
};
using namespace TruthyOperations;
#endif
