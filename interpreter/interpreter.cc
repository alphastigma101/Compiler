#include <interpreter.h>
#include <abstraction_tree_syntax.h>
/*
 *
 * 
*/
interpreter::interpreter(Vector<treeStructure>&& expr, const LanguageTokenTypes lang): currentLanguage(lang) {
    String value;
    try {
        for (int i = 0; i < expr.size(); i++) {
            auto temp = expr.at(i);
            if (std::get<1>(temp).first == "Binary") {
                auto binaryU = std::get<1>(temp).second;
                if (binaryU != nullptr) {
                    value = evaluate(*binaryU); 
                }
                /*else if (std::get<1>(temp).first == "Unary") { 
                    value = evaluate(std::get<1>(temp).second.get()); 
                }
                else if (std::get<1>(temp).first == "Grouping") { 
                     value = evaluate(std::get<1>(temp).second.get()); 
                }
                else if (std::get<1>(temp).first == "Literal") { 
                    value = evaluate(std::get<1>(temp).second.get()); 
                }
                else {
                    try {
                        catcher<interpreter> ci("Error, could not find node!");
                        throw ci;
                    }
                    catch(runtimeerror<interpreter>& e) {
                        std::cout << "Logs have been updated!" << std::endl;
                        //logging<interpreter> logs(logs_, e.what());
                        //logs.update();
                        //logs.rotate();
                    }
                }*/
            }
        }
    } catch (catcher<interpreter>& e) {
        std::cout << "Logs have been updated!" << std::endl;
        logging<interpreter> logs(logs_, e.what());
        logs.update();
        logs.rotate();
    }                              
}
String interpreter::evaluate(ExprVariant& temp) {
    const std::type_info& ti = typeid(temp);
    if (ti == static_cast<const std::type_info&>(typeid(Binary))) {
        // check to see if place holder is Binary
        auto binary = std::get_if<Binary>(&temp);
        return binary->accept(*binary);
    }
    /*else if (ti == static_cast<const std::type_info&>(typeid(Unary))) { 
        auto unary = std::any_cast<Unary*>(temp);
        auto exprUnaryPtr = std::any_cast<VisitExpr<Unary>*>(temp);
        return unary->accept(*exprUnaryPtr); 
    }
    else if (ti == static_cast<const std::type_info&>(typeid(Grouping))) {
        auto grouping = std::any_cast<Grouping*>(temp);
        auto exprGroupingPtr = std::any_cast<VisitExpr<Grouping>*>(temp);
        return grouping->accept(*exprGroupingPtr); 
    }
    else if (ti == static_cast<const std::type_info&>(typeid(Literal))) { 
        auto literal = std::any_cast<Literal*>(temp);
        auto exprLiteralPtr = std::any_cast<VisitExpr<Literal>*>(temp);
        return literal->accept(*exprLiteralPtr); 
    }*/
    else { throw catcher<interpreter>("Unexpected type in evaluate function"); }
    return nullptr;
}

/* ---------------------------------------------------------------------------
 * @brief A method that visits the unary abstract syntax tree
 * @param right: Is a fancy pointer that will point to Expr<Unary> at run time.
 * @return A Unary abstraction tree syntax node in the form of a string 
 * ---------------------------------------------------------------------------
*/
std::any interpreter::visitUnaryExpr(auto& expr) {
    auto right = evaluate(expr.right);
    switch (right.op.getType()) {
        case TokenType::BANG:
            return !isTruthy(right);
        case TokenType::MINUS:
            switch(currentLanguage) {
                case LanguageTokenTypes::Python:
                    return uPython(LanguageTokenTypes::Python, right);
                case LanguageTokenTypes::JavaScript:
                    return uJavaScript(LanguageTokenTypes::JavaScript, right);
                case LanguageTokenTypes::Ruby:
                    return uRuby(LanguageTokenTypes::Ruby, right);
                case LanguageTokenTypes::C:
                    return uC(LanguageTokenTypes::C, right);
                case LanguageTokenTypes::CPP:
                    return uCPP(LanguageTokenTypes::CPP, right);
                case LanguageTokenTypes::Java:
                    return uJava(LanguageTokenTypes::Java, right);
                case LanguageTokenTypes::Go:
                    return uGo(LanguageTokenTypes::Go, right);
                case LanguageTokenTypes::Kotlin:
                    return uKotlin(LanguageTokenTypes::Kotlin, right);
                case LanguageTokenTypes::Swift:
                    return uSwift(LanguageTokenTypes::Swift, right);
                case LanguageTokenTypes::Rust:
                    return uRust(LanguageTokenTypes::Rust, right);
                case LanguageTokenTypes::CSharp:
                    return uCSharp(LanguageTokenTypes::CSharp, right);
                case LanguageTokenTypes::FSharp:
                    return uFSharp(LanguageTokenTypes::FSharp, right);
                case LanguageTokenTypes::ObjectiveC:
                    return uObjectiveC(LanguageTokenTypes::ObjectiveC, right);
                case LanguageTokenTypes::Scala:
                    return uScala(LanguageTokenTypes::Scala, right);
                case LanguageTokenTypes::TypeScript:
                    return uTypeScript(LanguageTokenTypes::TypeScript, right);
                case LanguageTokenTypes::Dart:
                    return uDart(LanguageTokenTypes::Dart, right);
                case LanguageTokenTypes::PHP:
                    return uPHP(LanguageTokenTypes::PHP, right);
                case LanguageTokenTypes::R:
                    return uR(LanguageTokenTypes::R, right);
                case LanguageTokenTypes::Lua:
                    return uLua(LanguageTokenTypes::Lua, right);
                case LanguageTokenTypes::MATLAB:
                    return uMATLAB(LanguageTokenTypes::MATLAB, right);
                case LanguageTokenTypes::VBA:
                    return uVBA(LanguageTokenTypes::VBA, right);
                case LanguageTokenTypes::Groovy: 
                    return uGroovy(LanguageTokenTypes::Groovy, right);
                case LanguageTokenTypes::Julia:
                    return uJulia(LanguageTokenTypes::Julia, right);
                case LanguageTokenTypes::PowerShell:
                    return uPowerShell(LanguageTokenTypes::PowerShell, right);
                case LanguageTokenTypes::VisualBasic:
                    return uVisualBasic(LanguageTokenTypes::VisualBasic, right);
                case LanguageTokenTypes::Dlang:
                    return uDlang(LanguageTokenTypes::Dlang, right);
                case LanguageTokenTypes::Haskell:
                    return uHaskell(LanguageTokenTypes::Haskell, right);
                case LanguageTokenTypes::Erlang:
                    return uErlang(LanguageTokenTypes::Erlang, right);
                case LanguageTokenTypes::Clojure:
                    return uClojure(LanguageTokenTypes::Clojure, right);
                case LanguageTokenTypes::StandardML:
                    return uStandardML(LanguageTokenTypes::StandardML, right);
                case LanguageTokenTypes::Elm:
                    return uElm(LanguageTokenTypes::Elm, right);
                case LanguageTokenTypes::VHDLVerilog:
                    return uVHDLVerilog(LanguageTokenTypes::VHDLVerilog, right);
                case LanguageTokenTypes::Fortran:
                    return uFortran(LanguageTokenTypes::Fortran, right);
                case LanguageTokenTypes::COBOL:
                    return uCOBOL(LanguageTokenTypes::COBOL, right);
                case LanguageTokenTypes::Pascal:
                    return uPascal(LanguageTokenTypes::Pascal, right);
                case LanguageTokenTypes::Ada:
                    return uAda(LanguageTokenTypes::Ada, right);
                case LanguageTokenTypes::Perl:
                    return uPerl(LanguageTokenTypes::Perl, right);
                case LanguageTokenTypes::AWK:
                    return uAWK(LanguageTokenTypes::AWK, right);
                case LanguageTokenTypes::TCL:
                    return uTCL(LanguageTokenTypes::TCL, right);
                case LanguageTokenTypes::Shell:
                    return uShell(LanguageTokenTypes::Shell, right);
                case LanguageTokenTypes::LISPScheme:
                    return uLISPScheme(LanguageTokenTypes::LISPScheme, right);
                case LanguageTokenTypes::Racket:
                    return uRacket(LanguageTokenTypes::Racket, right);
                case LanguageTokenTypes::Prolog:
                    return uProlog(LanguageTokenTypes::Prolog, right);
                case LanguageTokenTypes::SmallTalk:
                    return uSmallTalk(LanguageTokenTypes::SmallTalk, right);
                case LanguageTokenTypes::HTMLCSS:
                    return uHTMLCSS(LanguageTokenTypes::HTMLCSS, right);
                case LanguageTokenTypes::SQL:
                    return uSQL(LanguageTokenTypes::SQL, right);
                case LanguageTokenTypes::LabVIEW:
                    return uLabVIEW(LanguageTokenTypes::LabVIEW, right);
                case LanguageTokenTypes::Eiffel:
                    return uEiffel(LanguageTokenTypes::Eiffel, right);
                case LanguageTokenTypes::Custom:
                    return uCustom(LanguageTokenTypes::Custom, right);
                default:
                    throw runtimeerror<interpreter>(right.op.getType(), "Operand must be a number.");           
            }
        default:
            throw runtimeerror<interpreter>(right.op.getType(), "Operand must be a number.");
    }
    // Unreachable.
    return NULL;
}
/* ---------------------------------------------------------------------------
 * @brief visits the Binary abstraction syntax tree 
 * @param auto expr: Is a generic type that must have a concrete type during run time and the tree it will visit at run time
 * @return A Binary abstraction syntax tree node in the form of a string
 * ---------------------------------------------------------------------------
*/
std::any interpreter::visitBinaryExpr(auto& expr) {
    // In go, := makes a object. It must be represented in c++ as = 
    auto left = evaluate(expr.left);
    auto right = evaluate(expr.right);
    switch (currentLanguage) {
        case LanguageTokenTypes::Python:
            if (arithmeticOperations(currentLanguage, expr, left, right) != NULL) {

            }
            break;
        case LanguageTokenTypes::JavaScript:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Ruby:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::C:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::CPP:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Java:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Go:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Kotlin:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Swift:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Rust:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::CSharp:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::FSharp:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::ObjectiveC:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Scala:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::TypeScript:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Dart:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::PHP:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::R:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Lua:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::MATLAB:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::VBA:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Julia:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::PowerShell:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::VisualBasic:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Dlang:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Haskell:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Erlang:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Clojure:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::StandardML:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Elm:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::VHDLVerilog:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Fortran:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::COBOL:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Pascal:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Ada:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Perl:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::AWK:
            arithmeticOperations(currentLanguage, expr, left, right);
            //TODO: Add support for AWK
            break;
        case LanguageTokenTypes::TCL:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Shell:
            throw catcher<interpreter>("Unary minus not supported in Shell");
        case LanguageTokenTypes::LISPScheme:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Racket:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Prolog:
            throw catcher<interpreter>("Unary minus not supported in this context in Prolog");
        case LanguageTokenTypes::SmallTalk:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::HTMLCSS:
            //evaluateBinaryTokens(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::SQL:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::LabVIEW:
            throw catcher<interpreter>("Unary minus not applicable in this context");
        case LanguageTokenTypes::Eiffel:
            arithmeticOperations(currentLanguage, expr, left, right);
            break;
        case LanguageTokenTypes::Custom:
            arithmeticOperations(currentLanguage, expr, left, right);
            // TODO: This needs to be redone
            // This should be defined as a struct using templates for the objects to add flexibility 
            break;
        default:
            throw catcher<interpreter>("Operand must be a number.");           
    }
    // Unreachable.
    return NULL;
}
