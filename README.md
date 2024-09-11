### Public-Project: Compiler 
```
    This is a open source project that uses c++ to compile and run custom programming languages or modern programming languages
```

# Table Of Contents

1. [Supported Programming languages](#supported-programming-languages)
2. [Project Construction](#product-construction)
3. [Macros](#macros)
    - [Sources](#sources)
4. [Pragmas](#pragmas)
    - [Sources](#sources)

### Supported Programming languages:

* [C](https://en.cppreference.com/w/c)
* [C++ (CPP)](https://en.cppreference.com/w/cpp)
* [Java](https://docs.oracle.com/en/java/)
* [Python](https://docs.python.org/3/)
* [JavaScript](https://developer.mozilla.org/en-US/docs/Web/JavaScript)
* [Ruby](https://www.ruby-lang.org/en/documentation/)
* [Swift](https://swift.org/documentation/)
* [Go](https://golang.org/doc/)
* [Kotlin](https://kotlinlang.org/docs/home.html)
* [Scala](https://docs.scala-lang.org/)
* [TypeScript](https://www.typescriptlang.org/docs/)
* [PHP](https://www.php.net/manual/en/)
* [Perl](https://perldoc.perl.org/)
* [R](https://www.r-project.org/other-docs.html)
* [Objective-C](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/Introduction/Introduction.html)
* [Haskell](https://www.haskell.org/documentation/)
* [Rust](https://www.rust-lang.org/learn)
* [Dart](https://dart.dev/guides)
* [Lua](https://www.lua.org/manual/5.4/)
* [Shell (Bash)](https://www.gnu.org/software/bash/manual/)
* [HTML/CSS](https://developer.mozilla.org/en-US/docs/Web/HTML)
* [SQL](https://dev.mysql.com/doc/)
* [MATLAB](https://www.mathworks.com/help/matlab/)
* [VHDL/Verilog](https://www.eda.org/svdb/view_category.php?categoryId=21)
* [F# (FSharp)](https://fsharp.org/learn/)
* [C# (CSHARP)](https://docs.microsoft.com/en-us/dotnet/csharp/)
* [VBA](https://docs.microsoft.com/en-us/office/vba/api/overview/)
* [Fortran](https://fortran-lang.org/learn/)
* [COBOL](https://open-cobol.sourceforge.io/)
* [Pascal](https://www.freepascal.org/docs.html)
* [LISP/Scheme](https://docs.racket-lang.org/)
* [Groovy](https://groovy-lang.org/documentation.html)
* [Erlang](https://www.erlang.org/docs)
* [Clojure](https://clojure.org/guides/getting_started)
* [Prolog](https://www.swi-prolog.org/pldoc/doc_for?object=manual)
* [Ada](https://learn.adacore.com/courses/intro-to-ada/)
* [AWK](https://www.gnu.org/software/gawk/manual/gawk.html)
* [TCL](https://www.tcl.tk/man/)
* [D](https://dlang.org/documentation.html)
* [Julia](https://docs.julialang.org/en/)
* [Visual Basic](https://docs.microsoft.com/en-us/dotnet/visual-basic/)
* [PowerShell](https://docs.microsoft.com/en-us/powershell/)
* [Racket](https://docs.racket-lang.org/)
* [Elm](https://guide.elm-lang.org/)
* [Eiffel](https://www.eiffel.org/doc/)
* [LabVIEW](https://www.ni.com/en-us/support/documentation.html)
* [Smalltalk](https://wiki.c2.com/?SmalltalkDocumentation)
* [Standard ML (SML)](https://smlfamily.github.io/)

### Product Construction
* The goal is split the product's code so that the *exec_compiler* which is located in the Makefile shows which files are being used to built it are either going to be connected to something that looks like a terminal embeded in the navbar.html file or it will be seperated from the *generate_code* which will be either built with the Dockerfile or the Makefile.

* Things that need to be implemented:
* A database that holds all the supported programming languages which each entities attributes is examples of optimization code for a specific langauge
* A optimization class that uses regex library that will take tokens and match the patterns to see if it can be optimized 
* A file callled `generate_code.html` that uses crow web frame works apis and inja template engine which it should contain a drop down menu of all the supported languages which the user should be able to click on and wait for it to generate the code
* Implement the funcions in languages.h which are inlined. Their job is to create stub function for each supported programming language
* Implement the routing using crow inside `generate_code.cc` 
* Implement .css code that will create a nice navbar 



* *generate_code* will use **crow** as its web-framework and inja for the template engine. I have included notes in *generate_code.cc* that will need to be implemented 
* **Sources:**
    * **Crow user manual/releases**:
        - *https://github.com/CrowCpp/Crow/releases*
        - *https://crowcpp.org/master/*
    * **inja user manual**:
        - *https://github.com/pantor/inja*
### Macros
* They function like functions but they are `directives` meaning they are `pre-proccessed` before `compilation`
* Need to add `\` whenever you want a new line 
# Sources
* **macros**:
    * *https://cplusplus.com/doc/tutorial/preprocessor/*
    * *https://learn.microsoft.com/en-us/cpp/preprocessor/macros-and-cpp?view=msvc-170*
    * *https://learn.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations?view=msvc-170*
    * *https://learn.microsoft.com/en-us/cpp/standard-library/aligned-storage-class?view=msvc-170*
    * *https://stackoverflow.com/questions/45477355/difference-between-pragma-and-pragma-in-c*
    * *https://learn.microsoft.com/en-us/cpp/preprocessor/macros-c-cpp?view=msvc-170*
### Pragmas
* They can be embedded with macros and can parse a directive if needed

# Sources
* **Pragmas**:
* *https://en.cppreference.com/w/cpp/preprocessor/impl*
* **Translation Phase**:
    * *https://en.cppreference.com/w/cpp/language/translation_phases#Phase_3*
* **preproccessor replace**:
    * *https://en.cppreference.com/w/cpp/preprocessor/replace*
