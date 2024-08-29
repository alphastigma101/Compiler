#ifndef _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#include <run_time_error.h>
#include <typeinfo>
namespace BinaryOperations {
    class binaryOperations: public Check<binaryOperations>, public catcher<binaryOperations>, public NonMemberConv<binaryOperations>, public runtimeerror<binaryOperations> {
        public:
            friend class interpreter;
            // Default constructor
            binaryOperations() = default;
            ~binaryOperations() noexcept {};
            auto arithmeticOperations(auto& expr, auto& left, auto& right);
            bool isEqual(auto& a, auto& b);
        private:
            void checkNumberOperands(auto& expr, auto& left, auto& right);
            logTable<std::map<std::string, std::vector<std::string>>> logs_;
        protected:
            inline bool isString(const std::any value) override { return value.type() == typeid(std::string);};
            /* -----------------------------------------------------------------------------
             * isNumeric Description:
                Is a helper function for (checkNumberOperands) and (checkNumberOperands)
             * Arguments:
                * Type: Is a generic type that must have a concrete type during run time
             * Returns:
                True if the object at runtime is type: int, int64_t, float, double, etc.
                Otherwise, return false
             * ----------------------------------------------------------------------------
            */
            inline bool isNumeric(const std::any value) override {
                // TODO: Need to add more supported types here. refer to languages_types.h
                return value.type() == typeid(int) ||
                       value.type() == typeid(int64_t) ||
                       value.type() == typeid(float) ||
                       value.type() == typeid(double);
            };
            /* ----------------------------
             *
             *
             *
             * ---------------------------
            */
            inline std::any toNumeric(std::any& value) override {
                try {
                    // explicit casting syntax is keywords<objec type>(user defined object)
                    if (value.type() == typeid(int)) return std::any_cast<int>(value);
                    else if (value.type() == typeid(int64_t)) return std::any_cast<int64_t>(value);
                    else if (value.type() == typeid(float)) return std::any_cast<float>(value);
                    else if (value.type() == typeid(double)) return std::any_cast<double>(value);
                    else {
                        throw catcher<binaryOperations>("Error when converting object into a representable type in c++!");
                    }
                }
                catch(catcher<binaryOperations>& e) {
                    std::cout << e.what() << std::endl;
                }
                return NULL;
            };
    };
};
using namespace BinaryOperations;
#endif 
