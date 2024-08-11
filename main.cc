#include <scanner.h> // includes token.h, languages.h 
#include <parser.h> // includes abstraction_syntax_tree.h, context_free_grammar.h, token.h, languages.h
#include <filesystem>
#include <system_error>
#include <fstream>
static bool hadError = false;
static std::any interpretLanguage;

/*
 * (run): Is a standalone static void function that runs the user input 
 * Parameters:
 * source: is a file that contains data of possibly of a language 
 */
static void run(const std::string& source) {
    Scanner scanner(source); // Create a new scanner instance
    d.setCode(source); // set the code 
    std::vector<Token> tokens = scanner.ScanTokens();
    Parser parser = new Parser(tokens);
    Expr expression = parser.parse();
    if (hadError) return;
}


LanguageTypes user_language(std::string& choice) {
    if (choice == "Python") return LanguageTypes::Python;
    else if (choice == "JavaScript") return LanguageTypes::JavaScript;
    else if (choice == "Ruby") return LanguageTypes::Ruby;
    else if (choice == "C") return LanguageTypes::C;
    else if (choice == "CPP" || choice == "C++") return LanguageTypes::CPP;
    else if (choice == "Java") return LanguageTypes::Java;
    else if (choice == "Go") return LanguageTypes::Go;
    else if (choice == "Kotlin") return LanguageTypes::Kotlin;
    else if (choice == "Swift") return LanguageTypes::Swift;
    else if (choice == "Rust") return LanguageTypes::Rust;
    else if (choice == "Haskell") return LanguageTypes::Haskell;
    else if (choice == "CSharp" || choice == "C#") return LanguageTypes::CSharp;
    else if (choice == "FSharp" || choice == "F#") return LanguageTypes::FSharp;
    else if (choice == "ObjectiveC" || choice == "Objective-C") return LanguageTypes::ObjectiveC;
    else if (choice == "VHDLVerilog" || choice == "VHDL/Verilog") return LanguageTypes::VHDLVerilog;
    else if (choice == "Fortran") return LanguageTypes::Fortran;
    else if (choice == "COBOL") return LanguageTypes::COBOL;
    else if (choice == "Pascal") return LanguageTypes::Pascal;
    else if (choice == "Ada") return LanguageTypes::Ada;
    else if (choice == "Scala") return LanguageTypes::Scala;
    else if (choice == "TypeScript") return LanguageTypes::TypeScript;
    else if (choice == "Dart") return LanguageTypes::Dart;
    else if (choice == "PHP") return LanguageTypes::PHP;
    else if (choice == "Perl") return LanguageTypes::Perl;
    else if (choice == "R") return LanguageTypes::R;
    else if (choice == "Lua") return LanguageTypes::Lua;
    else if (choice == "Shell" || choice == "Bash") return LanguageTypes::Shell;
    else if (choice == "MATLAB") return LanguageTypes::MATLAB;
    else if (choice == "VBA") return LanguageTypes::VBA;
    else if (choice == "LISPScheme" || choice == "LISP" || choice == "Scheme") return LanguageTypes::LISPScheme;
    else if (choice == "Groovy") return LanguageTypes::Groovy;
    else if (choice == "Erlang") return LanguageTypes::Erlang;
    else if (choice == "Clojure") return LanguageTypes::Clojure;
    else if (choice == "Prolog") return LanguageTypes::Prolog;
    else if (choice == "AWK") return LanguageTypes::AWK;
    else if (choice == "TCL") return LanguageTypes::TCL;
    else if (choice == "Julia") return LanguageTypes::Julia;
    else if (choice == "PowerShell") return LanguageTypes::PowerShell;
    else if (choice == "Racket") return LanguageTypes::Racket;
    else if (choice == "Smalltalk") return LanguageTypes::Smalltalk;
    else if (choice == "HTMLCSS" || choice == "HTML/CSS") return LanguageTypes::HTMLCSS;
    else if (choice == "SQL") return LanguageTypes::SQL;
    else if (choice == "LabVIEW") return LanguageTypes::LabVIEW;
    else if (choice == "VisualBasic" || choice == "VB") return LanguageTypes::VisualBasic;
    else if (choice == "Elm") return LanguageTypes::Elm;
    else if (choice == "Eiffel") return LanguageTypes::Eiffel;
    else if (choice == "StandardML" || choice == "SML") return LanguageTypes::StandardML;
    else if (choice == "Dlang" || choice == "D") return LanguageTypes::Dlang;
    else return NULL;
}

/* 
 * This function will implement > at runtime 
 */
static void runPrompt() {
     try {
         for (;;) { 
             std::cout << "> ";
             std::string line;
             std::getline(std::cin, line); // get user input
             if (line[0] == '\0' || line.empty()) break;
             run(line);
         }
    }
    catch(const std::system_error& e) {
        std::cout << "Caught system_error with code " "[" << e.code() << "] meaning " "[" << e.what() << "]\n";
    }
}

static void report(int &line, std::string& where, std::string& message) {
    std::cout << "[line " <<  line << "] Error" << where << ": " + message;
    hadError = true;
}

static void error(int& line, std::string& message) { report(line, "", message); }

static void runFile(const std::string& filePath) {
    std::string source,line;
    if (std::filesystem::exists(filePath)) {
        std::ifstream file (std::filesystem::path(filePath).stem());
        if (file.is_open()) { 
            while (std::getline(file, line)) {
                source.append(line);
            }
            file.close();
            run(source);
            // Indicate an error in the exit code.
            if (hadError) exit(1);
        }
    }
    else {
        std::cout << "Not a valid file" << std::endl;
        runPrompt();
    }
}


// This is the driver code
int main(int argc, char **argv) {
    const Table table = initTable();
    if (argc > 2) {
        std::cout << "Supported languages" << std::endl;
        for (const &it: table) { std::cout << it->first << std::endl; }
        std::cerr << "Usage: [script] [language]";
        exit(1); 
    }
    else if (argc == 2) {
        interpretLanguage = user_language((std::string)argv[2]);
        if (interpretLanguage != NULL) {
            user_choice = (std::string)argv[2]; // user_choice comes from language_types.h
        }
        else {throw std::runtime_error("Invalid Language!");}
        file_name = (std::string)argv[1];
        runFile((std::string)argv[1]);
    } 
    else { runPrompt(); }
    return 0;
}
