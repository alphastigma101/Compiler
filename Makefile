# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -fconcepts

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

# Generic rule for compiling .cc to .o
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files and binaries
clean:
	rm -f $(OBJ_FILES_INTERPRETER) $(OBJ_FILES_GENERATOR) $(BINARIES)

