#include <interpreter.h>
#include <abstraction_syntax_tree.h>
/*
 *
 * 
 *
*/
interpreter(ExprTypes<Binary, Unary, Grouping, Literal>& expr, LanguageTypes& lang): expr(this->expr), lang(currentLanguage) {
    try {
        for (auto &it : expr) {
            if (std::get<1>(it).first == "Binary") { auto value = evaluate(std::get<1>(it).second); }
            else if (std::get<1>(it).first == "Unary") { auto value = evaluate(std::get<1>(it).second); }
            else if (std::get<1>(it).first == "Grouping") { auto value = evaluate(std::get<1>(it).second); }
            else if (std::get<1>(it).first == "Literal") { auto value = evaluate(std::get<1>(it).second); }
        }
        //TODO: Add print debugging here                            
    } catch (RuntimeError& error) {
        std::cout << error.what();
    }                               
}
/* -------------------------------------------------------------------------------------------------------------------------
 * visitUnaryExpr Description: 
    Is a method that visits the unary abstract syntax tree
 * Arguments:
    * Visitor: Is a generic type that must have a concrete type during run time and will visit the abstraction syntax tree
 * Returns:
    A Unary abstraction tree syntax node
 * -------------------------------------------------------------------------------------------------------------------------   
*/
auto interpreter::visitUnaryExpr(std::any& expr) -> std::any {
    auto right = evaluate(expr.right);
    switch (expr.op.getType()) {
        case TokenType::BANG:
            return !isTruthy(right);
        case TokenType::MINUS:
            switch(currentLanguage) {
                case LanguageTypes::Python:
                    return u-Python(LanguageTypes::Python, right);
                case LanguageTypes::JavaScript:
                    return u-JavaScript(LanguageTypes::JavaScript, right);
                case LanguageTypes::Ruby:
                    return u-Ruby(LanguageTypes::Ruby, right);
                case LanguageTypes::C:
                    return u-C(LanguageTypes::C, right);
                case LanguageTypes::CPP:
                    return u-CPP(LanguageTypes::CPP, right);
                case LanguageTypes::Java:
                    return u-Java(LanguageTypes::Java, right);
                case LanguageTypes::Go:
                    return u-Go(LanguageTypes::Go, right);
                case LanguageTypes::Kotlin:
                    return u-Kotlin(LanguageTypes::Kotlin, right);
                case LanguageTypes::Swift:
                    return u-Swift(LanguageTypes::Swift, right);
                case LanguageTypes::Rust:
                    return u-Rust(LanguageTypes::Rust, right);
                case LanguageTypes::CSharp:
                    return u-CSharp(LanguagesTypes::CSharp, right);
                case LanguageTypes::FSharp:
                    return u-FSharp(LanguageTypes::FSharp, right);
                case LanguageTypes::ObjectiveC:
                    return u-ObjectiveC(LanguageTypes::ObjectiveC, right);
                case LanguageTypes::Scala:
                    return u-Scala(LanguageTypes::Scala, right);
                case LanguageTypes::TypeScript:
                    return u-TypeScript(LanguageTypes::TypeScript, right);
                case LanguageTypes::Dart:
                    return u-Dart(LanguageTypes::Dart, right);
                case LanguageTypes::PHP:
                    return u-PHP(LanguageTypes::PHP, right);
                case LanguageTypes::R:
                    return u-R(LanguageTypes::R, right);
                case LanguageTypes::Lua:
                    return u-Lua(LanguageTypes::Lua, right);
                case LanguageTypes::MATLAB:
                    return u-MATLAB(LanguageTypes::MATLAB, right);
                case LanguageTypes::VBA:
                    return u-VBA(LanguageTypes::VBA, right);
                case LanguageTypes::Groovy: 
                    return u-Groovy(LanguageTypes::Groovy, right);
                case LanguageTypes::Julia:
                    return u-Julia(LanguageTypes::Julia, right);
                case LanguageTypes::PowerShell:
                    return u-PowerShell(LanguageTypes::PowerShell, right);
                case LanguageTypes::VisualBasic:
                    return u-VisualBasic(LanguageTypes::VisualBasic, right);
                case LanguageTypes::Dlang:
                    return u-Dlang(LanguageTypes::Dlang, right);
                case LanguageTypes::Haskell:
                    return u-Haskell(LanguageTypes::Haskell, right);
                case LanguageTypes::Erlang:
                    return u-Erlang(LanguageTypes::Erlang, right);
                case LanguageTypes::Clojure:
                    return u-Clojure(LanguageTypes::Clojure, right);
                case LanguageTypes::StandardML:
                    return u-StandardML(LanguageTypes::StandardML, right);
                case LanguageTypes::Elm:
                    return u-Elm(LanguageTypes::Elm, right);
                case LanguageTypes::VHDLVerilog:
                    return u-VHDLVerilog(LanguageTypes::VHDLVerilog, right);
                case LanguageTypes::Fortran:
                    return u-Fortran(LanguageTypes::Fortran, right);
                case LanguageTypes::COBOL:
                    return u-COBOL(LanguageTypes::COBOL, right);
                case LanguageTypes::Pascal:
                    return u-Pascal(LanguageTypes::Pascal, right);
                case LanguageTypes::Ada:
                    return u-Ada(LanguageTypes::Ada, right);
                case LanguageTypes::Perl:
                    return u-Perl(LanguageTypes::Perl, right);
                case LanguageTypes::AWK:
                    return u-AWK(LanguageTypes::AWK, right);
                case LanguageTypes::TCL:
                    return u-TCL(LanguageTypes::TCL, right);
                case LanguageTypes::Shell:
                    return u-Shell(LanguageTypes::Shell, right);
                case LanguageTypes::LISPScheme:
                    return u-LISPScheme(LanguageTypes::LISPScheme, right);
                case LanguageTypes::Racket:
                    return u-Racket(LanguageTypes::Racket, right);
                case LanguageTypes::Prolog:
                    return u-Prolog(LanguageTypes::Prolog, right);
                case LanguageTypes::Smalltalk:
                    return u-SmallTalk(LanguageTypes::SmallTalk, right);
                case LanguageTypes::HTMLCSS:
                    return u-HTMLCSS(LanguageTypes::HTMLCSS, right);
                case LanguageTypes::SQL:
                    return u-SQL(LanguageTypes::SQL, right);
                case LanguageTypes::LabVIEW:
                    return u-LabVIEW(LanguageTypes::LabVIEW, right);
                case LanguageTypes::Eiffel:
                    return u-Eiffel(LanguageTypes::Eiffel, right);
                case LanguageTypes::Custom:
                    // TODO: This needs to be redone
                    // This should be defined as a struct using templates for the objects to add flexibility 
                    return u-Custom(LanguageTypes::Custom, right);
                default:
                    throw std::runtime_error("Operand must be a number.");           
            }
        }
        throw std::runtime_error("Operand must be a number.");
    }
    // Unreachable.
    return NULL;
}
/* --------------------------------------------------------------------------------------------------------------------
 * visitBinaryExpr Description: 
    Is a method that visits the Binary abstraction syntax tree 
 * Arguments:
    * Visitor: Is a generic type that must have a concrete type during run time and the tree it will visit at run time
 * Returns:
    A Binary abstraction syntax tree node 
 * --------------------------------------------------------------------------------------------------------------------
*/
auto interpreter::visitBinaryExpr(std::any& expr) -> std::any {
    // In go, := makes a object. It must be represented in c++ as = 
    auto left = evaluate(expr.left);
    auto right = evaluate(expr.right);
    switch (currentLanguage) {
        case LanguageTypes::Python:
            if (arithmeticOperations(currentLanguage, expr, left, right) != NULL) {

            }
            break;
        case LanguageTypes::JavaScript:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Ruby:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::C:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::CPP:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Java:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Go:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Kotlin:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Swift:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Rust:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::CSharp:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::FSharp:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::ObjectiveC:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Scala:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::TypeScript:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Dart:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::PHP:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::R:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Lua:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::MATLAB:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::VBA:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Julia:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::PowerShell:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::VisualBasic:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Dlang:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Haskell:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Erlang:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Clojure:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::StandardML:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Elm:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::VHDLVerilog:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Fortran:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::COBOL:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Pascal:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Ada:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Perl:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::AWK:
            arithmeticOperations(currentLanguage, expr, left, right);
            //TODO: Add support for AWK
            break;
        case LanguageTypes::TCL:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Shell:
            throw std::runtime_error("Unary minus not supported in Shell");
        case LanguageTypes::LISPScheme:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Racket:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Prolog:
            throw std::runtime_error("Unary minus not supported in this context in Prolog");
        case LanguageTypes::Smalltalk:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::HTMLCSS:
           evaluateBinaryTokens(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::SQL:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::LabVIEW:
            throw std::runtime_error("Unary minus not applicable in this context");
        case LanguageTypes::Eiffel:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTypes::Custom:
            arithmeticOperations(currentLanguage, expr, left, right);
            // TODO: This needs to be redone
            // This should be defined as a struct using templates for the objects to add flexibility 
            break;
        default:
            throw RunTimeError("Operand must be a number.");           
    }
    // Unreachable.
    return NULL;
}
/* ---------------------------------------------------------------------------------------------------------
 * isTruthy Description: 
    Is a method that will return an concrete type if the language the user specifies supports truthy/falsy
 * Arguments:
    * Type: Is a generic type that must have a concrete type during run time
 * Returns:
    True if the object was successfully casted into a c++ supported type 
    Otherwise, return false 
 * ---------------------------------------------------------------------------------------------------------
*/
bool interpreter::isTruthy(const std::any& object) {
    switch(currentLanguage) {
        case LanguageTypes::Python:
            if (std::any_cast<LanguageTypes::Python::None>(&object) != nullptr) return false;
            if (auto b = std::any_cast<LanguageTypes::Python::Bool>(&object)) return *b;
            break;
        case LanguageTypes::JavaScript:
            if (std::any_cast<LanguageTypes::JavaScript::Null>(&object) != nullptr) return false;
            if (std::any_cast<LanguageTypes::JavaScript::Undefined>(&object) != nullptr) return false;
            if (auto b = std::any_cast<LanguageTypes::JavaScript::Boolean>(&object)) return *b;
            break;
        //TODO: handle other languages here
    }
    return true;
}

