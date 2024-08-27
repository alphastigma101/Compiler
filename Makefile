# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -fconcepts
LDFLAGS := LDFLAGS = -L $(HOME)/Public-Projects/tests -lgtest -lgtest_main -pthread

# Include directories
INCLUDES := -I logging/ -I asm/ -I catch/ -I tokens/ \
            -I languages/ -I interface/ -I ast/ -I cfg/ \
            -I declarations/ -I definitions/ -I runtime/ -I interpreter/ \
            -I scanner/ -I parser/

# Source files for exec_interpreter
SRC_FILES_INTERPRETER := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                         ast/abstraction_tree_syntax.cc parser/parser.cc \
                         interpreter/interpreter.cc interpreter/language_specific_unary_operations.cc \
                         interpreter/language_specific_binary_operations.cc interpreter/language_specific_truthy_operations.cc \
                         main.cc

# Source files for exec_generator
SRC_FILES_GENERATOR := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                       ast/abstraction_tree_syntax.cc parser/parser.cc \
                       interpreter/language_specific_unary_operations.cc \
                       interpreter/language_specific_binary_operations.cc interpreter/language_specific_truthy_operations.cc \
                       generate_code.cc


SRC_FILES_TEST_TOKENS := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                         tests/test_token.cc

SRC_FILES_TEST_SCANNER := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                         tests/test_scanner.cc

SRC_FILES_TEST_AST := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                         ast/abstraction_tree_syntax.cc tests/test_ast.cc


SRC_FILES_TEST_PARSER := logging/logging.cc tokens/token.cc languages/languages.cc \
                         ast/abstraction_tree_syntax.cc parser/parser.cc \
                         tests/test_parser.cc

SRC_FILES_TEST_TRUTHY := logging/logging.cc tokens/token.cc languages/languages.cc \
                         interpreter/language_specific_truthy_operations.cc \
                         tests/test_truthy.cc

SRC_FILES_TEST_UNARY := logging/logging.cc tokens/token.cc languages/languages.cc \
                         interpreter/language_specific_unary_operations.cc \
                         tests/test_unary.cc

SRC_FILES_TEST_BINARY := logging/logging.cc tokens/token.cc languages/languages.cc \
                         interpreter/language_specific_binary_operations.cc \
                         tests/test_binary.cc

SRC_FILES_TEST_INTERPRETER := logging/logging.cc tokens/token.cc languages/languages.cc \
                         ast/abstraction_tree_syntax.cc interpreter/language_specific_unary_operations.cc \
                         interpreter/language_specific_binary_operations.cc interpreter/language_specific_truthy_operations.cc \
                         tests/test_interpreter.cc


# Object files for exec_interpreter
OBJ_FILES_INTERPRETER := $(patsubst %.cc, %.o, $(SRC_FILES_INTERPRETER))

# Object files for exec_generator
OBJ_FILES_GENERATOR := $(patsubst %.cc, %.o, $(SRC_FILES_GENERATOR))

# Executables
BINARIES := exec_interpreter exec_generator 
#exec_vm exec_new_parser_rules

# PHONY targets
.PHONY: all clean

# Default target
all: $(BINARIES)

# Build exec_interpreter
exec_interpreter: $(OBJ_FILES_INTERPRETER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Build exec_generator
exec_generator: $(OBJ_FILES_GENERATOR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Build exec_vm
#exec_vm: config_vm.o compiler.o parser.o ast.o token.o
	#$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Build exec_new_parser_rules
#exec_new_parser_rules:
	#echo "Using (Google Test Framework) to test parser"
	# Command to generate parser rules and store in current_rules.txt
	# $(CXX) $(CXXFLAGS) $(INCLUDES) -o exec_new_parser_rules

# Generic rule for compiling .cc to .o
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files and binaries
# Clean up object files and binaries
clean:
	rm -f $(patsubst %.cc,%.o,$(SRC_FILES_INTERPRETER) $(SRC_FILES_GENERATOR))
	rm -f $(BINARIES)
