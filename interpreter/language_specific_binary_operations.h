#ifndef _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#include <logging.h> // includes declarations.h 
//#include <run_time_error.h> // To output tokentype and message
#include <catch.h> // To output the message of an unexcpected crash
namespace BinaryOperations {
    class binaryOperations: public Check<binaryOperations>, public catcher<binaryOperations>, public NonMemberConv<binaryOperations>, public runtimeerror<binaryOperations> {
        public:
            friend class ::Interpreter::interpreter;
            friend class runtimeerror<binaryOperations>;
            friend class catcher<binaryOperations>;
            // Default constructor
            binaryOperations() = default;
            ~binaryOperations() noexcept {};
            auto arithmeticOperations(auto& cl, auto& expr, auto& left, auto& right);
            bool isEqual(auto& a, auto& b);
        private:
            void checkNumberOperands(auto& expr, auto& left, auto& right);
            logTable<Map<String, Vector<String>>> logs_;
        protected:
            inline static const char* what(const char* msg = catcher<binaryOperations>::getMsg()) throw() { return msg; };
            inline static bool isString(const std::any value) { return value.type() == typeid(std::string);};
            /** ---------------------------------------------------------------
             * @brief isNumeric Is a helper function for (checkNumberOperands) and (checkNumberOperands)
             * 
             * @param Type: Is a generic type that must have a concrete type during run time
             *
             * @return True if the object at runtime is type: int, int64_t, float, double, etc.
                       Otherwise, return false
             * ----------------------------------------------------------------
            */
            inline static bool isNumeric(const std::any value) {
                // TODO: Need to add more supported types here. refer to languages_types.h
                return value.type() == typeid(int) ||
                       value.type() == typeid(int64_t) ||
                       value.type() == typeid(float) ||
                       value.type() == typeid(double);
            };
            /** -------------------------------------------------------------
             * @brief convert an any object into a numeric representation 
             *
             * @param value is a any object type that provides type safe checking
             * --------------------------------------------------------------
            */
            inline static std::any toNumeric(std::any& value) {
                try {
                    // explicit casting syntax is keywords<objec type>(user defined object)
                    if (value.type() == typeid(int)) return std::any_cast<int>(value);
                    else if (value.type() == typeid(int64_t)) return std::any_cast<int64_t>(value);
                    else if (value.type() == typeid(float)) return std::any_cast<float>(value);
                    else if (value.type() == typeid(double)) return std::any_cast<double>(value);
                    else {
                        catcher<binaryOperations> cbo("Error when converting object into a representable type in c++!");
                        throw cbo;
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
