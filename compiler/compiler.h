#ifndef COMPILER_H
#define COMPILER_H
#include <setjmp.h> // this will jump to executing the buffer                                                                                                                    
#include <bitset> // This allows the use of NOT, AND, XOR, or OR operators when combining bits
#include <abstraction_tree_syntax.h> // Include the AST
namespace Compiler {
    // Will be using the ast so it can be a intermediate representation, (IR) and compile it into machine code and output it
    // use the lexeme tokens to determine if the code wants to print or not
    class compile: public intermediateRepresentation, public bitset, public setjmp {
        // setjmp will jump to the buffer execute it 
        public:
            compile();
            ~compiler();
            
    };

};

using namespace Compiler;
#endif 
