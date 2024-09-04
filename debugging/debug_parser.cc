#include "parser.h"
logTable<std::map<std::string, std::vector<std::string>>> logEntries; // declare variable globally
/*class debugParser : public parser {
    public:
        debugParser(std::vector<Token>& tokens);
        ~debugParser();
        //static void debugEquality();
};

debugParser::debugParser(std::vector<Token>& tokens) : parser(tokens) {}

debugParser::~debugParser() {}
*/
/*void debugParser::debugEquality() {
    equality();
    return;
}*/
parser createParser(std::vector<Token>& tokens) { return parser(tokens);}

static void debugEquality() {
    std::vector<Token> tokens = {
        Token(TokenType::LEFT_PAREN, "(", "", 0),
        Token(TokenType::NUMBER, "1", "1.0", 1),
        Token(TokenType::EQUAL_EQUAL, "==", "\0" , 1),
        Token(TokenType::NUMBER, "1", "1.0", 1),
        Token(TokenType::RIGHT_PAREN, ")", "", 1),
        Token(TokenType::END_OF_FILE, "EOF", "EOF", EOF)
    };
    parser p = createParser(tokens);
    auto result = p.equality();
}

/*static void debugComparison() {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", 1.0, 1),
        Token(TokenType::LESS, "<", nullptr, 1),
        Token(TokenType::NUMBER, "2", 2.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.comparison();
}

static void debugTerm() {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", 1.0, 1),
        Token(TokenType::PLUS, "+", nullptr, 1),
        Token(TokenType::NUMBER, "2", 2.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.term();
}

static void debugFactor() {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "2", 2.0, 1),
        Token(TokenType::STAR, "*", nullptr, 1),
        Token(TokenType::NUMBER, "3", 3.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.factor();
}

static void debugUnary() {
    std::vector<Token> tokens = {
        Token(TokenType::MINUS, "-", nullptr, 1),
        Token(TokenType::NUMBER, "5", 5.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.unary();
}

static void debugPrimaryNumber() {
    std::vector<Token> tokens = {Token(TokenType::NUMBER, "42", 42.0, 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
}

static void debugPrimaryString() {
    std::vector<Token> tokens = {Token(TokenType::STRING, "hello", "hello", 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
}

static void debugPrimaryTrue() {
    std::vector<Token> tokens = {Token(TokenType::TRUE, "true", true, 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
}

static void debugPrimaryFalse() {
    std::vector<Token> tokens = {Token(TokenType::FALSE, "false", false, 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}*/

int main(int argc, char **argv) {
    debugEquality();
    return 0;
}
