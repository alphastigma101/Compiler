#include <language_specific_unary_operations.h>

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

/* ----------------------------------------------------------------------------
 *
 *
*/
Visitor unaryOperations::dynamicLanguages::u-Python(LanguageTypes& lang, Vistor& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = static_cast<LanguageTypes::Python::Int>(&right))
                return -(*val);
            if (auto val = static_cast<LanguageTypes::Python::Float>(&right))
                return -(*val);

        }
    }
    catch(u->catcher("Failed to convert a python type into a c++ type!")& e) { std::cout << e.what() << std::endl;}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * JavaScript Description:
    This method will convert a JavaScript type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguages::u-JavaScript(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = static_cast<LanguageTypes::JavaScript::Number>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert JavaScript type into a c++ type!")& e) {std::cout << e.what() << std::endl;}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Ruby Description:
    This method will convert a Ruby type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguges::u-Ruby(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = static_cast<LanguageTypes::Ruby::Integer>(&right))
                return -(*val);
            if (auto val = static_cast<LanguageTypes::Ruby::Float>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert Ruby type into a c++ type!")& e) {std::cout << e.what() << std::endl;}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * C Description:
    This method will convert a C type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-C(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL;}
        else {
    
        }
    }
    catch(u->catcher("Failed to convert C type into c++ type!")& e) {std::cout << e.what() << std::endl;}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * CPP Description:
    This method will convert a C++ type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-CPP(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = static_cast<LanguageTypes::CPP::Int>(&right))
                return -(*val);
            if (auto val = static_cast<LanguageTypes::CPP::Double>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert c++ type into a c++ type!")& e) {std::cout << e.what() << std::endl;}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Java Description:
    This method will convert a Java type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-Java(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = static_cast<LanguageTypes::Java::Integer>(&right))
                return -(*val);
            if (auto val = static_cast<LanguageTypes::Java::Double>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert Java type into c++ type!")& e) {std::cout << e.what() << std::endl;}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Go Description:
    This method will convert a Go type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-Go(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = static_cast<LanguageTypes::Go::Int>(&right))
                return -(*val);
            if (auto val = static_cast<LanguageTypes::Go::Float64>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert Go type into c++ type!")& e) {std::cout << e.what() << std::endl;}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Kotlin Description:
    This method will convert a Kotlin type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-Kotlin(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = static_cast<LanguageTypes::Kotlin::Int>(&right))
                return -(*val);
            if (auto val = static_cast<LanguagesTypes::Kotlin::Long)((&right))
                return -(*val);
            if (auto val = static_cast<LanguageTypes::Kotlin::Double>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert Kotlin type into a c++ type!")& e) {std::cout << e.what() << std::endl;}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Swift Description:
    This method will convert a Swift type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-Swift(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = static_cast<LanguageTypes::Swift::Int>(&right))
                return -(*val);
            if (auto val = static_cast<LanguageTypes::Kotlin::Double>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert swift type into a c++ type!")& e) { std::cout << e.what() << std::endl;}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Rust Description:
    This method will convert a Rust type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-Rust(LanguageTypes& lang, Visitor& right) {
    try {
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
    }
    catch(u->catcher("Failed to convert a rust type into a c++ type!")& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}
/* ----------------------------------------------------------------------------
 * CSharp Description:
    This method will convert a CSharp type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-CSharp(LanguageTypes& lang, Visitor& right) {
    try {
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
    }
    catch(u->catcher("Failed to convert a csharp type into a c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * FSharp Description:
    This method will convert a FSharp type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor LanguageTypes::staticLanguages::u-FSharp(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = static_cast<LanguageTypes::FSharp::int_>(&right))
                return -(*val);
            if (auto val = static_cast<LanguagesTypes::FSharp::float_)((&right))
                return -(*val);
            if (auto val = static_cast<LanguageTypes::FSharp::double_>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert FSharp type into a c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * ObjectiveC Description:
    This method will convert a ObjectiveC type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-ObjectiveC(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = static_cast<LanguageTypes::ObjectiveC::NSInteger>(&right))
                return -(*val);
            if (auto val = static_cast<LanguagesTypes::ObjectiveC::NSUInteger)((&right))
                return -(*val);
            if (auto val = static_cast<LanguageTypes::ObjectiveC::CGFloat>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert a ObjectiveC type into a c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Scala Description:
    This method will convert a Scala type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-Scala(LanguageTypes& lang, Visitor& right) {
    try {
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
    }
    catch(u->catcher("Failed to convert Scala type into c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * TypeScript Description:
    This method will convert a TypeScript type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguages::u-TypeScript(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            // TODO: Need to add more support for typescript
            if (auto val = static_cast<LanguageTypes::TypeScript::number>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert typescript type into a c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Dart Description:
    This method will convert a Dart type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::staticLanguages::u-Dart(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = static_cast<LanguageTypes::Dart::int_>(&right))
                return -(*val);
            if (auto val = static_cast<LanguagesTypes::Dart::double_)((&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert dart type into c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * PHP Description:
    This method will convert a PHP type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguages::u-PHP(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = static_cast<LanguageTypes::PHP::Int>(&right))
                return -(*val);
            if (auto val = static_cast<LanguagesTypes::PHP::Float)((&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert php type into a c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * R Description:
    This method will convert a R type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguages::u-R(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = static_cast<LanguageTypes::R::Integer>(&right))
                return -(*val);
            if (auto val = static_cast<LanguageTypes::R::Double>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert a R type into a c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Lua Description:
    This method will convert a Lua type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguages::u-Lua(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = static_cast<LanguageTypes::Lua::Number>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert Lua type into a c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * MATLAB Description:
    This method will convert a MATLAB  type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguages::MATLAB(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            // TODO: Add more support  
            if (auto val = static_cast<LanguageTypes::MATLAB::Double>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert MATLAB type into c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * VBA Description:
    This method will convert a VBA type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguages::VBA(LanguageTypes& lang, Visitor& right) {
    try {
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
    }
    catch(u->catcher("Failed to convert VBA type into a c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Groovy Description:
    This method will convert a Groovy type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguages::Groovy(LanguageTypes& lang, Visitor& right) {
    try {
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
    }
    catch(u->catcher("Failed to convert groovy type into a c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Julia Description:
    This method will convert a Julia type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguages::Julia(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = static_cast<LanguageTypes::Julia::Int64>(&right))
                return -(*val);
            if (auto val = static_cast<LanguagesTypes::Julia::Float64)((&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert Julia type into c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * PowerShell Description:
    This method will convert a PowerShell type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::dynamicLanguages::PowerShell(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = static_cast<LanguageTypes::PowerShell::Int>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to powershell type into c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * VisualBasics Description:
    This method will convert a VisualBasics type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor LanguageTypes::dynamicLanguages::VisualBasic(LanguageTypes& lang, Visitor& right) {
    try {
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
    }
    catch(u->catcher("Failed to convert VisualBasic type into c++ type!")& e) {}
    return NULL;
}
/* ----------------------------------------------------------------------------
 * Dlang Description:
    This method will convert a Dlang type into a C++ representation type
 * Arguments:
 * LanguageTypes& lang: and alias a enumerator
 * Visitor& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
Visitor unaryOperations::otherLanguages::Dlang(LanguageTypes& lang, Visitor& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = static_cast<double>(&right))
                return -(*val);
        }
    }
    catch(u->catcher("Failed to convert Dlang type into a c++ type!")& e) {}
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::dynamicLanguages::Haskell(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::otherLanguages::Erlang(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::dynamicLanguages::Clojure(LanguageTypes& lang, Visitor& right) {
    if (auto val = static_cast<LanguageTypes::Clojure::Number>(&right))
        return -(*val);
}
/*
 *
*/
Visitor unaryOperations::otherLanguages::StandardML(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::otherLanguages::Elm(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::staticLanguages::VHDLVerilog(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::staticLanguages::Fortran(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::staticLanguages::COBOL(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::staticLanguages::Pascal(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::staticLanguages::Ada(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::dynamicLanguages::Perl(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::dynamicLanguages::u-AWK(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        //TODO: Add support for AWK
    }
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::otherLanguages::u-TCL(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::dynamicLanguages::u-Shell(LanguageTypes& lang, Visitor& right) {
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::dynamicLanguges::u-LISPScheme(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::dynamicLanguages::u-Racket(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::otherLanguages::u-Prolog(LanguageTypes& lang, Visitor& right) {
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::otherLanguages::u-Smalltalk(LanguageTypes& lang, Visitor& right) {
    if (checkNumberOperand(right) == false) {return NULL;}
    else {
        if (auto val = static_cast<double>(&right))
            return -(*val);
    }
}
/*
 *
*/
Visitor unaryOperations::otherLanguages::u-HTMLCSS(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::otherLanguages::u-SQL(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::otherLanguages::u-LabVIEW(LanguageTypes& lang, Visitor& right) {
    return NULL;
}
/*
 *
*/
Visitor unaryOperations::staticLanguages::u-Eiffel(LanguageTypes& lang, Visitor& right) {
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
Visitor unaryOperations::otherLanguages::u-Custom(LanguageTypes& lang, Visitor& right) {
    //TODO: This needs to be redone
    // This should be defined as a struct using templates for the objects to add flexibility 
}
