#ifndef _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_ 
#include <token.h>
#include <typeinfo>
#include <catcher.h>
template<class Visitor>
class unaryOperations: public Check<unaryOperations>, public catcher<unaryOperations> {
    public:
        Vistor u-Python(LanguageTypes& lang, Vistor& right); 
        Visitor u-JavaScript(LanguageTypes& lang, Visitor& right); 
        Visitor u-Ruby(LanguageTypes& lang, Visitor& right); 
        Visitor u-C(LanguageTypes& lang, Visitor& right);
        Visitor u-CPP(LanguageTypes& lang, Visitor& right); 
        Visitor u-Java(LanguageTypes& lang, Visitor& right); 
        Visitor u-Go(LanguageTypes& lang, Visitor& right); 
        Visitor u-Kotlin(LanguageTypes& lang, Visitor& right); 
        Visitor u-Swift(LanguageTypes& lang, Visitor& right); 
        Visitor u-Rust(LanguageTypes& lang, Visitor& right); 
        Visitor u-CSharp(LanguageTypes& lang, Visitor& right); 
        Visitor u-FSharp(LanguageTypes& lang, Visitor& right); 
        Visitor u-ObjectiveC(LanguageTypes& lang, Visitor& right); 
        Visitor u-Scala(LanguageTypes& lang, Visitor& right); 
        Visitor u-TypeScript(LanguageTypes& lang, Visitor& right); 
        Visitor u-Dart(LanguageTypes& lang, Visitor& right); 
        Visitor u-PHP(LanguageTypes& lang, Visitor& right); 
        Visitor u-R(LanguageTypes& lang, Visitor& right); 
        Visitor u-Lua(LanguageTypes& lang, Visitor& right); 
        Visitor u-MATLAB(LanguageTypes& lang, Visitor& right);
        Visitor u-VBA(LanguageTypes& lang, Visitor& right);
        Visitor u-Groovy(LanguageTypes& lang, Visitor& right); 
        Visitor u-Julia(LanguageTypes& lang, Visitor& right); 
        Visitor u-PowerShell(LanguageTypes& lang, Visitor& right); 
        Visitor u-VisualBasic(LanguageTypes& lang, Visitor& right); 
        Visitor u-Dlang(LanguageTypes& lang, Visitor& right); 
        Visitor u-Haskell(LanguageTypes& lang, Visitor& right); 
        Visitor u-Erlang(LanguageTypes& lang, Visitor& right); 
        Visitor u-Clojure(LanguageTypes& lang, Visitor& right); 
        Visitor u-StandardML(LanguageTypes& lang, Visitor& right); 
        Visitor u-Elm(LanguageTypes& lang, Visitor& right); 
        Visitor u-VHDLVerilog(LanguageTypes& lang, Visitor& right); 
        Visitor u-Fortran(LanguageTypes& lang, Visitor& right); 
        Visitor u-COBOL(LanguageTypes& lang, Visitor& right); 
        Visitor u-Pascal(LanguageTypes& lang, Visitor& right); 
        Visitor u-Ada(LanguageTypes& lang, Visitor& right); 
        Visitor u-Perl(LanguageTypes& lang, Visitor& right); 
        Visitor u-AWK(LanguageTypes& lang, Visitor& right); 
        Visitor u-Shell(LanguageTypes& lang, Visitor& right); 
        Visitor u-LISPScheme(LanguageTypes& lang, Visitor& right);
        Visitor u-Racket(LanguageTypes& lang, Visitor& right);
        Visitor u-Prolog(LanguageTypes& lang, Visitor& right); 
        Visitor u-Smalltalk(LanguageTypes& lang, Visitor& right); 
        Visitor u-HTMLCSS(LanguageTypes& lang, Visitor& right); 
        Visitor u-SQL(LanguageTypes& lang, Visitor& right); 
        Visitor u-LabVIEW(LanguageTypes& lang, Visitor& right); 
        Visitor u-Eiffel(LanguageTypes& lang, Visitor& right); 
        Visitor u-Custom(LanguageTypes& lang, Visitor& right);
    private:
        bool checkNumberOperand(auto& expr, auto& right);
        unaryOperations *u;
    protected:
        inline bool isString(const Type& value) override { return value.type() == typeid(std::string);};
};
#endif
