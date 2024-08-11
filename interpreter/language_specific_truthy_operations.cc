#include <language_specific_truthy_operations.h>

/* ---------------------------------------------------------------------------------------------------------
 * isTruthy Description:
    Is a method that will return an concrete type if the language the user specifies supports truthy/falsy
    Depending on the language, truthy can be an int, string, bool or NULL
 * Arguments:
    * Type: Is a generic type that must have a concrete type during run time
 * Returns:
    True if the object was successfully casted into a c++ supported type
    Otherwise, return false
 * ---------------------------------------------------------------------------------------------------------
*/
bool truthyOperations::isTruthy(const auto& object) {
    switch(currentLanguage) {
        case LanguageTypes::Python:
            if (static_cast<LanguageTypes::Python::None>(&object) != nullptr) return false;
            if (auto b = static_cast<LanguageTypes::Python::Bool>(&object)) return *b;
            if (auto i = static_cast<LanguageTypes::Python::Int>(&object)) return *i != 0;
            if (auto f = static_cast<LanguageTypes::Python::Float>(&object)) return *f != 0.0;
            if (auto s = static_cast<LanguageTypes::Python::Str>(&object)) return !s->empty();
            if (auto l = static_cast<LanguageTypes::Python::List>(&object)) return !l->empty();
            if (auto d = static_cast<LanguageTypes::Python::Dict>(&object)) return !d->empty();
            return true;
        case LanguageTypes::JavaScript:
            if (static_cast<LanguageTypes::JavaScript::Null>(&object) != nullptr) return false;
            if (static_cast<LanguageTypes::JavaScript::Undefined>(&object) != nullptr) return false;
            if (auto b = static_cast<LanguageTypes::JavaScript::Boolean>(&object)) return *b;
            if (auto n = static_cast<LanguageTypes::JavaScript::Number>(&object)) return *n != 0 && !std::isnan(*n);
            if (auto s = static_cast<LanguageTypes::JavaScript::String>(&object)) return !s->empty();
            return true;
        case LanguageTypes::Ruby:
            if (static_cast<LanguageTypes::Ruby::Nil>(&object) != nullptr) return false;
            if (auto b = static_cast<LanguageTypes::Ruby::TrueClass>(&object)) return true;
            if (auto b = static_cast<LanguageTypes::Ruby::FalseClass>(&object)) return false;
            return true;
        case LanguageTypes::C:
        case LanguageTypes::CPP:
            if (auto b = static_cast<LanguageTypes::CPP::Bool>(&object)) return *b;
            if (auto i = static_cast<LanguageTypes::CPP::Int>(&object)) return *i != 0;
            if (auto d = static_cast<LanguageTypes::CPP::Double>(&object)) return *d != 0.0;
            if (auto p = static_cast<LanguageTypes::CPP::Nullptr>(&object)) return false;
            return true;
        case LanguageTypes::Java:
            if (static_cast<LanguageTypes::Java::Null>(&object) != nullptr) return false;
            if (auto b = static_cast<LanguageTypes::Java::Boolean>(&object)) return *b;
            return true;
        case LanguageTypes::Go:
            if (auto b = static_cast<LanguageTypes::Go::Bool>(&object)) return *b;
            return true;
        case LanguageTypes::Kotlin:
        case LanguageTypes::Swift:
        case LanguageTypes::Rust:
        case LanguageTypes::CSharp:
        case LanguageTypes::FSharp:
        case LanguageTypes::ObjectiveC:
        case LanguageTypes::Scala:
        case LanguageTypes::TypeScript:
        case LanguageTypes::Dart:
            if (static_cast<std::nullptr_t>(&object) != nullptr) return false;
            if (auto b = static_cast<bool>(&object)) return *b;
            return true;
        case LanguageTypes::PHP:
            if (static_cast<nullptr_t>(&object) != nullptr) return false;
            if (auto b = static_cast<bool>(&object)) return *b;
            if (auto i = static_cast<int>(&object)) return *i != 0;
            if (auto f = static_cast<float>(&object)) return *f != 0.0f;
            if (auto s = static_cast<std::string>(&object)) return !s->empty();
            return true;
        case LanguageTypes::Perl:
        case LanguageTypes::R:
        case LanguageTypes::Lua:
        case LanguageTypes::MATLAB:
        case LanguageTypes::VBA:
        case LanguageTypes::Groovy:
        case LanguageTypes::Julia:
        case LanguageTypes::PowerShell:
        case LanguageTypes::VisualBasic:
            if (static_cast<nullptr_t>(&object) != nullptr) return false;
            if (auto b = static_cast<bool>(&object)) return *b;
            if (auto n = static_cast<double>(&object)) return *n != 0.0;
            if (auto s = static_cast<std::string>(&object)) return !s->empty();
            return true;
        case LanguageTypes::Haskell:
        case LanguageTypes::Erlang:
        case LanguageTypes::Clojure:
        case LanguageTypes::StandardML:
        case LanguageTypes::Elm:
            if (auto b = static_cast<bool>(&object)) return *b;
            return true;
        case LanguageTypes::VHDLVerilog:
        case LanguageTypes::Fortran:
        case LanguageTypes::COBOL:
        case LanguageTypes::Pascal:
        case LanguageTypes::Ada:
        case LanguageTypes::Eiffel:
            if (auto b = static_cast<bool>(&object)) return *b;
            return true;
        case LanguageTypes::AWK:
        case LanguageTypes::TCL:
            if (auto s = static_cast<std::string>(&object)) return !s->empty() && *s != "0";
            if (auto n = static_cast<double>(&object)) return *n != 0.0;
            return true;
        case LanguageTypes::Shell:
            if (auto s = static_cast<std::string>(&object)) return !s->empty();
            if (auto n = static_cast<int>(&object)) return *n != 0;
            return true;
        case LanguageTypes::LISPScheme:
        case LanguageTypes::Racket:
            if (static_cast<nullptr_t>(&object) != nullptr) return false;
            return true;
        case LanguageTypes::Prolog:
            if (auto b = static_cast<bool>(&object)) return *b;
            return true;
        case LanguageTypes::Smalltalk:
            if (static_cast<nullptr_t>(&object) != nullptr) return false;
            if (auto b = static_cast<bool>(&object)) return *b;
            return true;
        case LanguageTypes::HTMLCSS:
        case LanguageTypes::SQL:
        case LanguageTypes::LabVIEW:
            return NULL;
        case LanguageTypes::Dlang:
            if (static_cast<nullptr_t>(&object) != nullptr) return false;
            if (auto b = static_cast<bool>(&object)) return *b;
            if (auto i = static_cast<int>(&object)) return *i != 0;
            if (auto f = static_cast<float>(&object)) return *f != 0.0f;
            if (auto s = static_cast<std::string>(&object)) return !s->empty();
            return true;

        default:
            return NULL;
    }
}
