#include <languages.h>
#include <iostream>
std::string operations::replace(std::string &code, const std::string for_loop, const std::string while_loop, const std::string if_block, const std::string function, const std::unordered_map<std::string, std::pair<int,int>> values) {
    try {
        if (code.compare(code.find("FUNCTION"), std::string("FUNCTION").length(), "FUNCTION") == 0) {
            auto val = values.at("FUNCTION");
            code.replace((std::size_t)code.find("FUNCTION")+val.first, (size_t)val.second, function);
        }
    }
    catch(const std::out_of_range& e) {}
    try {
        if (code.compare(code.find("FOR"), std::string("FOR").length(), "FOR") == 0) {
            auto val = values.at("FOR");
            code.replace((std::size_t)code.find("FOR")+val.first, (size_t)val.second, for_loop);
        }
    }
    catch(const std::out_of_range& e) {
    
    }
    try {
        if (code.compare(code.find("WHILE"), std::string("WHILE").length(), "WHILE") == 0) {
            auto val = values.at("WHILE");
            code.replace((std::size_t)code.find("WHILE")+val.first, (size_t)val.second, while_loop);
        }
    }
    catch(const std::out_of_range& e) {}
    try {
        if (code.compare(code.find("IF"), std::string("IF").length(), "IF") == 0) {
            auto val = values.at("IF");
            code.replace((std::size_t)code.find("IF")+val.first, (std::size_t)val.second, if_block);
        }
    }
    catch(const std::out_of_range& e) {}
    return code;
}

std::string static_languages::C() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "for (int i = 0; i < 10; i++){\n\t\t// Fill in your code here!\n\t}";
    std::string while_loop = "while (true){\n\t\t// Fill in your code here and replace true with something else!\n\t}";
    std::string if_block = "if (true){\n\t\t// Fill in your code here!\n\t}\n\telse if (true) {\n\t\t// Fill in your code here!\n\t}";
    std::string function = "// You can call in function by their signatures inside certain fields like this field, but the function needs to be defined before you call it";
    static std::string code = C_CODE(C_CODE_STR)C_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::CPP() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {-1, 4}}
    };   
    std::string for_loop = "for (int i = 0; i < 10; i++) {\n\t\t// Fill in your code here!\n\t}"; 
    std::string while_loop = "while (true) {\n\t\t// Fill in your code here and replace true with something else!\n\t}";
    std::string if_block = "if (true){\n\t\t// Fill in your code here!\n\t}\n\telse if (true) {\n\t\t// Fill in your code here!\n\t}";
    std::string function = "// You can call in function by providing their signatures inside certain fields";
    std::string code = CPP_CODE(CPP_CODE_STR)CPP_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::Java() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {-1, 4}}
    };   
    std::string for_loop = "\tfor (int i = 0; i < 10; i++) {\n\t  // Fill in your code here!\n\t\t}";
    std::string while_loop = "\twhile (true) {\n\t  // Fill in your code here and replace true with something else!\n\t}";
    std::string if_block = "\tif (true){\n\t  // Fill in your code here!\n\t}\n\t\telse if (true) {\n\t  // Fill in your code here!\n\t}";
    std::string function = "\t// You can call in function by providing their signatures inside certain fields";
    std::string code = JAVA_CODE(JAVA_CODE_STR)JAVA_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Python() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {-1, 4}}
    };   
    std::string for_loop = "for i in range(0, 10):\n\t  # Fill in your code here!"; 
    std::string while_loop = "while (True):\n\t  # Fill in your code here and replace true with something else!\n";
    std::string if_block = "if (true):\n\t  # Fill in your code here!\n\telif (True): \n\t  #Fill in your code here!\n";
    std::string function = "# You can call in function by providing their signatures inside certain fields";
    static std::string code = PYTHON_CODE(PYTHON_CODE_STR)PYTHON_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;

}

std::string dynamic_languages::JavaScript() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "for (var i in arr) {\n\t  // Fill in your code here!}"; 
    std::string while_loop = "while (true) {\n  // Fill in your code here and replace true with something else!\n\t}";
    std::string if_block = "if (true){\n  // Fill in your code here!\n\t}\n\telse if (true) {\n  //Fill in your code here!\n\t}";
    std::string function = "// You can call in function by providing their signatures inside certain fields ex: some_function()";
    static std::string code = JAVASCRIPT_CODE(JAVASCRIPT_CODE_STR)JAVASCRIPT_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Ruby() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string notes = "// the yield keyword allows you to print things.\nAn example of a for loop is insde the Array class as you need to create your own instances";
    std::string class_block = "class Array\ndef find\nfor i in 0...size\nvalue = self[i]\nreturn value if yield(value)\nend\nreturn nil\nend\nend\n"; // Each end needs to align 
    std::string for_loop = "for i in 0...size\nvalue = self[i]\nreturn value if yield(value)";
    std::string while_loop = "while i1 <= max\nyield i1\ni1, i2 = i2, i1+i2\nend"; // end needs to be aligned with while
    std::string if_block = "if block_given?\nresult = yield <object>\nend"; // yield outputs the value to the terminal
    std::string function = "// You can call in function or instance of a class by providing their signatures inside this field or any other field\n[1, 3, 5, 7, 9].find {|v| v*v > 30 }";
    static std::string code = RUBY_CODE(RUBY_CODE_STR)RUBY_CODE_STR;
    code.insert(0, notes);
    code.insert(1, class_block);
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::Swift() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "for val in sequence{\n\t// statements\n}";
    std::string while_loop = "while (condition){\n\t// body of loop\n}";
    std::string if_block = "if (true){\n\t  // Fill in your code here!\n}\n\telse if (true) {\n  // Fill in your code here!\n\t}";
    std::string function = "// You can call in function by providing their signatures inside certain this field or any other field";
    static std::string code = SWIFT_CODE(SWIFT_CODE_STR)SWIFT_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::Go() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {-1, 4}}
    };   
    std::string for_loop = "for i:=0; i < 3; i++ {\n\t  // Fill in your code here!\n\t}"; 
    std::string while_loop = "while true {\n\t  // Fill in your code here and replace true with something else!\n\t}";
    std::string if_block = "if true {\n\t  // Fill in your code here!\n\t}\n\telse if true {\n\t  // Fill in your code here!\n\t}";
    std::string function = "// You can call in the function by defining it and declaring it inside a field";
    std::string code = GO_CODE(GO_CODE_STR)GO_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::Kotlin() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string notes = "// There are three ways to create arrays in Kotlin: /*\n\t1) arrayOf() Which is an array of types you can specify\n2) arrayOfNulls() this is self explainatory\n3) emptyArray() which is also self explainatory\n*/";
    std::string for_loop = "for (item in items) {\nprintln(item)\n}";
    std::string if_block = "if (true) {\n\t// FMI\n}\nelse {\n\t//FMI\n}";
    std::string while_loop = "var index = 0\nwhile (index < items.size) {\nprintln(\"item at $index is ${items[index]}\")\nindex++";
    std::string function = "// Define the funciton and pass it inside a field";
    static std::string code = KOTLIN_CODE(KOTLIN_CODE_STR)KOTLIN_CODE_STR;
    code.insert(0, notes);
    code.insert(1, "val items = listOf(\"apple\", \"banana\", \"kiwifruit\")\t//This is how you create a list in kotlin\n");
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    static std::string result = FINAL(updated_code)updated_code;
    return result;
}

std::string static_languages::Scala() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {-1, 4}}
    };
    std::string for_loop = "val buffer = new ListBuffer[Int]()\n\tfor i <- ints do\n\t  buffer += i * 2\n\tbuffer.toList\n\t"; 
    std::string if_block = "if (true) {\n\t  // FMI\n\t}\n\telse if (true) {\n\t  // FMI\n\t}\n\telse{\n\t  // FMI\n\t}\n";
    std::string function = "// You can call in the function as long as it is defined inside a field, ex: some_function()";
    std::string while_loop = "FMI";
    static std::string code = SCALA_CODE(SCALA_CODE_STR)SCALA_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::TypeScript() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "for (var i in arr) { // Fill in your code here!}"; 
    std::string while_loop = "while (true) {\n\t// Fill in your code here and replace true with something else!\n}";
    std::string if_block = "if (true){\n\t//fill in your code here!\n}\nelse if (true) {\n\t//Fill in your code here!\n}";
    std::string function = "// You can call in function by providing their signatures inside certain fields ex: some_function()";
    static std::string code = TYPESCRIPT_CODE(TYPESCRIPT_CODE_STR)TYPESCRIPT_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}
std::string dynamic_languages::PHP() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string notes = "// This is how you create variables in php: /* $var = 'Bob';\n $Var = 'Joe';*/\n//As you can see it is similar to bash in a way. You can also reference an object like so:\n/* $foo = 'Bob';\n$bar = &$foo;*/\n// Now replace the variables that do not exist with existing variables\n";
    std::string front_tag = "<?php\n";
    std::string end_tag = "?>";
    std::string for_loop = "echo 'Single digit odd numbers from range():';\nforeach (range(1, 9, 2) as $number) {\n echo \"$number \";\n}\necho \"\n\"";
    std::string while_loop = "$i = 1;\nwhile ($i < 6) {\n\techo $i;\n$i++;\n}\n";
    std::string if_block = "if ($start <= $limit) {\nif ($step <= 0) {\n\t//Replace the objects with existing objects\n\tthrow new LogicException('Step must be positive');\n}\nfor ($i = $start; $i <= $limit; $i += $step) {\nyield $i;\n}\n} else {\nif ($step >= 0) {\n throw new LogicException(\"Step must be negative\");\n}\n";
    std::string function = "echo \"You need to define the function first somewhere inside the tag field and you can call it in a field like this comment\"";
    static std::string code = PHP_CODE(PHP_CODE_STR)PHP_CODE_STR;
    code.insert(0, front_tag);
    code.insert(1, notes);
    code.insert(2, "class FMI {\n// As you can see, the class syntax in php is similar to c++. Instead of doing public: you do something below:\npublic $var = 'a default value';\n//public function fmi() {\necho $this->var;\n}\n}");
    code.insert(3, "// You can create an array using arry(//fill stuff in here ); or you can do it like this:\n/*$array = [\"foo\" => \"bar\",\n\"bar\" => \"foo\", \"c\"\n];*/\n//This is the syntax:/*\n$arr[key] = value;\n$arr[] = value;\n//Meaning that it is an element if it does not have =>, but will be a dictionary if it has a element mapped to another element using the =>");
    code.insert(code.length()-1, end_tag);
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    static std::string result = FINAL(updated_code)updated_code;
    return result;
}


std::string dynamic_languages::Perl() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = PERL_CODE(PERL_CODE_STR)PERL_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::R() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = R_CODE(R_CODE_STR)R_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::ObjectiveC() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    }; 
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = OBJECTIVEC_CODE(OBJECTIVEC_CODE_STR)OBJECTIVEC_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::Haskell() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = HASKELL_CODE(HASKEL_CODE_STR)HASKELL_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::Rust() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = RUST_CODE(RUST_CODE_STR)RUST_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::Dart() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = DART_CODE(DART_CODE_STR)DART_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Lua() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    const std::string function = "FMI";
    static std::string code = LUA_CODE(LUA_CODE_STR)LUA_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Shell() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = SHELL_CODE(SHELL_CODE_STR)SHELL_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string other_languages::HTMLCSS() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = HTMLCSS_CODE(HTMLCSS_CODE_STR)HTMLCSS_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string other_languages::SQL() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = SQL_CODE(SQL_CODE_STR)SQL_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::MATLAB() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = MATLAB_CODE(MATLAB_CODE_STR)MATLAB_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::VHDLVerilog() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = VHDL_CODE(VHDL_CODE_STR)VHDL_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::FSharp() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = FSHARP_CODE(FSHARP_CODE_STR)FSHARP_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::CSharp() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = CSHARP_CODE(CSHARP_CODE_STR)CSHARP_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::VBA() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = VBA_CODE(VBA_CODE_STR)VBA_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::Fortran() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = FORTAN_CODE(FORTAN_CODE_STR)FORTAN_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::COBOL() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = COBOL_CODE(COBOL_CODE_STR)COBOL_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::Pascal() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = PASCAL_CODE(PASCAL_CODE_STR)PASCAL_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::LISPScheme() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = LISPSCHEME_CODE(LISPSCHEME_CODE_STR)LISPSCHEME_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Groovy() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = GROOVY_CODE(GROOVY_CODE_STR)GROOVY_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Erlang() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = ERLANG_CODE(ERLANG_CODE_STR)ERLANG_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Clojure() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = CLOJURE_CODE(CLOJURE_CODE_STR)CLOJURE_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Prolog() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };   
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = PROLOG_CODE(PROLOG_CODE_STR)PROLOG_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string static_languages::Ada() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = ADA_CODE(ADA_CODE_STR)ADA_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::AWK() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = AWK_CODE(AWK_CODE_STR)AWK_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::TCL() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = TCL_CODE(TCL_CODE_STR)TCL_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string other_languages::Dlang() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = DLANG_CODE(DLANG_CODE_STR)DLANG_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Julia() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = JULIA_CODE(JULIA_CODE_STR)JULIA_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string other_languages::VisualBasic() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = VISUALBASIC_CODE(VISUALBASIC_CODE_STR)VISUALBASIC_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::PowerShell() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = POWERSHELL_CODE(POWERSHELL_CODE_STR)POWERSHELL_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Racket() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = RACKET_CODE(RACKET_CODE_STR)RACKET_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string other_languages::Elm() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = ELM_CODE(ELM_CODE_STR)ELM_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string other_languages::Eiffel() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = EIFFEL_CODE(EIFFEL_CODE_STR)EIFFEL_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string other_languages::LabVIEW() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = LABVIEW_CODE(LABVIEW_CODE_STR)LABVIEW_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string dynamic_languages::Smalltalk() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = SMALLTALK_CODE(SMALLTALK_CODE_STR)SMALLTALK_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}

std::string other_languages::StandardML() {
    std::unordered_map<std::string, std::pair<int,int>> values =  {
        {"FUNCTION", {-1, 10}},
        {"FOR", {-1, 5}},
        {"WHILE", {-1, 7}},
        {"IF", {0, 2}}
    };
    std::string for_loop = "";
    std::string while_loop = "";
    std::string if_block = "";
    std::string function = "FMI";
    static std::string code = STANDARDML_CODE(STANDARDML_CODE_STR)STANDARDML_CODE_STR;
    std::string updated_code = replace(code, for_loop, while_loop, if_block, function, values);
    return updated_code;
}
