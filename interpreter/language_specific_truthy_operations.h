#ifndef _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#include <language_specific_unary_operations.h>
namespace TruthyOperations {
    class truthyOperations: public runtimeerror<truthyOperations> {
        public:
            friend class interpreter;
            truthyOperations() = default;
            ~truthyOperations() noexcept {};
        private:
            bool isTruthy(auto& object);
            logTable<std::map<std::string, std::vector<std::string>>> logs_;
    };
};
using namespace TruthyOperations;
#endif
