#pragma once
#ifndef _LANGUAGE_TYPES_H_
#define _LANGUAGE_TYPES_H_
#include <any>
#include <cstdint>
#include <optional>
#include <variant>
#include <complex>
#include <functional>
#include <set>
#include <chrono>
#include <regex>
#include <time.h>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <list>
#include <deque>
#include <future>
#include <iostream>
/**                                                                                                                
 * This header file is designed to be used in conjunction with `enum_types.h` at the end. This separation helps to better organize the code and its definitions.
*/
namespace LanguageTypes {
    struct Python {
        using Any = std::any;
        using None = std::nullptr_t;
        using Bool = bool;
        using Int = int;
        using Float = float;
        using Double = double;
        using String = std::string;
        template<typename T> using List = std::vector<T>;
        template<typename K, typename V> using Dict = std::map<K, V>;
        template<typename... Args> using Tuple = std::tuple<Args...>;
        template<typename T> using Set = std::set<T>;
        template<typename T> using FrozenSet = std::set<T>; // sets are already immutable
        //template<typename T> using MemoryView = std::span<T>; // C++20 feature
        using NoneType = void;
    };
    struct Ruby {
        using Any = std::any;
        using Nil = std::nullptr_t;
        using Bool = bool;
        using Int = int;
        //using Set = ...;
        using TrueClass = bool;
        using FalseClass = bool;
        //using NilClass = ;
        using Symbol = std::string;
        //using Range = ...;
        //using Enumerator = ...;
        using Float = float;
        using Double = double;
        using String = std::string;
        template<typename T> using Array = std::vector<T>;
        template<typename K, typename V> using Hash = std::map<K, V>;
    };
    struct JavaScript {
        using Undefined = std::monostate;
        using Null = std::nullptr_t;
        using Bool = bool;
        using Int = int;
        //using Symbol = ...;
        template<typename T> using Function = std::function<T>;
        //using Error = ...;
        template<typename K, typename V> using Map = std::map<K, V>;
        template<typename T> using Set = std::set<T>;
        template<typename K, typename V> using WeakMap = std::unordered_map<K, std::weak_ptr<V>>;
        template<typename V> using WeakSet =  std::unordered_set<std::weak_ptr<V>, std::owner_less<std::weak_ptr<V>>>;
        using Date = std::chrono::system_clock::time_point;
        using RegExp = std::regex;
        template<typename T> using Promise = std::promise<T>;
        //using Proxy = ...;
        //using Reflect = ...;
        using Double = double;
        using Float = float;
        using String = std::string;
        using Array = std::vector<std::any>;
        using Object = std::any;
    };
    struct Java {
        using Object = std::any;
        using Null = std::nullptr_t;
        using Bool = bool;
        using Int = int;
        using i8 = int8_t;
        using i16 = int16_t;
        using i32 = int32_t;
        using i64 = int64_t;
        using c32 = char32_t;
        using c16 = char16_t;
        using c8 = unsigned char;
        using Float = float;
        using Double = double;
        template<typename T> using Queue = std::queue<T>;
        template<typename T> using Deque = std::deque<T>;
        //using Stream = ...;
        //using Optional = ...;
        //using Date = ...;
        //using Time = ...;
        using String = std::string;
    };
    struct CPP {
        using Any = std::any;
        using Void = void;
        //template<typename T> using Class = class T;
        //template<typename T> using Struct = struct T;
        //:w
        //template<typename T> using Union = union T;
        using Nullptr = std::nullptr_t;
        using Bool = bool;
        using Char = char;
        using Int = int;
        using i8 = int8_t;
        using i16 = int16_t;
        using i32 = int32_t;
        using i64 = int64_t;
        using c32 = char32_t;
        using c16 = char16_t;
        using c8 = unsigned char;
        using Long = long;
        using Float = float;
        using Double = double;
        using String = std::string;
        using wChar = wchar_t;
        using Short = short;
        using SizeT = std::size_t;
        using Unsigned = unsigned;
        using Signed = signed;
        template<typename... Args> using Vector = std::vector<Args...>;
        template<typename K, typename V> using Map = std::map<K, V>;
        template<typename T, size_t N> using Array = std::array<T, N>;
        template<typename T> using Deque = std::deque<T>;
        template<typename T> using Set = std::set<T>;
        template<typename K, typename V> using UnorderedMap = std::unordered_map<K, V>;
        template<typename T> using UnorderedSet = std::unordered_set<T>;
        template<typename T> using Queue = std::queue<T>;
        template<typename T> using Stack = std::stack<T>;
        template<typename T, typename U> using Pair = std::pair<T, U>;
        template<typename... Args> using Tuple = std::tuple<Args...>;
        template<typename T> using UniquePtr = std::unique_ptr<T>;
        template<typename T> using SharedPtr = std::shared_ptr<T>;
        template<typename T> using WeakPtr = std::weak_ptr<T>;
    };
    struct C {
        using Any = std::any;
        using Nullptr = std::nullptr_t;
        //using Struct = struct;
        //using Union = union;
        using Bool = bool;
        using Int = int;
        using i8 = int8_t;
        using i16 = int16_t;
        using i32 = int32_t;
        using i64 = int64_t;
        using Char = char;
        using c32 = char32_t;
        using c16 = char16_t;
        using c8 = unsigned char;
        using Long = long;
        using Float = float;
        using Double = double;
        using String = std::string;
    };
     struct Go {
        using Any = std::any;
        using Bool = bool;
        using Int = int;
        using i8 = int8_t;
        using i16 = int16_t;
        using i32 = int32_t;
        using i64 = int64_t;
        using Char = char;
        using c32 = char32_t;
        using c16 = char16_t;
        using c8 = unsigned char;
        using Float = float;
        using Double = double;
        using String = std::string;
        using Slice = std::vector<Any>;
        using Map = std::map<Any, Any>;
    };
    struct Kotlin {
        using Any = std::any;
        using Unit = void;
        using Boolean = bool;
        using Int = int;
        using i8 = int8_t;
        using i16 = int16_t;
        using i32 = int32_t;
        using i64 = int64_t;
        using Char = char;
        using c32 = char32_t;
        using c16 = char16_t;
        using c8 = unsigned char;
        using Float = float;
        using Double = double;
        using String = std::string;
        template<typename T> using List = std::vector<T>;
        template<typename K, typename V> using Map = std::map<K, V>;
    };
    struct Swift {
        using Any = std::any;
        using Bool = bool;
        using Int = int;
        using i8 = int8_t;
        using i16 = int16_t;
        using i32 = int32_t;
        using i64 = int64_t;
        using Char = char;
        using c32 = char32_t;
        using c16 = char16_t;
        using c8 = unsigned char;
        using Float = float;
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
        using Float = float;
        using Double = double;
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
        using Int = int32_t;
        using Double = double;
        using string = std::string;
        using Long = int64_t;
    };
    struct Fortran {
        using Bool = bool;
        using Int = int32_t;
        using Float = float;
        using Double = double;
        using String = std::string;
    };
    struct COBOL {
        using numeric = int64_t;
        using alphanumeric = std::string;
    };
    struct Pascal {
        using Bool = bool;
        using Int = int32_t;
        using Double = double;
        using Char = char;
        using String = std::string;
    };
    struct Ada {
        using Bool = bool;
        using Int = int32_t;
        using Float = float;
        using Char = char;
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
        using Array = std::map<std::any, Mixed>;
        using Object = std::map<std::any, Mixed>;
    };
    struct Perl {
        using Scalar = std::any;
        using Array = std::vector<Scalar>;
        using Hash = std::map<std::string, Scalar>;
        using Int = int;
        using Double = double;
        using Float = float;
        using Long = int64_t;
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
    struct SmallTalk {
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
        using Int = int32_t;
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
        using Int = int32_t;
        using Double = double;
        using bool_ = bool;
        using Long = int64_t;
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
        struct hasSpecialRules {
            // implement the rules here
            // Example: If the language is NUKE. That means if any kind of syntax error occurs, it will spout random ASCII values and display TATICAL NUKE AT THE END 
            // And destory itself. 
            // Otherwise make the source code use the generic rules for a custom language
            // TODO: Search and see if there are theories on generic rules when it comes to creating a custom language if not, make one 
            // Phonetics and Phonology:
            // - Decide on the sound inventory (consonants, vowels).
            // - Establish phonotactic rules (how sounds can combine).

            // Morphology:
            // - Determine how words are formed (prefixes, suffixes, infixes).
            // - Choose between isolating (few affixes) vs. agglutinative (many affixes) vs. fusional (affixes merge with roots).

            // Syntax:
            // - Define sentence structure (e.g., Subject-Verb-Object vs. Subject-Object-Verb).
            // - Establish rules for question formation, negation, etc.

            // Semantics:
            // - Create a vocabulary and decide on word meanings.
            // - Develop rules for word formation and compounding.

            // Pragmatics:
            // - Consider how context affects meaning.
            // - Decide on politeness strategies and speech acts.

            // Orthography:
            // - Design a writing system (alphabetic, syllabic, logographic).

        };
    };
};
using namespace LanguageTypes;
#include <enum_types.h>
#endif
