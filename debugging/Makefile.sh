#!bin/bash 

INCLUDE="-I ../logging/ -I ../asm/ -I ../catch/ -I ../tokens/ -I ../languages/ -I ../interface/ -I ../ast/ -I ../cfg/ -I 
             ../declarations/ -I ../definitions/ -I ../runtime/ -I ../interpreter/ -I ../scanner/ -I ../parser/"
LDFLAFS=" -L $HOME/Public-Projects/logging -lgtest -lgtest_main -pthread"

#echo "creating debugging object files and executables"
#g++ -g -w -std=c++17 -fconcepts $INCLUDE  -c ../logging/logging.cc -o logging.o 
#g++ -g -std=c++17 -fconcepts $INCLUDE -c debug_logging.cc -o debug_logging.o
#g++ -g debug_logging.o logging.o -o exec_debug_logging
#echo "Creating test object files and executables"
#g++ -g -w -std=c++17 -fconcepts $INCLUDE  -c ../logging/logging.cc -o logging.o  
#g++ -g -std=c++17 -fconcepts $INCLUDE -c ../tests/test_logging.cc -o test_logging.o 
#echo "Linking the test object files together for the logger"
#g++ -g -std=c++17 test_logging.o logging.o -o test_logging $LDFLAFS


#echo "Creating debugging object files and executables"
g++ -g -std=c++17 -fconcepts $INCLUDE -c ../languages/languages.cc -o languages.o
#g++ -g -std=c++17 -fconcepts $INCLUDE -c debug_languages.cc -o debug_languages.o
#g++ -g -std=c++17 debug_languages.o languages.o -o exec_debug_languages
#g++ -g -std=c++17 -fconcepts $INCLUDE -c ../tests/test_languages.cc -o test_languages.o
#g++ -g -std=c++17 test_languages.o languages.o -o test_languages $LDFLAFS


echo "Creating debugging object files and executables for token"
g++ -g -std=c++17 -fconcepts $INCLUDE -c ../tokens/token.cc -o token.o
g++ -g -std=c++17 $INCLUDE -c debug_tokens.cc -o debug_tokens.o
g++ -g -std=c++17 token.o languages.o logging.o -o exec_debug_tokens
g++ -g -std=c++17 -fconcepts $INCLUDE -c ../tests/test_token.cc -o test_token.o 
g++ -g -std=c++17 test_token.o token.o languages.o logging.o -o test_tokens $LDFLAFS




#echo "Creating debuging object files and executables for scanner"
#g++ -g -std=c++17 -fconcepts $INCLUDE -c ../scanner/scanner.cc -o scanner.o
#g++ -g -std=c++17 $INCLUDE ../scanner/scanner.cc -o debug_scanner.o
#g++ -g -std=c++17 token.o languages.o logging.o debug_scanner.o -o exec_debug_scanner
#g++ -g -std=c++17 $INCLUDE ../tests/test_scanner.cc -o test_scanner.o
#g++ -g -std=c++17 token.o languages.o test_scanner.o logging.o -o test_scanner $LDFLAFS


#g++ -g -std=c++17 -fconcepts -I logging/ -I asm/ -I catch/ -I tokens/ -I languages/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ -I scanner/ -I parser/ -c languages/languages.cc -o languages/languages.o

# Create a file called debugging_languages.cc. Needs to be linked and compiled
#g++ -g -std=c++17 -fconcepts -I logging/ -I asm/ -I catch/ -I tokens/ -I languages/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ -I scanner/ -I parser/ -c scanner/scanner.cc -o scanner/scanner.o

# Create a file called debugging_scanner.cc Needs to be compiled and linked
#g++ -g -std=c++17 -fconcepts -I logging/ -I asm/ -I catch/ -I tokens/ -I languages/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ -I scanner/ -I parser/ -c ast/abstraction_tree_syntax.cc -o abstraction_tree_syntax.o
# Create a file called debugging_ast.cc needs to be compiled and linked

#g++ -g -std=c++17 -fconcepts -I logging/ -I asm/ -I catch/ -I tokens/ -I languages/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ -I scanner/ -I parser/ -c parser/parser.cc -o parser.o

# Create a file called debugging_parser.cc needs to be compiled and linked
#g++ -g -std=c++17 -fconcepts -I logging/ -I asm/ -I catch/ -I tokens/ -I languages/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ -I scanner/ -I parser/ -c interpreter/interpreter.cc -o interpreter.o


#g++ -g -std=c++17 -fconcepts -I logging/ -I asm/ -I catch/ -I tokens/ -I languages/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ -I scanner/ -I parser/ -c interpreter/language_specific_unary_operations.cc -o interpreter/language_specific_unary_operations.o
#g++ -g -std=c++17 -fconcepts -I logging/ -I asm/ -I catch/ -I tokens/ -I languages/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ -I scanner/ -I parser/ -c interpreter/language_specific_binary_operations.cc -o interpreter/language_specific_binary_operations.o

#g++ -g -std=c++17 -fconcepts -I logging/ -I asm/ -I catch/ -I tokens/ -I languages/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ -I scanner/ -I parser/ -c interpreter/language_specific_truthy_operations.cc -o interpreter/language_specific_truthy_operations.o
#g++ -g -std=c++17 -fconcepts -I logging/ -I asm/ -I catch/ -I tokens/ -I languages/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ -I scanner/ -I parser/ -c main.cc -o main.o
#echo "Buidling the executable exec_interpreter"
#g++ -g -std=c++17 -fconcepts -I ../logging/ -I ../asm/ -I ../catch/ -I ../tokens/ -I ../languages/ -I ../interface/ -I ../ast/ -I ../cfg/ -I ../declarations/ -I ../definitions/ -I ../runtime/ -I ../interpreter/ -I ../scanner/ -I ../parser/ logging.o token.o languages.o scanner.o abstraction_tree_syntax.o parser.o interpreter.o language_specific_unary_operations.o interpreter/language_specific_binary_operations.o interpreter/language_specific_truthy_operations.o main.o -o exec_interpreter
                                                               

# -----
#echo "Building executables for generate_code"
#g++ -g -std=c++17 -fconcepts -I ../logging/ -I ../asm/ -I ../catch/ -I ../tokens/ -I ../languages/ -I ../interface/ -I ../ast/ -I ../cfg/ -I ../declarations/ -I ../definitions/ -I ../runtime/ -I ../interpreter/ -I ../scanner/ -I ../parser/ -c ../generate_code.cc -o generate_code.o
# -----
#g++ -g -std=c++17 -fconcepts -I ../logging/ -I ../asm/ -I ../catch/ -I ../tokens/ -I ../languages/ -I ../interface/ -I ../ast/ -I ../cfg/ -I ../declarations/ -I ../definitions/ -I ../runtime/ -I ../interpreter/ -I ../scanner/ -I ../parser/ logging.o token.o languages.o scanner.o abstraction_tree_syntax.o parser.o language_specific_unary_operations.o language_specific_binary_operations.o language_specific_truthy_operations.o generate_code.o -o exec_generator

