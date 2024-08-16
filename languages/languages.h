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
        std::string replace(std::string &code, const std::string for_loops, const std::string while_loops, const std::string if_blocks, const std::string function, const std::unordered_map<std::string, std::pair<int,int>> values); 
    };
};
using namespace Operations;
namespace Languages {
    // Static languages struct
    struct static_languages: operations {
        std::string C();
        std::string CPP();
        std::string Java();
        std::string Go();
        std::string Kotlin();
        std::string Swift();
        std::string Rust();
        std::string Haskell();
        std::string CSharp();
        std::string FSharp();
        std::string ObjectiveC();
        std::string VHDLVerilog();
        std::string Fortran();
        std::string COBOL();
        std::string Pascal();
        std::string Ada();
        std::string Scala();
        std::string TypeScript();
        std::string Dart();
    };
    // Dynamic languages struct
    struct dynamic_languages: operations {
        std::string Python();
        std::string JavaScript();
        std::string Ruby();
        std::string PHP();
        std::string Perl();
        std::string R();
        std::string Lua();
        std::string Shell();
        std::string MATLAB();
        std::string VBA();
        std::string LISPScheme();
        std::string Groovy();
        std::string Erlang();
        std::string Clojure();
        std::string Prolog();
        std::string AWK();
        std::string TCL();
        std::string Julia();
        std::string PowerShell();
        std::string Racket();
        std::string Smalltalk();
    };
    // Other languages that don't fit neatly into static/dynamic categories
    struct other_languages: operations {
        std::string HTMLCSS();
        std::string SQL();
        std::string LabVIEW();
        std::string VisualBasic();
        std::string Elm();
        std::string Eiffel();
        std::string StandardML();
        std::string Dlang();
    };

    // Main languages struct
    struct languages {
        static static_languages static_lang;
        dynamic_languages dynamic_lang;
        other_languages other_lang;
    };
};
using namespace Languages;
extern languages type;
#endif
