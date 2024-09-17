#ifndef COMPILER_H
#define COMPILER_H
#include <setjmp.h> // this will jump to executing the buffer                                                                                                                    
#include <bitset> // This allows the use of NOT, AND, XOR, or OR operators when combining bits
#include <abstraction_tree_syntax.h> // Include the AST

namespace Compiler {
    /** ----------------------------------------------------------------------
     * @brief A run time multi-layer layer compiler that compiles statically typed languages into byte code that will be later translated into machine code 
     *        the c++ compiler can understand.
     *
     * @details Uses the graph-structure that the intermediate representation created
     * @details During run-time/compiling phase, it will access a specific struct inside languages_types.h that the user choosed.
     *          To find out what type it is while traversing the graph, there is to possible approaches, while the second option is more promising:
     *              1. convert it using std::byte{} and compare the bytes with every avialable type inside the targeted struct 
     *              2. string match it by getting the lexeme via getLexeme() or manually convert the type from the struct into a string representation 
     *                 and do a rough match. Example: 
     *                      - list == List (this is a close match)
     *                      - List == List (Perfect match)
     *                      - foo == Bar   (Not a close match or a match)
     * -----------------------(Processing methods)----------------------------
     * @details if the token class instance's TokenType contain METHODS and DOT, the targeted struct must either contain another struct of somesort that has a 
     *          list of methods supported by a specific type. These methods must be declared and defined somewhere in the codebase, and must exactly match the type that was found
     *          after the matching phase.
     * @details Once the method has been found. It also must be converted into bytes representation and later on be translated into machine code
    */
    class compiler  {
        public:
            compiler(intermediateRepresentation& iR);
            ~compiler() noexcept = default;
        protected:
            /** -------------------------------------------------------------
             *
             * @brief Translate bytecode into a sequence of bits that can be used to represent data at a high level.
             *
             * @details You can use bitset along with to_ullong() so the assembly language can understand it to get a sequence of 1s and 0s
             * @details sizeof returns bytes that represent the object and must be times by eight
             *          The formula for such a thing is 1 byte = 8bits
             *
            */
            template<typename T>
            inline static std::bitset<sizeof(T) * 8> byteSize(T value) {
                auto temp = std::bitset<sizeof(T) * 8>(value);
                return std::move(temp).to_ullong();
            };
        private:
            inline static String machineCodeStr;

            
    };

};

using namespace Compiler;
#endif 
