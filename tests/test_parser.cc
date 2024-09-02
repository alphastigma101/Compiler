#include <gtest/gtest.h>
#include "parser.h" 
// TODO optional: Use google test's input parameter generator to test input values
class ParserTest : public testing::Test {
    protected:
        void SetUp() override {
            // Set up any necessary test environment
        }

        void TearDown() override {
            // Clean up after each test
        }

        // Helper function to create a parser with tokens
        parser createParser(const std::vector<Token>& tokens) { return parser(tokens);}
};

// Test equality method
TEST_F(ParserTest, EqualityTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", 1.0, 1),
        Token(TokenType::EQUAL_EQUAL, "==", nullptr, 1),
        Token(TokenType::NUMBER, "1", 1.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test comparison method
TEST_F(ParserTest, ComparisonTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", 1.0, 1),
        Token(TokenType::LESS, "<", nullptr, 1),
        Token(TokenType::NUMBER, "2", 2.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test term method
TEST_F(ParserTest, TermTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", 1.0, 1),
        Token(TokenType::PLUS, "+", nullptr, 1),
        Token(TokenType::NUMBER, "2", 2.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.term();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test factor method
TEST_F(ParserTest, FactorTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "2", 2.0, 1),
        Token(TokenType::STAR, "*", nullptr, 1),
        Token(TokenType::NUMBER, "3", 3.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.factor();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test unary method
TEST_F(ParserTest, UnaryTest) {
    std::vector<Token> tokens = {
        Token(TokenType::MINUS, "-", nullptr, 1),
        Token(TokenType::NUMBER, "5", 5.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.unary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Unary>(*result));
}

// Test primary method with different token types
TEST_F(ParserTest, PrimaryTestNumber) {
    std::vector<Token> tokens = {Token(TokenType::NUMBER, "42", 42.0, 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestString) {
    std::vector<Token> tokens = {Token(TokenType::STRING, "hello", "hello", 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestTrue) {
    std::vector<Token> tokens = {Token(TokenType::TRUE, "true", true, 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestFalse) {
    std::vector<Token> tokens = {Token(TokenType::FALSE, "false", false, 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestNil) {
    std::vector<Token> tokens = {Token(TokenType::NIL, "nil", nullptr, 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestGrouping) {
    std::vector<Token> tokens = {
        Token(TokenType::LEFT_PAREN, "(", nullptr, 1),
        Token(TokenType::NUMBER, "42", 42.0, 1),
        Token(TokenType::RIGHT_PAREN, ")", nullptr, 1)
    };
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Grouping>(*result));
}

// Test expression method
TEST_F(ParserTest, ExpressionTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", 1.0, 1),
        Token(TokenType::PLUS, "+", nullptr, 1),
        Token(TokenType::NUMBER, "2", 2.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.expression();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test parse method
TEST_F(ParserTest, ParseTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", 1.0, 1),
        Token(TokenType::PLUS, "+", nullptr, 1),
        Token(TokenType::NUMBER, "2", 2.0, 1)
    };
    parser p = createParser(tokens);
    auto result = p.parse();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test error handling
TEST_F(ParserTest, ParseErrorTest) {
    std::vector<Token> tokens = {
        Token(TokenType::LEFT_PAREN, "(", nullptr, 1),
        Token(TokenType::NUMBER, "42", 42.0, 1)
        // Missing RIGHT_PAREN
    };
    parser p = createParser(tokens);
    auto result = p.parse();
    EXPECT_EQ(result, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
