all: exec_interpreter exec_generator exec_vm exec_new_parser_rules

# This allows me to declare each header with angle brackets around them to avoid multiple collisions 
DATABASE =: -I database/
PARSER =: -I parser/
TOKENS =: -I tokens/
INTERFACE =: -I interface/
INTERPRETER =: -I interpreter/
CFG =: -I cfg/
SCANNER =: -I scanner/
OPTIMIZATION =: -I optimization/
LANGUAGES =: -I languages/
AST =: -I ast/
COMPILER =: -I compiler/
VM =: -I vm/
CATCH =: -I catch/
LOGGING =: -I logging/

logging.o: $(LOGGING)
	g++ -std=c++17 $(LOGGING) -c logging/logging.c -o logging.o

languages.o: logging.o $(LANGUAGES) $(LOGGING)
	echo "Attempting to compile languages.cc"
	g++ -std=c++17 $(LANGUAGES) $(LOGGING) -c languages/languages.cc -o languages.o

token.o: logging.o languages.o $(TOKENS) $(INTERFACE) $(LOGGING)
	echo "Attempting to compile token.cc"
	g++ -std=c++17 $(TOKENS) $(LOGGING) $(INTERFACE) $(LANGUAGES) logging.o languages.o -c tokens/token.cc -o token.o 

ast.o: logging.o token.o languages.o $(AST) $(CFG) $(CATCH) $(INTERFACE)
	echo "Attempting to compile abstraction_syntax_tree.cc into an object file"
	g++ -std=c++17 $(INTERFACE) $(AST) $(CFG) $(CATCH) $(LOGGING) token.o languages.o logging.o -c ast/abstraction_syntax_tree.cc -o ast.o -fconcepts

parser.o: logging.o ast.o token.o languages.o $(TOKENS) $(CFG) $(LOGGING)
	g++ -std=c++17 $(TOKENS) $(CFG) ast.o token.o languages.o logging.o -c parser/parser.cc -o parser.o

scanner.o: logging.o token.o languages.o $(TOKENS) $(SCANNER)
	echo "Attempting to compile scanner.cc file into an object file"
	g++ -std=c++17 $(TOKENS) $(SCANNER) logging.o token.o languages.o -c scanner/scanner.cc -o scanner.o

binary.o: logging.o token.o $(INTERPRETER) $(LOGGING)
	g++ -std=c++17 $(INTERPRETER) $(LOGGING) logging.o token.o -c interpreter/language_specific_binary_operations.cc -o binary.o

unary.o: logging.o token.o $(INTERPRETER) $(LOGGING)
	g++ -std=c++17 $(INTERPRETER) logging.o token.o -c interpreter/language_specific_unary_operations.cc -o unary.o

truthy.o: logging.o token.o $(INTERPRETER) $(LOGGING)
	g++ -std=c++17 $(INTERPRETER) $(LOGGING) logging.o token.o -c interpreter/language_specific_truthy_operations.cc -o truthy.o

interp.o: token.o languages.o unary.o truthy.o binary.o
	g++ -std=c++17 $(INTERPRETER) token.o languages.o unary.o -c interpreter/interpreter.cc -o interp.o
	
main.o: main.cc scanner.o parser.o interp.o token.o ast.o
	g++ -std=c++17 $(SCANNER) $(PARSER) -c main.cc -o main.o

# Link object files to create executable 'exec_compiler', depends on scanner.o and main.o
exec_interpreter: scanner.o parser.o interp.o main.o ast.o 
	g++ -g -std=c++17 $(CFG) $(INTERFACE) scanner.o main.o ast.o interp.o parser.o -o exec_interpreter

compiler.o: ast.o $(AST) $(CFG) $(LANGUAGES) $(INTERFACE)
	g++ -std=c++17 $(AST) -c copmiler/compiler.cc -o compiler.o

generate_code.o: token.o ast.o parser.o generate_code.cc
	g++ -std=c++17 $(AST) $(CFG) $(LANGUAGES) $(PARSER) $(TOKENS) -c generate_code.cc -o gc.o

exec_generator: ast.o parser.o gc.o token.o
	g++ -g -std=c++17 parser.o ast.o gc.o token.o -o exec_generator 

config_virtual_machine.o: compiler.o ast.o token.o parser.o virtual_machine.cc vm.cc
	g++ -std=c++17 $(AST) $(CFG) $(LANGUAGES) $(PARSER) $(COMPILER) $(TOKENS) $(VM) -c vm/config_virtual_machine.cc -o config_vm.o

exec_vm: config_virtual_machine.o compiler.o parser.o ast.o token.o
	g++ -g -std=c++17 config_vm.o compiler.o parser.o ast.o token.o -o exec_vm 

rules.o: $(AST) $(PARSER)
	echo "Modify the parser_rules.cc iniside tests folder to test the new rules then copy them into parser.cc if successful"
	echo "Current rules will be generated in the form of a grammar and stored in a file called current_rules.txt"
	#g++ -std=c++17 

exec_new_parser_rules:
	echo "Using (Google Test Frame Work) to test parser"
	#g++ -std=c++17

# Clean up object files
clean:
	rm -rf *.o
