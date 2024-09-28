#pragma once
#ifndef _LANGUAGES_H_
#define _LANGUAGES_H_
#include <macros.h>
#include <languages_types.h>
#define FINAL(CODE)  _Pragma(#CODE)

namespace Operations {
    // operations struct 
    // functions that operate on a string aka the code
    struct operations {
        String replace(String &code, const String for_loops, const String while_loops, const String if_blocks, const String function, const std::unordered_map<String, std::pair<int,int>> values); 
    };
};
using namespace Operations;
namespace Languages {
    // Static languages struct
    struct static_languages: operations {
        String C();
        String CPP();
        String Java();
        String Go();
        String Kotlin();
        String Swift();
        String Rust();
        String Haskell();
        String CSharp();
        String FSharp();
        String ObjectiveC();
        String VHDLVerilog();
        String Fortran();
        String COBOL();
        String Pascal();
        String Ada();
        String Scala();
        String TypeScript();
        String Dart();
    };
    // Dynamic languages struct
    struct dynamic_languages: operations {
        String Python();
        String JavaScript();
        String Ruby();
        String PHP();
        String Perl();
        String R();
        String Lua();
        String Shell();
        String MATLAB();
        String VBA();
        String LISPScheme();
        String Groovy();
        String Erlang();
        String Clojure();
        String Prolog();
        String AWK();
        String TCL();
        String Julia();
        String PowerShell();
        String Racket();
        String Smalltalk();
    };
    // Other languages that don't fit neatly into static/dynamic categories
    struct other_languages: operations {
        String HTMLCSS();
        String SQL();
        String LabVIEW();
        String VisualBasic();
        String Elm();
        String Eiffel();
        String StandardML();
        String Dlang();
    };

    // Main languages struct
    struct languages {
        static static_languages static_lang;
        dynamic_languages dynamic_lang;
        other_languages other_lang;
    };
};
using namespace Languages;
#endif
