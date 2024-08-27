#ifndef _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#include <language_specific_unary_operations.h>
namespace TruthyOperations {
    class truthyOperations: public runtimeerror<truthyOperations>, public catcher<truthyOperations> {
        public:
            friend class interpreter;
            truthyOperations(){};
            ~truthyOperations() noexcept = default;
        private:
            bool isTruthy(auto& object);
    };
};
using namespace TruthyOperations;
#endif
