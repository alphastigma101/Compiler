#pragma once
#ifndef _TOKEN_TYPES_H_
#define _TOKEN_TYPES_H_
#include <languages_types.h>
/**---------------------------------------------------------------------------
 * @brief The underlying are representations of literals
 *
 * ---------------------------------------------------------------------------
*/
enum TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE,
    RIGHT_BRACE, COMMA, DOT, 
    MINUS, PLUS, SEMICOLON,
    SLASH, STAR,
    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    // Literals.
    IDENTIFIER, STRING, NUMBER, INT, FLOAT, CHAR, VOID, 
    AUTO, BOOL,
    // General Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, PUBLIC, 
    PRIVATE, PROTECTED, IMPORT, PACKAGE, STATIC, FINAL, STD, 
    CATCH, FN, NUKE, 
    // Python Tokens
    DEF, ELIF, TRY, EXCEPT, FINALLY, WITH, AS,
    // JavaScript Tokens
    LET, CONST, FUNCTION, EXPORT,
    // Ruby Tokens
    END, ELSIF, UNLESS, MODULE, REQUIRE,
    // Swift Tokens & Go Tokens
    FUNC, STRUCT, INTERFACE,
    // Kotlin Tokens
    VAL,
    // PHP Tokens
    INCLUDE,
    // R Tokens
    LIBRARY,
    // Rust Tokens
    MUT, ENUM, IMPL,
    // Lua Tokens
    LOCAL, 
    // HTML Tokens
    TAG_OPEN, TAG_CLOSE, ATTR_NAME, ATTR_VALUE,
    // CSS Tokens
    SELECTOR, PROPERTY, VALUE, ID,
    // SQL Tokens
    SELECT, INSERT, UPDATE, DELETE, CREATE,
    DROP, WHERE, FROM, INTO, VALUES, SET,
    // MATLAB Tokens
    CLASSDEF,
    // Verilog Tokens
    ENDMODULE, INPUT, OUTPUT,
    ALWAYS, ASSIGN,
    // VHDL Tokens
    ENTITY, ARCHITECTURE, SIGNAL, PROCESS,
    // F# Tokens
    MATCH,
    // C# Tokens
    USING, NAMESPACE,
    // VBA Tokens
    SUB, DIM,
    // Fortran Tokens
    INTEGER, REAL, DO, ENDDO, SUBROUTINE,
    // COBOL Tokens
    IDENTIFICATION, DIVISION, SECTION, PERFORM, STOP, RUN,
    // Pascal Tokens
    PROGRAM, BEGIN, PROCEDURE,
    // LISP Tokens
    DEFUN, SETQ, LAMBDA, PROGN, LOOP,
    // Scheme Tokens
    DEFINE, COND,
    // Erlang Tokens
    CASE, RECEIVE, SWITCH,
    // Clojure Tokens
    DEFN, RECUR,
    // Prolog Tokens
    FACT, RULE,
    // TCL Tokens
    PROC,
    // Julia Tokens
    TYPE,
    // Elm Tokens
    EXPOSING, ALIAS,
    PORT, THEN, OF,
    IN, ARROW, EQUALS,
    // Racket Tokens
    QUOTE, UNQUOTE, QUASIQUOTE,
    SYNTAX, SYNTAX_RULES,

    // GraphQL Tokens
    QUERY, MUTATION, SUBSCRIPTION, UNION, 
    SCALAR, FRAGMENT,
    ON, BOOLEAN, LIST, NON_NULL,
    SPREAD, AT, EXCLAMATION, BRACES, PARENS, END_OF_FILE
};

enum LanguageTokenTypes {
    C, CPP, Java, Python,
    JavaScript, Ruby, Swift,
    Go, Kotlin, Scala, TypeScript,
    PHP, Perl, R, ObjectiveC, Haskell,
    Rust, Dart, Lua, Shell, HTMLCSS,
    SQL, MATLAB, VHDLVerilog, FSharp,
    CSharp, VBA, Fortran, COBOL,Pascal, 
    LISPScheme, Groovy,Erlang, Clojure, Dlang, 
    Prolog, Ada, AWK, TCL, D, Julia, VisualBasic,
    PowerShell, Racket, Elm, Eiffel, LabVIEW, SmallTalk, StandardML, Custom
};

enum LanguagePatterns {
    // Common syntax that is used is {}, :  <- for code blocks, () <- for storing arguments , =>, [](){} lamda functions
    // Variables: :=, =, etc
    // Include the key words for looping in every language, add support if a lexeme looks like a loop
    // Add support if a lexeme looks like a if statement, case, or function 
};
/**
 * @brief A map that maps enums to strings 
 *
*/
static const std::unordered_map<TokenType, std::string> tokenTypeStrings = {
    {TokenType::LEFT_PAREN, "LEFT_PAREN"},
    {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
    {TokenType::LEFT_BRACE, "LEFT_BRACE"},
    {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
    {TokenType::COMMA, "COMMA"},
    {TokenType::DOT, "DOT"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::PLUS, "PLUS"},
    {TokenType::SEMICOLON, "SEMICOLON"},
    {TokenType::SLASH, "SLASH"},
    {TokenType::STAR, "STAR"},
    {TokenType::BANG, "BANG"},
    {TokenType::BANG_EQUAL, "BANG_EQUAL"},
    {TokenType::EQUAL, "EQUAL"},
    {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
    {TokenType::GREATER, "GREATER"},
    {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
    {TokenType::LESS, "LESS"},
    {TokenType::LESS_EQUAL, "LESS_EQUAL"},
    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::STRING, "STRING"},
    {TokenType::NUMBER, "NUMBER"},
    {TokenType::INT, "INT"},
    {TokenType::FLOAT, "FLOAT"},
    {TokenType::CHAR, "CHAR"},
    {TokenType::VOID, "VOID"},
    {TokenType::AUTO, "AUTO"},
    {TokenType::BOOL, "BOOL"},
    {TokenType::AND, "AND"},
    {TokenType::CLASS, "CLASS"},
    {TokenType::ELSE, "ELSE"},
    {TokenType::FALSE, "FALSE"},
    {TokenType::FUN, "FUN"},
    {TokenType::FOR, "FOR"},
    {TokenType::IF, "IF"},
    {TokenType::NIL, "NIL"},
    {TokenType::OR, "OR"},
    {TokenType::PRINT, "PRINT"},
    {TokenType::RETURN, "RETURN"},
    {TokenType::SUPER, "SUPER"},
    {TokenType::THIS, "THIS"},
    {TokenType::TRUE, "TRUE"},
    {TokenType::VAR, "VAR"},
    {TokenType::WHILE, "WHILE"},
    {TokenType::PUBLIC, "PUBLIC"},
    {TokenType::PRIVATE, "PRIVATE"},
    {TokenType::PROTECTED, "PROTECTED"},
    {TokenType::IMPORT, "IMPORT"},
    {TokenType::PACKAGE, "PACKAGE"},
    {TokenType::STATIC, "STATIC"},
    {TokenType::FINAL, "FINAL"},
    {TokenType::STD, "STD"},
    {TokenType::CATCH, "CATCH"},
    {TokenType::FN, "FN"},
    {TokenType::NUKE, "NUKE"},
    {TokenType::DEF, "DEF"},
    {TokenType::ELIF, "ELIF"},
    {TokenType::TRY, "TRY"},
    {TokenType::EXCEPT, "EXCEPT"},
    {TokenType::FINALLY, "FINALLY"},
    {TokenType::WITH, "WITH"},
    {TokenType::AS, "AS"},
    {TokenType::LET, "LET"},
    {TokenType::CONST, "CONST"},
    {TokenType::FUNCTION, "FUNCTION"},
    {TokenType::EXPORT, "EXPORT"},
    {TokenType::END, "END"},
    {TokenType::ELSIF, "ELSIF"},
    {TokenType::UNLESS, "UNLESS"},
    {TokenType::MODULE, "MODULE"},
    {TokenType::REQUIRE, "REQUIRE"},
    {TokenType::FUNC, "FUNC"},
    {TokenType::STRUCT, "STRUCT"},
    {TokenType::INTERFACE, "INTERFACE"},
    {TokenType::VAL, "VAL"},
    {TokenType::INCLUDE, "INCLUDE"},
    {TokenType::LIBRARY, "LIBRARY"},
    {TokenType::MUT, "MUT"},
    {TokenType::ENUM, "ENUM"},
    {TokenType::IMPL, "IMPL"},
    {TokenType::LOCAL, "LOCAL"},
    {TokenType::TAG_OPEN, "TAG_OPEN"},
    {TokenType::TAG_CLOSE, "TAG_CLOSE"},
    {TokenType::ATTR_NAME, "ATTR_NAME"},
    {TokenType::ATTR_VALUE, "ATTR_VALUE"},
    {TokenType::SELECTOR, "SELECTOR"},
    {TokenType::PROPERTY, "PROPERTY"},
    {TokenType::VALUE, "VALUE"},
    {TokenType::ID, "ID"},
    {TokenType::SELECT, "SELECT"},
    {TokenType::INSERT, "INSERT"},
    {TokenType::UPDATE, "UPDATE"},
    {TokenType::DELETE, "DELETE"},
    {TokenType::CREATE, "CREATE"},
    {TokenType::DROP, "DROP"},
    {TokenType::WHERE, "WHERE"},
    {TokenType::FROM, "FROM"},
    {TokenType::INTO, "INTO"},
    {TokenType::VALUES, "VALUES"},
    {TokenType::SET, "SET"},
    {TokenType::CLASSDEF, "CLASSDEF"},
    {TokenType::ENDMODULE, "ENDMODULE"},
    {TokenType::INPUT, "INPUT"},
    {TokenType::OUTPUT, "OUTPUT"},
    {TokenType::ALWAYS, "ALWAYS"},
    {TokenType::ASSIGN, "ASSIGN"},
    {TokenType::ENTITY, "ENTITY"},
    {TokenType::ARCHITECTURE, "ARCHITECTURE"},
    {TokenType::SIGNAL, "SIGNAL"},
    {TokenType::PROCESS, "PROCESS"},
    {TokenType::MATCH, "MATCH"},
    {TokenType::USING, "USING"},
    {TokenType::NAMESPACE, "NAMESPACE"},
    {TokenType::SUB, "SUB"},
    {TokenType::DIM, "DIM"},
    {TokenType::INTEGER, "INTEGER"},
    {TokenType::REAL, "REAL"},
    {TokenType::DO, "DO"},
    {TokenType::ENDDO, "ENDDO"},
    {TokenType::SUBROUTINE, "SUBROUTINE"},
    {TokenType::IDENTIFICATION, "IDENTIFICATION"},
    {TokenType::DIVISION, "DIVISION"},
    {TokenType::SECTION, "SECTION"},
    {TokenType::PERFORM, "PERFORM"},
    {TokenType::STOP, "STOP"},
    {TokenType::RUN, "RUN"},
    {TokenType::PROGRAM, "PROGRAM"},
    {TokenType::BEGIN, "BEGIN"},
    {TokenType::PROCEDURE, "PROCEDURE"},
    {TokenType::DEFUN, "DEFUN"},
    {TokenType::SETQ, "SETQ"},
    {TokenType::LAMBDA, "LAMBDA"},
    {TokenType::PROGN, "PROGN"},
    {TokenType::LOOP, "LOOP"},
    {TokenType::DEFINE, "DEFINE"},
    {TokenType::COND, "COND"},
    {TokenType::CASE, "CASE"},
    {TokenType::RECEIVE, "RECEIVE"},
    {TokenType::SWITCH, "SWITCH"},
    {TokenType::DEFN, "DEFN"},
    {TokenType::RECUR, "RECUR"},
    {TokenType::FACT, "FACT"},
    {TokenType::RULE, "RULE"},
    {TokenType::PROC, "PROC"},
    {TokenType::TYPE, "TYPE"},
    {TokenType::EXPOSING, "EXPOSING"},
    {TokenType::ALIAS, "ALIAS"},
    {TokenType::PORT, "PORT"},
    {TokenType::THEN, "THEN"},
    {TokenType::OF, "OF"},
    {TokenType::IN, "IN"},
    {TokenType::ARROW, "ARROW"},
    {TokenType::EQUALS, "EQUALS"},
    {TokenType::QUOTE, "QUOTE"},
    {TokenType::UNQUOTE, "UNQUOTE"},
    {TokenType::QUASIQUOTE, "QUASIQUOTE"},
    {TokenType::SYNTAX, "SYNTAX"},
    {TokenType::SYNTAX_RULES, "SYNTAX_RULES"},
    {TokenType::QUERY, "QUERY"},
    {TokenType::MUTATION, "MUTATION"},
    {TokenType::SUBSCRIPTION, "SUBSCRIPTION"},
    {TokenType::UNION, "UNION"},
    {TokenType::SCALAR, "SCALAR"},
    {TokenType::FRAGMENT, "FRAGMENT"},
    {TokenType::ON, "ON"},
    {TokenType::BOOLEAN, "BOOLEAN"},
    {TokenType::LIST, "LIST"},
    {TokenType::NON_NULL, "NON_NULL"},
    {TokenType::SPREAD, "SPREAD"},
    {TokenType::AT, "AT"},
    {TokenType::EXCLAMATION, "EXCLAMATION"},
    {TokenType::BRACES, "BRACES"},
    {TokenType::PARENS, "PARENS"},
    {TokenType::END_OF_FILE, "EOF"}
};


#endif
