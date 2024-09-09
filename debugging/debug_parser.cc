#include <parser.h>
#include <scanner.h>
void runTest(const std::string& input) {
    std::cout << "Testing input: " << input << std::endl;
    
    // Create scanner and generate tokens
    Scanner scanner(input);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    // Print tokens for debugging
    std::cout << "Tokens:" << std::endl;
    for (auto& token : tokens) {
        std::string temp = std::any_cast<std::string>(token.toString());
        std::cout << temp << std::endl;
    }
    
    // Parse tokens
    parser p(tokens);
    auto result = p.parse();
    
    // Print result or error
    if (result) {
        std::cout << "Parsing successful!" << std::endl;
        // You might want to add a method to print the AST here
    } else {
        std::cout << "Parsing failed." << std::endl;
    }
    
    std::cout << "------------------------" << std::endl;
}

logTable<std::map<std::string, std::vector<std::string>>> logEntries; // declare variable globally
class debugParser: public parser {
    public:
        explicit debugParser(): parser() {}
        virtual ~debugParser() noexcept = default;
        static void debugEquality(debugParser* p);
};

void debugParser::debugEquality(debugParser* p) {
    //p->equality();
    return;
}


parser createParser(std::vector<Token>& tokens) { return parser(tokens);}

static void debugEquality() {
    const std::vector<std::string> testCases = {
        "3 + 4",
        "5 * 6",
        "2 + 3 * 4",
        "(2 + 3) * 4",
        "2 * (3 + (4 - 1))",
        "-5 + -3",
        "10 / 2",
        "3 + 4 * 2 + (6 / 3)",
        "13 + 34 * 2 - (6 / 2)",
        "33 + 34 * 2 / (6 / 3)",

        //"42",
        //"",
        "(2 / 3) / 5",
        //"2 + * 3"
    };  
    /*for (int i = 0; i < test_strings.size(); i++) {
        Scanner scanner(test_strings[i]);
        std::vector<Token> tokens = scanner.ScanTokens();
        parser p(tokens);
        p.equality();
    }*/
    for (const auto& testCase : testCases) {
        runTest(testCase);
    }
    //debugParser dP;
    //dP.debugEquality(&dP);
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
