#include <parser.h>
#include <scanner.h>
// Test case 1: Simple addition
std::vector<Token> test1 = {
    Token(TokenType::NUMBER, "3", "3.0", 1),
    Token(TokenType::PLUS, "+", "0.0", 1),
    Token(TokenType::NUMBER, "4", "4.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 2: Simple multiplication
std::vector<Token> test2 = {
    Token(TokenType::NUMBER, "5", "5.0", 1),
    Token(TokenType::STAR, "*", "0.0", 1),
    Token(TokenType::NUMBER, "6", "6.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 3: Mixed operations
std::vector<Token> test3 = {
    Token(TokenType::NUMBER, "2", "2.0", 1),
    Token(TokenType::PLUS, "+", "0.0", 1),
    Token(TokenType::NUMBER, "3", "3.0", 1),
    Token(TokenType::STAR, "*", "0.0", 1),
    Token(TokenType::NUMBER, "4", "4.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 4: Parentheses
std::vector<Token> test4 = {
    Token(TokenType::LEFT_PAREN, "(", "0.0", 1),
    Token(TokenType::NUMBER, "2", "2.0", 1),
    Token(TokenType::PLUS, "+", "0.0", 1),
    Token(TokenType::NUMBER, "3", "3.0", 1),
    Token(TokenType::RIGHT_PAREN, ")", "0.0", 1),
    Token(TokenType::STAR, "*", "0.0", 1),
    Token(TokenType::NUMBER, "4", "4.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 5: Nested parentheses
std::vector<Token> test5 = {
    Token(TokenType::NUMBER, "2", "2.0", 1),
    Token(TokenType::STAR, "*", "0.0", 1),
    Token(TokenType::LEFT_PAREN, "(", "0.0", 1),
    Token(TokenType::NUMBER, "3", "3.0", 1),
    Token(TokenType::PLUS, "+", "0.0", 1),
    Token(TokenType::LEFT_PAREN, "(", "0.0", 1),
    Token(TokenType::NUMBER, "4", "4.0", 1),
    Token(TokenType::MINUS, "-", "0.0", 1),
    Token(TokenType::NUMBER, "1", "1.0", 1),
    Token(TokenType::RIGHT_PAREN, ")", "0.0", 1),
    Token(TokenType::RIGHT_PAREN, ")", "0.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 6: Unary operators
std::vector<Token> test6 = {
    Token(TokenType::MINUS, "-", "0.0", 1),
    Token(TokenType::NUMBER, "5", "5.0", 1),
    Token(TokenType::PLUS, "+", "0.0", 1),
    Token(TokenType::MINUS, "-", "0.0", 1),
    Token(TokenType::NUMBER, "3", "3.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 7: Division
std::vector<Token> test7 = {
    Token(TokenType::NUMBER, "10", "10.0", 1),
    Token(TokenType::SLASH, "/", "0.0", 1),
    Token(TokenType::NUMBER, "2", "2.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 8: Complex expression
std::vector<Token> test8 = {
    Token(TokenType::NUMBER, "3", "3.0", 1),
    Token(TokenType::PLUS, "+", "0.0", 1),
    Token(TokenType::NUMBER, "4", "4.0", 1),
    Token(TokenType::STAR, "*", "0.0", 1),
    Token(TokenType::NUMBER, "2", "2.0", 1),
    Token(TokenType::MINUS, "-", "0.0", 1),
    Token(TokenType::LEFT_PAREN, "(", "0.0", 1),
    Token(TokenType::NUMBER, "6", "6.0", 1),
    Token(TokenType::SLASH, "/", "0.0", 1),
    Token(TokenType::NUMBER, "3", "3.0", 1),
    Token(TokenType::RIGHT_PAREN, ")", "0.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 9: Single number
std::vector<Token> test9 = {
    Token(TokenType::NUMBER, "42", "42.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 10: Empty expression (should throw an error)
std::vector<Token> test10 = {
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 11: Mismatched parentheses (should throw an error)
std::vector<Token> test11 = {
    Token(TokenType::LEFT_PAREN, "(", "0.0", 1),
    Token(TokenType::NUMBER, "2", "2.0", 1),
    Token(TokenType::PLUS, "+", "0.0", 1),
    Token(TokenType::NUMBER, "3", "3.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};

// Test case 12: Invalid token sequence (should throw an error)
std::vector<Token> test12 = {
    Token(TokenType::NUMBER, "2", "2.0", 1),
    Token(TokenType::PLUS, "+", "0.0", 1),
    Token(TokenType::STAR, "*", "0.0", 1),
    Token(TokenType::NUMBER, "3", "3.0", 1),
    Token(TokenType::END_OF_FILE, "", "EOF", EOF)
};
logTable<std::map<std::string, std::vector<std::string>>> logEntries; // declare variable globally
class debugParser: public parser {
    public:
        explicit debugParser(): parser() {}
        virtual ~debugParser() noexcept = default;
        static void debugEquality(debugParser* p);
};

void debugParser::debugEquality(debugParser* p) {
    p->equality();
    return;
}



parser createParser(std::vector<Token>& tokens) { return parser(tokens);}

static void debugEquality() {
    //std::string source = "if(x == 10){print \"Hello\";}) // End of line";
    //Scanner scanner(source);
    //std::vector<Token> tokens = scanner.ScanTokens();    
     std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "5", "5.0", 1),
        Token(TokenType::PLUS, "+", "0.0", 1),
        Token(TokenType::NUMBER, "3", "3.0", 1),
        Token(TokenType::STAR, "*", "0.0", 1),
        Token(TokenType::NUMBER, "2", "2.0", 1),
        Token(TokenType::END_OF_FILE, "", "EOF", EOF)
     };  
     parser p(tokens);
     debugParser dP;
     dP.debugEquality(&dP);
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
