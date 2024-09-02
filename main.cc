#include <scanner.h> // includes token.h, languages.h 
#include <parser.h> // includes abstraction_syntax_tree.h, context_free_grammar.h, token.h, languages.h
#include <interpreter.h> // includes: token.h, definitions.h, declarations.h, catch.h, runtimeerror.h  
#include <filesystem>
#include <system_error>
#include <fstream>
static bool hadError = false;
static LanguageTokenTypes interpretLanguage;
currentType<LanguageTokenTypes> ct;
/*
 * (run): Is a standalone static void function that runs the user input 
 * Parameters:
 * source: is a file that contains data of possibly of a language 
 */
static void run(std::string& source) {
    Scanner scanner(source); // Create a new scanner instance
    std::vector<Token> tokens = scanner.ScanTokens();
    ct.setTokenLanguage(interpretLanguage); // set the language
    parser parser_(tokens);
    parser_.parse();
    //TODO: Add threading here and thread the ast 
    // ast aT(parser_.node);
    //
    // ----- (No threading is needed below this line)
    interpreter interp(parser_.node, ct.getTokenLanguage());
    //expr = parser.parse();
    if (hadError) return;
}


LanguageTokenTypes user_language(const std::string& choice) {
    if (choice == "Python") return LanguageTokenTypes::Python;
    else if (choice == "JavaScript") return LanguageTokenTypes::JavaScript;
    else if (choice == "Ruby") return LanguageTokenTypes::Ruby;
    else if (choice == "C") return LanguageTokenTypes::C;
    else if (choice == "CPP" || choice == "C++") return LanguageTokenTypes::CPP;
    else if (choice == "Java") return LanguageTokenTypes::Java;
    else if (choice == "Go") return LanguageTokenTypes::Go;
    else if (choice == "Kotlin") return LanguageTokenTypes::Kotlin;
    else if (choice == "Swift") return LanguageTokenTypes::Swift;
    else if (choice == "Rust") return LanguageTokenTypes::Rust;
    else if (choice == "Haskell") return LanguageTokenTypes::Haskell;
    else if (choice == "CSharp" || choice == "C#") return LanguageTokenTypes::CSharp;
    else if (choice == "FSharp" || choice == "F#") return LanguageTokenTypes::FSharp;
    else if (choice == "ObjectiveC" || choice == "Objective-C") return LanguageTokenTypes::ObjectiveC;
    else if (choice == "VHDLVerilog" || choice == "VHDL/Verilog") return LanguageTokenTypes::VHDLVerilog;
    else if (choice == "Fortran") return LanguageTokenTypes::Fortran;
    else if (choice == "COBOL") return LanguageTokenTypes::COBOL;
    else if (choice == "Pascal") return LanguageTokenTypes::Pascal;
    else if (choice == "Ada") return LanguageTokenTypes::Ada;
    else if (choice == "Scala") return LanguageTokenTypes::Scala;
    else if (choice == "TypeScript") return LanguageTokenTypes::TypeScript;
    else if (choice == "Dart") return LanguageTokenTypes::Dart;
    else if (choice == "PHP") return LanguageTokenTypes::PHP;
    else if (choice == "Perl") return LanguageTokenTypes::Perl;
    else if (choice == "R") return LanguageTokenTypes::R;
    else if (choice == "Lua") return LanguageTokenTypes::Lua;
    else if (choice == "Shell" || choice == "Bash") return LanguageTokenTypes::Shell;
    else if (choice == "MATLAB") return LanguageTokenTypes::MATLAB;
    else if (choice == "VBA") return LanguageTokenTypes::VBA;
    else if (choice == "LISPScheme" || choice == "LISP" || choice == "Scheme") return LanguageTokenTypes::LISPScheme;
    else if (choice == "Groovy") return LanguageTokenTypes::Groovy;
    else if (choice == "Erlang") return LanguageTokenTypes::Erlang;
    else if (choice == "Clojure") return LanguageTokenTypes::Clojure;
    else if (choice == "Prolog") return LanguageTokenTypes::Prolog;
    else if (choice == "AWK") return LanguageTokenTypes::AWK;
    else if (choice == "TCL") return LanguageTokenTypes::TCL;
    else if (choice == "Julia") return LanguageTokenTypes::Julia;
    else if (choice == "PowerShell") return LanguageTokenTypes::PowerShell;
    else if (choice == "Racket") return LanguageTokenTypes::Racket;
    else if (choice == "Smalltalk") return LanguageTokenTypes::SmallTalk;
    else if (choice == "HTMLCSS" || choice == "HTML/CSS") return LanguageTokenTypes::HTMLCSS;
    else if (choice == "SQL") return LanguageTokenTypes::SQL;
    else if (choice == "LabVIEW") return LanguageTokenTypes::LabVIEW;
    else if (choice == "VisualBasic" || choice == "VB") return LanguageTokenTypes::VisualBasic;
    else if (choice == "Elm") return LanguageTokenTypes::Elm;
    else if (choice == "Eiffel") return LanguageTokenTypes::Eiffel;
    else if (choice == "StandardML" || choice == "SML") return LanguageTokenTypes::StandardML;
    else if (choice == "Dlang" || choice == "D") return LanguageTokenTypes::Dlang;
    else return LanguageTokenTypes::Custom;
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

static void report(int &line, std::string where, std::string& message) {
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
    const Table table = initTable(languageExtensions, downloads);
    if (argc > 2) {
        std::cout << "Supported languages" << std::endl;
        for (const std::pair<const std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>& it : table) { std::cout << it.first << std::endl; }
        std::cerr << "Usage: [script] [language]";
        exit(1); 
    }
    else {
        interpretLanguage = user_language((std::string)argv[2]);
        user_choice = (std::string)argv[2]; // user_choice comes from language_types.h
        file_name = (std::string)argv[1];
        runFile((std::string)argv[1]);
    } 
    else { runPrompt(); }
    return 0;
}
