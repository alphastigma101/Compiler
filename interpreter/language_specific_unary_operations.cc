#include <language_specific_unary_operations.h>
/* -----------------------------------------------------------------------------
 * isNumeric Description:
    Is a helper function for (checkNumberOperands) and (checkNumberOperands)
 * Arguments:
    * Type: Is a generic type that must have a concrete type during run time
 * Returns:
    True if the object at runtime is type: int, int64_t, float, double, etc.
    Otherwise, return false
 * ----------------------------------------------------------------------------
*/
bool binaryOperations::isNumeric(const Type& value) override {
    // TODO: Need to add more supported types here. refer to languages_types.h
    return value.type() == typeid(int) ||
           value.type() == typeid(int64_t) ||
           value.type() == typeid(float) ||
           value.type() == typeid(double);
}
/* ----------------------------------------------------------------------------------------------------------------------------------------------------
 * checkNumberOperand Description: 
    Is a method that calls in isNumeric, the helper function
 * Arguments:
    * Visitor expr: It is an object that represents the abstraction syntax, (ast) that is currently being used. In this case, it would be the Unary ast
    * Visitor right: Is a generic type that must have a concrete type during run time, and will visit the unary abstract syntax tree right side (rh)
 * Returns:
    True if a and b are equal
    Otherwise, return false 
 * ----------------------------------------------------------------------------------------------------------------------------------------------------
*/
bool unaryOperations::checkNumberOperand(auto& right) {
    if (isNumeric(right) == true) return true;
    return false;
}

/*
 *
*/
Vistor unaryOperations::Python(LanguageTypes& lang, Vistor& right) {
    if (checkNumberOperand(right) == false) { return NULL; }
    else {
        if (auto val = static_cast<LanguageTypes::Python::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Python::Float>(&right))
            return -(*val);
    }
}
/*
 *
*/
Visitor unaryOperations::JavaScript(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) { return NULL; }
    else {
        if (auto val = static_cast<LanguageTypes::JavaScript::Number>(&right))
            return -(*val);
    }
    return NULL; // if it reaches down here there's probably a bug somewhere 
}
/*
 *
*/
VisitorunaryOperations::Ruby(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) { return NULL; }
    else {
        if (auto val = static_cast<LanguageTypes::Ruby::Integer>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Ruby::Float>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::C(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) { return NULL;}
    else {
    
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::CPP(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) { return NULL; }
    else {
        if (auto val = static_cast<LanguageTypes::CPP::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::CPP::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Java(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) { return NULL; }
    else {
        if (auto val = static_cast<LanguageTypes::Java::Integer>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Java::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Go(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) { return NULL; }
    else {
        if (auto val = static_cast<LanguageTypes::Go::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Go::Float64>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Kotlin(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) { return NULL; }
    else {
        if (auto val = static_cast<LanguageTypes::Kotlin::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Kotlin::Long)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Kotlin::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Swift(LanguageTypes& lang, Visitor& right) {
   if (checkNumberOperand(right) == false) { return NULL; }
   else {
       if (auto val = static_cast<LanguageTypes::Swift::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Kotlin::Double>(&right))
            return -(*val);
    }
   return NULL;
}
/*
 *
*/
Visitor unaryOperations::Rust(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) { return NULL; }
    else {
        if (auto val = static_cast<LanguageTypes::Rust::i8>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Rust::i16)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Rust::i32>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Rust::i64>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Rust::u8>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Rust::u16>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Rust::u32>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Rust::u64>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Rust::f32>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Rust::f64>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::CSharp(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) { return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::CSharp::byte>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::CSharp::sbyte)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::CSharp::short_>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::CSharp::ushort>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::CSharp::int_)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::CSharp::uint>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::CSharp::long_>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::CSharp::ulong)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::CSharp::float_>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::CSharp::double_>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::CSharp::decimal)((&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor LanguageTypes::FSharp(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::FSharp::int_>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::FSharp::float_)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::FSharp::double_>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::ObjectiveC(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::ObjectiveC::NSInteger>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::ObjectiveC::NSUInteger)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::ObjectiveC::CGFloat>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Scala(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::Scala::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Scala::Long)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Scala::Float>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Scala::Double)((&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::TypeScript(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        // TODO: Need to add more support for typescript
        if (auto val = static_cast<LanguageTypes::TypeScript::number>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Dart(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::Dart::int_>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Dart::double_)((&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::PHP(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::PHP::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::PHP::Float)((&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::R(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::R::Integer>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::R::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Lua(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::Lua::Number>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::MATLAB(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        // TODO: Add more support  
        if (auto val = static_cast<LanguageTypes::MATLAB::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::VBA(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::VBA::Byte>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::VBA::Integer)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::VBA::Long>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::VBA::Single>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::VBA::Double)((&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Groovy(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::Groovy::Integer>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Groovy::Long)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Groovy::Double>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Groovy::Float>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Julia(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::Julia::Int64>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Julia::Float64)((&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::PowerShell(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::PowerShell::Int>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor LanguageTypes::VisualBasic(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        // TODO: This needs to be redone
        if (auto val = static_cast<LanguageTypes::VisualBasic::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::VisualBasic::Long)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::VisualBasic::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Dlang(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Haskell(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::Haskell::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Haskell::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Erlang(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        try {
            if (auto val = static_cast<LanguageTypes::Erlang::Number>(&right))
                return -(*val);
        }
        catch() {
            
        }
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Clojure(LanguageTypes& lang, Visitor& right) {
    if (auto val = static_cast<LanguageTypes::Clojure::Number>(&right))
        return -(*val);
}
/*
 *
*/
Visitor unaryOperations::StandardML(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {

        // TODO: This needs to be redone
        if (auto val = static_cast<LanguageTypes::StandardML::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::StandardML::Long)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::StandardML::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Elm(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::VHDLVerilog(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        // TODO: This needs to be redone
        if (auto val = static_cast<LanguageTypes::VHDLVerilog::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::VHDLVerilog::Long)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::VHDLVerilog::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Fortran(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::Fortran::interger>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Fortran::real)((&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::COBOL(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::COBOL::numeric>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Pascal(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::Pascal::integer>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Pascal::real)((&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Ada(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::Ada::integer>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Ada::Float)((&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Perl(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        // TODO: This needs to be redone
        if (auto val = static_cast<LanguageTypes::Perl::Int>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::Perl::Long)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::Perl::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::AWK(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        //TODO: Add support for AWK
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::TCL(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Shell(LanguageTypes& lang, Visitor& right) {
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::LISPScheme(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {    
        if (auto val = static_cast<LanguageTypes::LISPScheme::Double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Racket(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Prolog(LanguageTypes& lang, Visitor& right) {
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Smalltalk(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<double>(&right))
            return -(*val);
    }
}
/*
 *
*/
Visitor unaryOperations::HTMLCSS(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::HTMLCSS::Number>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::SQL(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<LanguageTypes::SQL::Integer>(&right))
            return -(*val);
        if (auto val = static_cast<LanguagesTypes::SQL::Decimal)((&right))
            return -(*val);
        if (auto val = static_cast<LanguageTypes::SQL::Float>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::LabVIEW(LanguageTypes& lang, Visitor& right) {
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Eiffel(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<double>(&right))
            return -(*val);
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::Custom(LanguageTypes& lang, Visitor& right) {
    //TODO: This needs to be redone
    // This should be defined as a struct using templates for the objects to add flexibility 
}
