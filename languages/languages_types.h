#pragma once
#ifndef _LANGUAGE_TYPES_H_
#define _LANGUAGE_TYPES_H_
#include <lookup_language.h>
#include <any>
#include <cstdint>
#include <optional>
#include <variant>
#include <complex>
#include <functional>
#include <set>
#include <time.h>
extern std::string user_choice; // get the user choice of language from the begining 
extern std::string file_name; 
namespace LanguageTypes {
    struct Python {
        using Any = std::any;
        using None = std::nullptr_t;
        using Bool = bool;
        using Int = int64_t;
        using Float = double;
        using Str = std::string;
        using List = std::vector<Any>;
        using Dict = std::map<Any, Any>;
    };
    struct Ruby {
        using Any = std::any;
        using Nil = std::nullptr_t;
        using TrueClass = bool;
        using FalseClass = bool;
        using Integer = int64_t;
        using Float = double;
        using String = std::string;
        using Array = std::vector<Any>;
        using Hash = std::map<Any, Any>;
    };
    struct JavaScript {
        using Any = std::any;
        using Undefined = std::monostate;
        using Null = std::nullptr_t;
        using Boolean = bool;
        using Number = double;
        using String = std::string;
        using Array = std::vector<Any>;
        using Object = std::map<std::string, Any>;
    };
    struct Java {
        using Object = std::any;
        using Null = std::nullptr_t;
        using Boolean = bool;
        using Byte = int8_t;
        using Short = int16_t;
        using Integer = int32_t;
        using Long = int64_t;
        using Float = float;
        using Double = double;
        using Char = char16_t;
        using String = std::string;
    };
    struct CPP {
        using Any = std::any;
        using Nullptr = std::nullptr_t;
        using Bool = bool;
        using Char = char;
        using Int = int;
        using Long = long;
        using Float = float;
        using Double = double;
        using String = std::string;
    };
     struct Go {
        using Any = std::any;
        using Bool = bool;
        using Int = int64_t;
        using Float64 = double;
        using String = std::string;
        using Slice = std::vector<Any>;
        using Map = std::map<Any, Any>;
    };
    struct Kotlin {
        using Any = std::any;
        using Unit = void;
        using Boolean = bool;
        using Int = int32_t;
        using Long = int64_t;
        using Float = float;
        using Double = double;
        using Char = char16_t;
        using String = std::string;
        template<typename T> using List = std::vector<T>;
        template<typename K, typename V> using Map = std::map<K, V>;
    };
    struct Swift {
        using Any = std::any;
        using Bool = bool;
        using Int = int64_t;
        using Double = double;
        using String = std::string;
        template<typename T> using Optional = std::optional<T>;
        template<typename T> using Array = std::vector<T>;
        template<typename K, typename V> using Dictionary = std::map<K, V>;
    };
    struct Rust {
        using Bool = bool;
        using i8 = int8_t;
        using i16 = int16_t;
        using i32 = int32_t;
        using i64 = int64_t;
        using u8 = uint8_t;
        using u16 = uint16_t;
        using u32 = uint32_t;
        using u64 = uint64_t;
        using f32 = float;
        using f64 = double;
        using String = std::string;
        template<typename T> using Vec = std::vector<T>;
        template<typename K, typename V> using HashMap = std::map<K, V>;
    };
    struct Haskell {
        using Bool = bool;
        using Int = int64_t;
        using Float = double;
        using String = std::string;
        template<typename T> using Maybe = std::optional<T>;
        template<typename T> using List = std::vector<T>;
    };
    struct CSharp {
        using object = std::any;
        using bool_ = bool;
        using byte = uint8_t;
        using sbyte = int8_t;
        using short_ = int16_t;
        using ushort = uint16_t;
        using int_ = int32_t;
        using uint = uint32_t;
        using long_ = int64_t;
        using ulong = uint64_t;
        using float_ = float;
        using double_ = double;
        using decimal = long double;
        using char_ = char16_t;
        using string = std::string;
    };
    struct FSharp {
        using bool_ = bool;
        using int_ = int32_t;
        using float_ = float;
        using double_ = double;
        using string = std::string;
        template<typename T> using option = std::optional<T>;
        template<typename T> using list = std::vector<T>;
    };
    struct ObjectiveC {
        using id = std::any;
        using BOOL = bool;
        using NSInteger = int64_t;
        using NSUInteger = uint64_t;
        using CGFloat = double;
        using NSString = std::string;
        template<typename T> using NSArray = std::vector<T>;
        template<typename K, typename V> using NSDictionary = std::map<K, V>;
    };
    struct VHDLVerilog {
        using bit = bool;
        using integer = int32_t;
        using real = double;
        using string = std::string;
    };
    struct Fortran {
        using logical = bool;
        using integer = int32_t;
        using real = float;
        using doubleprecision = double;
        using character = std::string;
    };
    struct COBOL {
        using numeric = int64_t;
        using alphanumeric = std::string;
    };
    struct Pascal {
        using boolean = bool;
        using integer = int32_t;
        using real = double;
        using char_ = char;
        using string = std::string;
    };
    struct Ada {
        using Boolean = bool;
        using Integer = int32_t;
        using Float = float;
        using Character = char;
        using String = std::string;
    };
    struct Scala {
        using Any = std::any;
        using Unit = void;
        using Boolean = bool;
        using Int = int32_t;
        using Long = int64_t;
        using Float = float;
        using Double = double;
        using Char = char16_t;
        using String = std::string;
        template<typename T> using List = std::vector<T>;
        template<typename K, typename V> using Map = std::map<K, V>;
    };
    struct TypeScript {
        using any = std::any;
        using undefined = std::monostate;
        using null = std::nullptr_t;
        using boolean = bool;
        using number = double;
        using string = std::string;
        template<typename T> using Array = std::vector<T>;
        template<typename K, typename V> using Record = std::map<K, V>;
    };
    struct Dart {
        using dynamic = std::any;
        using bool_ = bool;
        using int_ = int64_t;
        using double_ = double;
        using String = std::string;
        template<typename T> using List = std::vector<T>;
        template<typename K, typename V> using Map = std::map<K, V>;
    };
    struct PHP {
        using Mixed = std::any;
        using Null = std::nullptr_t;
        using Bool = bool;
        using Int = int64_t;
        using Float = double;
        using String = std::string;
        using Array = std::map<std::string, Mixed>;
        using Object = std::map<std::string, Mixed>;
    };
    struct Perl {
        using Scalar = std::any;
        using Array = std::vector<Scalar>;
        using Hash = std::map<std::string, Scalar>;
    };
    struct R {
        using Any = std::any;
        using Logical = bool;
        using Integer = int32_t;
        using Double = double;
        using Complex = std::complex<double>;
        using Character = std::string;
        using List = std::vector<Any>;
        using DataFrame = std::map<std::string, std::vector<Any>>;
    };
    struct Lua {
        using Nil = std::nullptr_t;
        using Boolean = bool;
        using Number = double;
        using String = std::string;
        using Function = std::function<std::any(std::vector<std::any>)>;
        using Table = std::map<std::any, std::any>;
    };
    struct Shell {
        using String = std::string;
        using Integer = int64_t;
        using Array = std::vector<String>;
    };
    struct MATLAB {
        using Double = double;
        using Logical = bool;
        using Char = std::string;
        using String = std::string;
        using Cell = std::vector<std::any>;
        using Struct = std::map<std::string, std::any>;
    };
    struct VBA {
        using Variant = std::any;
        using Boolean = bool;
        using Byte = uint8_t;
        using Integer = int16_t;
        using Long = int32_t;
        using Single = float;
        using Double = double;
        using Currency = int64_t;
        using String = std::string;
        using Date = time_t;
    };
    struct LISPScheme {
        using Any = std::any;
        using Bool = bool;
        using Number = double;
        using Symbol = std::string;
        using String = std::string;
        using List = std::vector<Any>;
    };
    struct Groovy {
        using Any = std::any;
        using Boolean = bool;
        using Integer = int32_t;
        using Long = int64_t;
        using Float = float;
        using Double = double;
        using String = std::string;
        using List = std::vector<Any>;
        using Map = std::map<Any, Any>;
    };
    struct Erlang {
        using Atom = std::string;
        using Number = double;
        using Pid = std::uintptr_t;
        using Reference = std::uintptr_t;
        using Binary = std::vector<uint8_t>;
        using List = std::vector<std::any>;
        using Tuple = std::vector<std::any>;
        using Map = std::map<std::any, std::any>;
    };
    struct Clojure {
        using Any = std::any;
        using Nil = std::nullptr_t;
        using Boolean = bool;
        using Number = double;
        using Symbol = std::string;
        using Keyword = std::string;
        using String = std::string;
        using List = std::vector<Any>;
        using Vector = std::vector<Any>;
        using Map = std::map<Any, Any>;
        using Set = std::set<Any>;
    };
    struct Prolog {
        using Atom = std::string;
        using Number = double;
        using Variable = std::string;
        using Compound = std::vector<std::any>;
    };
    struct AWK {
        using Scalar = std::any;
        using Array = std::map<std::string, Scalar>;
    };
    struct TCL {
        using Any = std::string;
        using List = std::vector<Any>;
        using Dict = std::map<Any, Any>;
    };
    struct Julia {
        using Any = std::any;
        using Nothing = std::nullptr_t;
        using Bool = bool;
        using Int64 = int64_t;
        using Float64 = double;
        using Complex = std::complex<double>;
        using String = std::string;
        using Symbol = std::string;
        template<typename T> using Array = std::vector<T>;
        template<typename K, typename V> using Dict = std::map<K, V>;
    };
    struct PowerShell {
        using Any = std::any;
        using Bool = bool;
        using Int = int64_t;
        using Double = double;
        using String = std::string;
        using Array = std::vector<Any>;
        using Hashtable = std::map<Any, Any>;
    };
    struct Racket {
        using Any = std::any;
        using Boolean = bool;
        using Number = double;
        using String = std::string;
        using Symbol = std::string;
        using List = std::vector<Any>;
        using Vector = std::vector<Any>;
        using Hash = std::map<Any, Any>;
    };
    struct Smalltalk {
        using Object = std::any;
        using Boolean = bool;
        using Integer = int64_t;
        using Float = double;
        using Character = char;
        using String = std::string;
        using Symbol = std::string;
        using Array = std::vector<Object>;
        using Dictionary = std::map<Object, Object>;
    };
    struct HTMLCSS {
        using String = std::string;
        using Number = double;
        using Boolean = bool;
        struct Element {
            std::string tag;
            std::map<std::string, std::string> attributes;
            std::vector<std::variant<std::string, Element>> children;
        };
        struct StyleRule {
            std::string selector;
            std::map<std::string, std::string> properties;
        };
    };
    struct SQL {
        using Null = std::nullptr_t;
        using Integer = int64_t;
        using Decimal = long double;
        using Float = double;
        using Char = std::string;
        using Varchar = std::string;
        using Text = std::string;
        using Date = std::string; // ISO 8601 format
        using Time = std::string; // ISO 8601 format
        using Timestamp = std::string; // ISO 8601 format
        using Boolean = bool;
        using Blob = std::vector<uint8_t>;
    };
    struct LabVIEW {
        using Boolean = bool;
        using I8 = int8_t;
        using I16 = int16_t;
        using I32 = int32_t;
        using I64 = int64_t;
        using U8 = uint8_t;
        using U16 = uint16_t;
        using U32 = uint32_t;
        using U64 = uint64_t;
        using SGL = float;
        using DBL = double;
        using EXT = long double;
        using String = std::string;
        template<typename T> using Array = std::vector<T>;
        template<typename K, typename V> using Cluster = std::map<K, V>;
    };
    struct VisualBasic {
        using Any = std::any;
        using Boolean = bool;
        using Byte = uint8_t;
        using Short = int16_t;
        using Integer = int32_t;
        using Long = int64_t;
        using Single = float;
        using Double = double;
        using Decimal = long double;
        using Date = time_t;
        using String = std::string;
        using Object = std::any;
        template<typename T> using Array = std::vector<T>;
    };
    struct Elm {
        using Int = int32_t;
        using Float = double;
        using Bool = bool;
        using Char = char;
        using String = std::string;
        template<typename T> using Maybe = std::optional<T>;
        template<typename T> using List = std::vector<T>;
        template<typename... Types> using Tuple = std::tuple<Types...>;
        template<typename K, typename V> using Dict = std::map<K, V>;
    };
    struct Eiffel {
        using INTEGER = int32_t;
        using REAL = double;
        using BOOLEAN = bool;
        using CHARACTER = char;
        using STRING = std::string;
        template<typename T> using ARRAY = std::vector<T>;
        template<typename K, typename V> using TABLE = std::map<K, V>;
        using ANY = std::any;
    };
    struct StandardML {
        using int_ = int32_t;
        using real = double;
        using bool_ = bool;
        using char_ = char;
        using string = std::string;
        template<typename T> using list = std::vector<T>;
        template<typename... Types> using tuple = std::tuple<Types...>;
        template<typename K, typename V> using map = std::map<K, V>;
    };
    struct Dlang {
        using void_ = void;
        using bool_ = bool;
        using byte = int8_t;
        using ubyte = uint8_t;
        using short_ = int16_t;
        using ushort = uint16_t;
        using int_ = int32_t;
        using uint = uint32_t;
        using long_ = int64_t;
        using ulong = uint64_t;
        using cent = __int128;
        using ucent = unsigned __int128;
        using float_ = float;
        using double_ = double;
        using real = long double;
        using ifloat = std::complex<float>;
        using idouble = std::complex<double>;
        using ireal = std::complex<long double>;
        using char_ = char;
        using wchar = char16_t;
        using dchar = char32_t;
        using string = std::string;
        template<typename T> using Array = std::vector<T>;
        template<typename K, typename V> using AssociativeArray = std::map<K, V>;
    };
    struct Custom {
        // alias templates
        template<typename...> using Object = void;
        using numeric = Object<int, double, float>;
        using tokens = Object<char, std::string>;
        using list = Object<std::vector<std::any>>;
        using dict = Object<std::map<std::any,std::any>>;
        template<typename...> using Ptr = void*;
        template<typename...> using Ref = void;
        using ptr = Ptr<numeric, tokens>;
        using ref = Ref<std::reference_wrapper<numeric>, std::reference_wrapper<tokens>>;
    };
};
using namespace LanguageTypes;
#endif
