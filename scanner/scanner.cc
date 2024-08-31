#include <scanner.h>

/* ---------------------------------------------------------------------------------------------
 * This is the default constructor which can be used to create an instance of the Scanner Class
 * Params:
    *  std::string source: the source line of code from a file or from the runprompt function
 * --------------------------------------------------------------------------------------------  
 */
Scanner::Scanner(const std::string source): source(source) {}

/* ----------------------------------------------------------------------------------
 * (keywords) is a dictionary that holds in various keywords of programming languages 
 * Using unordered_map type because I want O(n) at run time
 * ----------------------------------------------------------------------------------
*/
const std::unordered_map<std::string, TokenType> Scanner::keywords = {
    // Add all the Keywrods here
    {"and",    TokenType::AND},
    {"class",  TokenType::CLASS},
    {"else",   TokenType::ELSE},
    {"false",  TokenType::FALSE},
    {"for",    TokenType::FOR},
    {"fun",    TokenType::FUN},
    {"if",     TokenType::IF},
    {"nil",    TokenType::NIL},
    {"or",     TokenType::OR},
    {"print",  TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super",  TokenType::SUPER},
    {"this",   TokenType::THIS},
    {"true",   TokenType::TRUE},
    {"var",    TokenType::VAR},
    {"while",  TokenType::WHILE},
    {"finally", TokenType::FINALLY},
    {"protected", TokenType::PROTECTED},
    {"import", TokenType::IMPORT},
    {"private", TokenType::PRIVATE},
    {"package", TokenType::PACKAGE},
    {"fn", TokenType::FN},
    {"catch", TokenType::CATCH},
    {"def", TokenType::DEF},
    {"final", TokenType::FINAL},
    {"std", TokenType::STD},
    {"var", TokenType::VAR},
    {"nuke", TokenType::NUKE}
};

/* ------------------------------------------------------------------------------------------------------
 * (ScanTokens) is a method that is apart of the scanner class 
 * Instead of (scanToken) method, this method scans the whole file until it reaches the EOF, (End Of File)
 * Takes no paramaters and returns void
 * ------------------------------------------------------------------------------------------------------
 */
std::vector<Token> Scanner::ScanTokens() {
    while (!isAtEnd()) {
        // We are at the beginning of the next lexeme.
        start = current;
        scanToken();
    }
    tokens.push_back(Token(TokenType::END_OF_FILE, static_cast<const std::string>(std::string("EOF")), static_cast<const std::string>(std::string("EOF")), line));
    return tokens;

}
/* ---------------------------------------------------------------------------------------------------------
 * (scanToken) is a method that is apart of the (Scanner) class 
 * Arguments:
    * None
 * ---------------------------------(Additional Info)-------------------------------------------------------
 * The purpose of (scanToken) is to perform a lexical analysis by gathering up lexemes 
 * lexemes are only the raw substrings of the source code.
    * Couple examples of lexemes would be 'v' 'a' 'r' group them together to make something useful out of them 
    * Lexeme is known as a string and so is a token
    * Note: grouping these bits of characters into lexemes are called its (lexical grammar). 
 * ------------------------------------------------------------------------------------------
*/
void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        // Single-character tokens
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
        case '/':
               if (match('/')) {
                   // A comment goes until the end of the line.
                   while (peek() != '\n' && !isAtEnd()) advance();
               } else { addToken(TokenType::SLASH); }
               break;
        case 'o':
               // Need to also add support for | and || 
               if (match('r')) { addToken(TokenType::OR); }
               break;
        case ' ':
        case '\r':
        case '\t':
               // Ignore whitespace.
                break;
        case '\n':
                line++;
                break;
        case '"': string_(); break;
        default: 
               if (isDigit(c)) { number_();} 
               else if (isAlpha(c)) { identifier(); }
               else { 
                   //throw runtimeerror<Scaner>(line, "Unexcepted character");
               }                
               break;
    }
}
/* ---------------------------------------------------------------------------
 * @brief Helper function that adds tokens to a container
 * @param const TokenType type: represents enum literals
 * ---------------------------------------------------------------------------
*/
void Scanner::addToken(const TokenType type) { addToken(type, ""); }

/* ---------------------------------------------------------------------------
 * @brief A method that gets called by a data memeber function helper
 * @param Tokentype type: Is a Lexical grammar
 * @param const std::string literal: A representation of a primitive instance type 
 * @return Nothing. This method only pushes to a vector. 
 * ---------------------------------------------------------------------------
*/
void Scanner::addToken(const TokenType type, const std::string literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}

/* ---------------------------------------------------------------------------
 * @brief Searches for the keyword inside a string literal.
 * @param None
 * @return None. It uses a dictionary to see if the object type is inside the dictionary 
 *  If it is not in the dictionary, it will be converted into TokenType::IDENTIFIER
 *  --------------------------------------------------------------------------
*/
void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();
    std::string text = source.substr(start, current - start);
    auto it = keywords.find(text);
    TokenType type;
    if (it != keywords.end()) {
        type = it->second;
    } else {
        type = TokenType::IDENTIFIER; // Default type if not found in keywords
    }
    addToken(type);
}
/* --------------------------------------------------------------------------
 * @brief It scans through the string literal and matches it with a enum type
 * @param const char expected: A character literal that is matched with an enum type
 * @return True if there is a match. Otherwise false
*/
bool Scanner::match(const char expected) {
    if (isAtEnd()) return false;
    if (source.at(current) != expected) return false;
    current++;
    return true;
}
/*
 *
 *
*/
void Scanner::string_() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }
    if (isAtEnd()) { throw catcher<Scanner>("Unterminated string."); }
    // The closing ".
    advance();

    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, current - start - 2);
    //std::string value = source;
    //value.erase(std::remove( value.begin(), value.end(), '\"' ),value.end());
    addToken(TokenType::STRING, value);
}
/*
 *
 *
*/
void Scanner::number_() {    
    while (isDigit(peek())) advance();
    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();
        while (isDigit(peek())) advance();
    }
    addToken(TokenType::NUMBER, source.substr(start, current - start));
}
