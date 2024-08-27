#include <gtest/gtest.h>
#include "scanner.h"

class ScannerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Teardown code if needed
    }
};

// Test the constructor
TEST_F(ScannerTest, ConstructorTest) {
    std::string source = "var x = 5;";
    Scanner scanner(source);
    EXPECT_EQ(scanner.Source, source);
}

// Test scanning of single-character tokens
TEST_F(ScannerTest, SingleCharacterTokens) {
    std::string source = "(){},.-+;*";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 10); // 9 tokens + EOF
    EXPECT_EQ(tokens[0].type, TokenType::LEFT_PAREN);
    EXPECT_EQ(tokens[1].type, TokenType::RIGHT_PAREN);
    EXPECT_EQ(tokens[2].type, TokenType::LEFT_BRACE);
    EXPECT_EQ(tokens[3].type, TokenType::RIGHT_BRACE);
    EXPECT_EQ(tokens[4].type, TokenType::COMMA);
    EXPECT_EQ(tokens[5].type, TokenType::DOT);
    EXPECT_EQ(tokens[6].type, TokenType::MINUS);
    EXPECT_EQ(tokens[7].type, TokenType::PLUS);
    EXPECT_EQ(tokens[8].type, TokenType::SEMICOLON);
    EXPECT_EQ(tokens[9].type, TokenType::END_OF_FILE);
}

// Test scanning of double-character tokens
TEST_F(ScannerTest, DoubleCharacterTokens) {
    std::string source = "!= == <= >=";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 5); // 4 tokens + EOF
    EXPECT_EQ(tokens[0].type, TokenType::BANG_EQUAL);
    EXPECT_EQ(tokens[1].type, TokenType::EQUAL_EQUAL);
    EXPECT_EQ(tokens[2].type, TokenType::LESS_EQUAL);
    EXPECT_EQ(tokens[3].type, TokenType::GREATER_EQUAL);
}

// Test scanning of keywords
TEST_F(ScannerTest, Keywords) {
    std::string source = "and class else if while var";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 7); // 6 tokens + EOF
    EXPECT_EQ(tokens[0].type, TokenType::AND);
    EXPECT_EQ(tokens[1].type, TokenType::CLASS);
    EXPECT_EQ(tokens[2].type, TokenType::ELSE);
    EXPECT_EQ(tokens[3].type, TokenType::IF);
    EXPECT_EQ(tokens[4].type, TokenType::WHILE);
    EXPECT_EQ(tokens[5].type, TokenType::VAR);
}

// Test scanning of identifiers
TEST_F(ScannerTest, Identifiers) {
    std::string source = "variable_name anotherVar _underscoreVar";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 4); // 3 tokens + EOF
    EXPECT_EQ(tokens[0].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
}

// Test scanning of numbers
TEST_F(ScannerTest, Numbers) {
    std::string source = "123 45.67";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 3); // 2 tokens + EOF
    EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[0].literal, "123");
    EXPECT_EQ(tokens[1].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[1].literal, "45.67");
}

// Test scanning of strings
TEST_F(ScannerTest, Strings) {
    std::string source = "\"Hello, World!\" \"Another string\"";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 3); // 2 tokens + EOF
    EXPECT_EQ(tokens[0].type, TokenType::STRING);
    EXPECT_EQ(tokens[0].literal, "Hello, World!");
    EXPECT_EQ(tokens[1].type, TokenType::STRING);
    EXPECT_EQ(tokens[1].literal, "Another string");
}

// Test scanning of comments
TEST_F(ScannerTest, Comments) {
    std::string source = "// This is a comment\nvar x = 5;";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 5); // 4 tokens + EOF
    EXPECT_EQ(tokens[0].type, TokenType::VAR);
    EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].type, TokenType::EQUAL);
    EXPECT_EQ(tokens[3].type, TokenType::NUMBER);
}

// Test error handling (e.g., unterminated string)
TEST_F(ScannerTest, UnterminatedString) {
    std::string source = "\"This string never ends";
    Scanner scanner(source);
    
    testing::internal::CaptureStdout();
    std::vector<Token> tokens = scanner.ScanTokens();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Unterminated string") != std::string::npos);
}

// Test a complex case combining multiple elements
TEST_F(ScannerTest, ComplexCase) {
    std::string source = "if (x == 10) { print \"Hello\"; } // End of line";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 11); // 10 tokens + EOF
    EXPECT_EQ(tokens[0].type, TokenType::IF);
    EXPECT_EQ(tokens[1].type, TokenType::LEFT_PAREN);
    EXPECT_EQ(tokens[2].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[3].type, TokenType::EQUAL_EQUAL);
    EXPECT_EQ(tokens[4].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[5].type, TokenType::RIGHT_PAREN);
    EXPECT_EQ(tokens[6].type, TokenType::LEFT_BRACE);
    EXPECT_EQ(tokens[7].type, TokenType::PRINT);
    EXPECT_EQ(tokens[8].type, TokenType::STRING);
    EXPECT_EQ(tokens[9].type, TokenType::RIGHT_BRACE);
}

// Driver Code
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
