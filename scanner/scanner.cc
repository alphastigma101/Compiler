#include <scanner.h>

/* ---------------------------------------------------------------------------------------------
 * This is the default constructor which can be used to create an instance of the Scanner Class
 * Params:
    *  std::string Source: the source line of code from a file or from the runprompt function
 * --------------------------------------------------------------------------------------------  
 */
Scanner::Scanner(std::string& Source): Source(this->Source) {}

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
    {"var", TokenType::VAR}
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
    tokens.push_back(Token(TokenType::END_OF_FILE, "", nullptr, line));
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
        case '"': String(); break;
        default: 
               if (isDigit(c)) {number();} 
               else if (isAlpha(c)) { identifier(); }
               else { std::cout << line << "Unexpected character."; }
               break;
    }
}

void Scanner::addToken(const TokenType type) { addToken(type, ""); }

/*
 * (addToken) is a method that is apart of the Scanner class 
 * Params:
    * Tokentype type: Is a Lexical grammar
    * const std::string literal: A representation of a primitive instance type 
 * This method only pushes to a vector 
*/
void Scanner::addToken(const TokenType type, const std::string literal) {
    std::string text = Source.substr(start, current);
    tokens.push_back(Token(type, text, literal, line));
}

/*
 * (identifier) is a method apart of the scanner class that searches for the keyword 
 * Params:
    *  None
 *  This method uses a dictionary to see if the object type is inside the dictionary 
 *  If it is not in the dictionary, it will be converted into TokenType::IDENTIFIER
 *  It will always call in addToken
*/
void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();
    std::string text = Source.substr(start, current);
    auto it = keywords.find(text);
    TokenType type;
    if (it != keywords.end()) {
        type = it->second;
    } else {
        type = TokenType::IDENTIFIER; // Default type if not found in keywords
    }
    addToken(type);
}
/*
 *
 *
*/
bool Scanner::match(const char expected) {
    if (isAtEnd()) return false;
    if (Source.at(current) != expected) return false;
    current++;
    return true;
}

/*
 *
 *
*/
void Scanner::String() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }
    if (isAtEnd()) {
        std::cout << line << "Unterminated string.";
        return;
    }
    // The closing ".
    advance();

    // Trim the surrounding quotes.
    std::string value = Source.substr(start + 1, current - 1);
    addToken(TokenType::STRING, value);
}
/*
 *
 *
*/
void Scanner::number() {    
    while (isDigit(peek())) advance();
    // Look for a fractional part.
    if (Scanner::peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();
        while (isDigit(peek())) advance();
    }
    addToken(TokenType::NUMBER, Source.substr(start, current));
}
