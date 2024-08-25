#ifndef _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_ 
#include <token.h>
#include <typeinfo>
#include <catch.h>

template<typename...> using VisitorType = void;
using Visitor = VisitorType<std::any>;

class unaryOperations: public Check<unaryOperations>, public catcher<unaryOperations> {
    public:
        /* -----------------------------------------------------------------------------
         * isNumeric Description:
            Is a helper function for (checkNumberOperands) and (checkNumberOperands)
         * @param Type: Is a generic type that must have a concrete type during run time
         * @return:
            True if the object at runtime is type: int, int64_t, float, double, etc.
            Otherwise, return false
         * ----------------------------------------------------------------------------
        */
        inline bool isNumeric(const Visitor& value) override {
            // TODO: Need to add more supported types here. refer to languages_types.h
            return value.type() == typeid(int) ||
            value.type() == typeid(int64_t) ||
            value.type() == typeid(float) ||
            value.type() == typeid(double);
        };
        struct staticLanguages {
            Visitor u-C(LanguageTypes& lang, Visitor& right); // C
            Visitor u-CPP(LanguageTypes& lang, Visitor& right); // C++
            Visitor u-Java(LanguageTypes& lang, Visitor& right); // Java
            Visitor u-Go(LanguageTypes& lang, Visitor& right); // Go
            Visitor u-Kotlin(LanguageTypes& lang, Visitor& right); // Kotlin
            Visitor u-Swift(LanguageTypes& lang, Visitor& right); // Swift
            Visitor u-Rust(LanguageTypes& lang, Visitor& right); // Rust
            Visitor u-CSharp(LanguageTypes& lang, Visitor& right); // C#
            Visitor u-FSharp(LanguageTypes& lang, Visitor& right); // F#
            Visitor u-ObjectiveC(LanguageTypes& lang, Visitor& right); // Objective-C
            Visitor u-Scala(LanguageTypes& lang, Visitor& right); // Scala
            Visitor u-Dart(LanguageTypes& lang, Visitor& right); // Dart
            Visitor u-VHDLVerilog(LanguageTypes& lang, Visitor& right); // VHDL/Verilog
            Visitor u-Fortran(LanguageTypes& lang, Visitor& right); // Fortran
            Visitor u-COBOL(LanguageTypes& lang, Visitor& right); // COBOL
            Visitor u-Pascal(LanguageTypes& lang, Visitor& right); // Pascal
            Visitor u-Ada(LanguageTypes& lang, Visitor& right); // Ada
            Visitor u-Eiffel(LanguageTypes& lang, Visitor& right); // Eiffel
        };
        struct dynamicLanguages {
            Visitor u-Python(LanguageTypes& lang, Visitor& right); // Python
            Visitor u-JavaScript(LanguageTypes& lang, Visitor& right); // JavaScript
            Visitor u-Ruby(LanguageTypes& lang, Visitor& right); // Ruby
            Visitor u-R(LanguageTypes& lang, Visitor& right); // R
            Visitor u-PHP(LanguageTypes& lang, Visitor& right); // PHP
            Visitor u-Lua(LanguageTypes& lang, Visitor& right); // Lua
            Visitor u-MATLAB(LanguageTypes& lang, Visitor& right); // MATLAB
            Visitor u-VBA(LanguageTypes& lang, Visitor& right); // VBA
            Visitor u-Groovy(LanguageTypes& lang, Visitor& right); // Groovy
            Visitor u-Julia(LanguageTypes& lang, Visitor& right); // Julia
            Visitor u-PowerShell(LanguageTypes& lang, Visitor& right); // PowerShell
            Visitor u-VisualBasic(LanguageTypes& lang, Visitor& right); // Visual Basic
            Visitor u-Perl(LanguageTypes& lang, Visitor& right); // Perl
            Visitor u-AWK(LanguageTypes& lang, Visitor& right); // AWK
            Visitor u-Shell(LanguageTypes& lang, Visitor& right); // Shell scripting
            Visitor u-LISPScheme(LanguageTypes& lang, Visitor& right); // Lisp/Scheme
            Visitor u-Racket(LanguageTypes& lang, Visitor& right); // Racket
            Visitor u-Clojure(LanguageTypes& lang, Visitor& right); // Clojure
            Visitor u-Smalltalk(LanguageTypes& lang, Visitor& right); // Smalltalk
            Visitor u-Haskell(LanguageTypes& lang, Visitor& right); // Haskell
            Visitor u-TypeScript(LanguageTypes& lang, Visitor& right); // TypeScript
        };
        struct otherLanguages {
            Visitor u-HTMLCSS(LanguageTypes& lang, Visitor& right); // HTML/CSS
            Visitor u-SQL(LanguageTypes& lang, Visitor& right); // SQL
            Visitor u-LabVIEW(LanguageTypes& lang, Visitor& right); // LabVIEW (visual programming)
            Visitor u-StandardML(LanguageTypes& lang, Visitor& right); // Standard ML (Functional)
            Visitor u-Elm(LanguageTypes& lang, Visitor& right); // Elm (Functional)
            Visitor u-Custom(LanguageTypes& lang, Visitor& right); // Custom language
            Visitor u-Dlang(LanguageTypes& lang, Visitor& right); // D
            Visitor u-Prolog(LanguageTypes& lang, Visitor& right); // Prolog
            Visitor u-TCL(LanguageTypes& lang, Visitor& right); // TCL
            Visitor u-StandardML(LanguageTypes& lang, Visitor& right); // StandardML
        };
    private:
        bool checkNumberOperand(auto& expr, auto& right);
        unaryOperations *u;
    protected:
        inline bool isString(const Type& value) override { return value.type() == typeid(std::string);};
};
#endif
