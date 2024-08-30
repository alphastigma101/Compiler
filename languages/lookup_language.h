#pragma once
#ifndef _LOOKUP_TABLE_H_
#define _LOOKUP_TABLE_H_
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
const std::unordered_map<std::string, std::string> downloads = {
    {"C", "https://gcc.gnu.org/"},
    {"C++ (CPP)", "https://gcc.gnu.org/"},
    {"Java", "https://www.oracle.com/java/technologies/javase-downloads.html"},
    {"Python", "https://www.python.org/downloads/"},
    {"JavaScript", "https://nodejs.org/en/download/"},
    {"Ruby", "https://www.ruby-lang.org/en/downloads/"},
    {"Swift", "https://swift.org/download/"},
    {"Go", "https://golang.org/dl/"},
    {"Kotlin", "https://kotlinlang.org/docs/install.html"},
    {"Scala", "https://www.scala-lang.org/download/"},
    {"TypeScript", "https://www.typescriptlang.org/download"},
    {"PHP", "https://www.php.net/downloads"},
    {"Perl", "https://www.perl.org/get.html"},
    {"R", "https://cran.r-project.org/mirrors.html"},
    {"Objective-C", "https://developer.apple.com/xcode/"},
    {"Haskell", "https://www.haskell.org/platform/"},
    {"Rust", "https://www.rust-lang.org/tools/install"},
    {"Dart", "https://dart.dev/get-dart"},
    {"Lua", "https://www.lua.org/download.html"},
    {"Shell (Bash)", "https://www.gnu.org/software/bash/"},
    {"HTML/CSS", "https://www.w3.org/Style/CSS/"},
    {"SQL", "https://www.mysql.com/downloads/"},
    {"MATLAB", "https://www.mathworks.com/downloads/"},
    {"VHDL/Verilog", "https://www.eda.org/"},
    {"F# (FSharp)", "https://dotnet.microsoft.com/download/dotnet/5.0"},
    {"C# (CSHARP)", "https://dotnet.microsoft.com/download/dotnet/5.0"},
    {"VBA", "https://www.microsoft.com/en-us/microsoft-365/access"},
    {"Fortran", "https://gcc.gnu.org/fortran/"},
    {"COBOL", "https://www.gnu.org/software/gcc/cobol/"},
    {"Pascal", "https://www.freepascal.org/download.html"},
    {"LISP/Scheme", "https://mitpress.mit.edu/9780262530054/structure-and-interpretation-of-computer-programs/"},
    {"Groovy", "https://groovy-lang.org/download.html"},
    {"Erlang", "https://www.erlang.org/downloads"},
    {"Clojure", "https://clojure.org/guides/getting_started"},
    {"Prolog", "https://www.swi-prolog.org/Download.html"},
    {"Ada", "https://www.adacore.com/download"},
    {"AWK", "https://awk.js.org/"},
    {"TCL", "https://www.activestate.com/products/tcl/"},
    {"D", "https://dlang.org/download.html"},
    {"Julia", "https://julialang.org/downloads/"},
    {"Visual Basic", "https://visualstudio.microsoft.com/vs/"},
    {"PowerShell", "https://docs.microsoft.com/en-us/powershell/scripting/install/installing-powershell-core-on-windows"},
    {"Racket", "https://racket-lang.org/download/"},
    {"Elm", "https://guide.elm-lang.org/install.html"},
    {"Eiffel", "https://www.eiffel.com/"},
    {"LabVIEW", "https://www.ni.com/en-us/support/downloads/software-products/download.labview.html"},
    {"Smalltalk", "https://www.squeak.org/"},
    {"Standard ML (SML)", "https://www.standardml.org/"}
};

const std::unordered_map<std::string, std::vector<std::string>> languageExtensions = {
        {"C", {".c"}},
        {"C++ (CPP)", {".cpp", ".cc", ".cxx"}},
        {"Java", {".java"}},
        {"Python", {".py"}},
        {"JavaScript", {".js"}},
        {"Ruby", {".rb"}},
        {"Swift", {".swift"}},
        {"Go", {".go"}},
        {"Kotlin", {".kt", ".kts"}},
        {"Scala", {".scala"}},
        {"TypeScript", {".ts"}},
        {"PHP", {".php"}},
        {"Perl", {".pl"}},
        {"R", {".r", ".R"}},
        {"Objective-C", {".m"}},
        {"Haskell", {".hs"}},
        {"Rust", {".rs"}},
        {"Dart", {".dart"}},
        {"Lua", {".lua"}},
        {"Shell (Bash)", {".sh"}},
        {"HTML/CSS", {".html", ".css"}},
        {"SQL", {".sql"}},
        {"MATLAB", {".m"}},
        {"VHDL/Verilog", {".vhd", ".vhdl", ".v", ".sv", ".svh"}},
        {"F# (FSharp)", {".fs", ".fsx", ".fsscript"}},
        {"C# (CSHARP)", {".cs"}},
        {"VBA", {".vba"}},
        {"Fortran", {".f", ".f90", ".f95", ".f03", ".f08"}},
        {"COBOL", {".cob", ".cbl"}},
        {"Pascal", {".pas"}},
        {"LISP/Scheme", {".lisp", ".scm"}},
        {"Groovy", {".groovy"}},
        {"Erlang", {".erl"}},
        {"Clojure", {".clj"}},
        {"Prolog", {".pl", ".pro"}},
        {"Ada", {".ada", ".adb"}},
        {"AWK", {".awk"}},
        {"TCL", {".tcl"}},
        {"D", {".d"}},
        {"Julia", {".jl"}},
        {"Visual Basic", {".vb"}},
        {"PowerShell", {".ps1", ".psm1", ".psd1"}},
        {"Racket", {".rkt"}},
        {"Elm", {".elm"}},
        {"Eiffel", {".e"}},
        {"LabVIEW", {".vi"}},
        {"Smalltalk", {".st"}}, // No specific extension, commonly ".st" or others
        {"Standard ML (SML)", {".sml", ".ml"}}
    };

typedef std::string Key;
typedef std::vector<std::string> Extension;
typedef std::vector<std::string> LanguageLinks;
typedef std::map<Key, std::pair<Extension, LanguageLinks>> Table;
const inline Table initTable() {
    Table languageTable;
    for (auto it = languageExtensions.begin(); it != languageExtensions.end(); ++it) {
        const Key& key = it->first;
        const Extension& extension = it->second;
        auto downloadIt = downloads.begin();
        if (downloadIt != downloads.end()) {
            LanguageLinks&& Links{downloadIt->second};
            languageTable[key] = std::make_pair(extension, Links);
        }
    }
    return languageTable;
}; 

#endif 
