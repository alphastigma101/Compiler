#include <gtest/gtest.h>
#include "token.h" // Make sure to include your Token class header

class TokenTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Teardown code if needed
    }
};

// Test the default constructor
TEST_F(TokenTest, DefaultConstructor) {
    Token token;
    EXPECT_EQ(token.getType(), TokenType()); // Assuming TokenType has a default constructor
    EXPECT_EQ(token.getLexeme(), "");
    EXPECT_EQ(token.getLiteral(), "");
    EXPECT_EQ(token.getLine(), 0);
}

// Test the parameterized constructor
TEST_F(TokenTest, ParameterizedConstructor) {
    Token token(TokenType::IDENTIFIER, "myVar", "myVar", 5);
    EXPECT_EQ(token.getType(), TokenType::IDENTIFIER);
    EXPECT_EQ(token.getLexeme(), "myVar");
    EXPECT_EQ(token.getLiteral(), "myVar");
    EXPECT_EQ(token.getLine(), 5);
}

// Test getType method
TEST_F(TokenTest, GetType) {
    Token token(TokenType::NUMBER, "123", "123", 1);
    EXPECT_EQ(token.getType(), TokenType::NUMBER);
}

// Test getLexeme method
TEST_F(TokenTest, GetLexeme) {
    Token token(TokenType::STRING, "\"Hello\"", "Hello", 1);
    EXPECT_EQ(token.getLexeme(), "\"Hello\"");
}

// Test getLiteral method
TEST_F(TokenTest, GetLiteral) {
    Token token(TokenType::STRING, "\"World\"", "World", 1);
    EXPECT_EQ(token.getLiteral(), "World");
}

// Test getLine method
TEST_F(TokenTest, GetLine) {
    Token token(TokenType::PLUS, "+", "+", 10);
    EXPECT_EQ(token.getLine(), 10);
}

// Test toString method
TEST_F(TokenTest, ToString) {
    Token token(TokenType::EQUAL, "=", "=", 1);
    std::any result = token.toString();
    ASSERT_TRUE(result.type() == typeid(std::string));
    std::string str_result = std::any_cast<std::string>(result);
    EXPECT_TRUE(str_result.find("EQUAL") != std::string::npos);
    EXPECT_TRUE(str_result.find("=") != std::string::npos);
}

// Test multiple tokens
TEST_F(TokenTest, MultipleTokens) {
    Token token1(TokenType::IF, "if", "if", 1);
    Token token2(TokenType::LEFT_PAREN, "(", "(", 1);
    Token token3(TokenType::IDENTIFIER, "x", "x", 1);
    Token token4(TokenType::GREATER, ">", ">", 1);
    Token token5(TokenType::NUMBER, "5", "5", 1);
    Token token6(TokenType::RIGHT_PAREN, ")", ")", 1);

    EXPECT_EQ(token1.getType(), TokenType::IF);
    EXPECT_EQ(token2.getType(), TokenType::LEFT_PAREN);
    EXPECT_EQ(token3.getType(), TokenType::IDENTIFIER);
    EXPECT_EQ(token4.getType(), TokenType::GREATER);
    EXPECT_EQ(token5.getType(), TokenType::NUMBER);
    EXPECT_EQ(token6.getType(), TokenType::RIGHT_PAREN);

    EXPECT_EQ(token1.getLexeme(), "if");
    EXPECT_EQ(token2.getLexeme(), "(");
    EXPECT_EQ(token3.getLexeme(), "x");
    EXPECT_EQ(token4.getLexeme(), ">");
    EXPECT_EQ(token5.getLexeme(), "5");
    EXPECT_EQ(token6.getLexeme(), ")");
}

// Driver Code
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
