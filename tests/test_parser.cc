#include <gtest/gtest.h>
#include <parser.h>
#include <scanner.h>
// TODO optional: Use google test's input parameter generator to test input values
logTable<std::map<std::string, std::vector<std::string>>> logEntries; // declare variable globally
class ParserTest : public testing::Test {
    protected:
        void SetUp() override {
            // Set up any necessary test environment
        }

        void TearDown() override {
            // Clean up after each test
        }

        // Helper function to create a parser with tokens
        parser createParser(std::vector<Token>& tokens) { return parser(tokens);}
};
// Test equality for "1 == 1"
TEST_F(ParserTest, EqualityTest_1_equals_1) {
    Scanner scanner("1 == 1");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test equality for "2 != 3"
TEST_F(ParserTest, EqualityTest_2_not_equals_3) {
    Scanner scanner("2 != 3");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test equality for "true == true"
TEST_F(ParserTest, EqualityTest_true_equals_true) {
    Scanner scanner("true == true");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test equality for "false != true"
TEST_F(ParserTest, EqualityTest_false_not_equals_true) {
    Scanner scanner("false != true");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test equality for "'hello' == 'hello'"
TEST_F(ParserTest, EqualityTest_hello_equals_hello) {
    Scanner scanner("'hello' == 'hello'");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test equality for "'world' != 'World'"
TEST_F(ParserTest, EqualityTest_world_not_equals_World) {
    Scanner scanner("'world' != 'World'");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
// Test equality for "42 != 42.0"
TEST_F(ParserTest, EqualityTest_float_integer) {
    Scanner scanner("42 == 42.0");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
// Test equality for "42 != 42.0"
TEST_F(ParserTest, EqualityTest_float_float) {
    Scanner scanner("3.14 != 3.14159");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
// Test equality for "1 == 2 == false"
TEST_F(ParserTest, EqualityTest_one_equals_2_equals_false) {
    Scanner scanner("1 == 2 == false");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
// Test equality for "42 != 42.0"
TEST_F(ParserTest, EqualityTest_one_not_equal_two_not_equal) {
    Scanner scanner("1 != 2 != false");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}


TEST_F(ParserTest, one_doesnt_equal_one) {
   Scanner scanner("(1 != 1) == false");
   std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, true_equals_false) {
    Scanner scanner("true == !false");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, zero_equals_false) {
    Scanner scanner("0 == false");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));

}

TEST_F(ParserTest, EqualityTest_5) {
    Scanner scanner("1 == true");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));

}

TEST_F(ParserTest, EqualityTest_6) {
   Scanner scanner("'' == false");
   std::vector<Token> tokens = scanner.ScanTokens();
   parser p = createParser(tokens);
   auto result = p.equality();
   ASSERT_NE(result, nullptr);
   EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_7) {
    Scanner scanner("'0' != 0");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

/*TEST_F(ParserTest, EqualityTest_8) {
    Scanner scanner("null != undefined");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_9) {
    Scanner scanner("[] == []");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_10) {
    Scanner scanner("{} != {}");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_11) {
    Scanner scanner("Infinity == Infinity");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_12) {
    Scanner scanner("NaN != NaN");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_13) {
    Scanner scanner("(1 < 2) == (3 > 2)");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_14) {
    Scanner scanner("(1 <= 1) != (2 >= 3)");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}*/



// Test comparison method
TEST_F(ParserTest, ComparisonTest) {
    std::vector<std::string> test_str = {
        "1 < 2",
        "3 > 4",
        "5 <= 6",
        "7 >= 8",
        "9 == 10",
        "11 != 12",
        "13 < 14 < 15",
        "16 > 17 > 18",
        "19 <= 20 <= 21",
        "22 >= 23 >= 24",
        "25 == 26 == 27",
        "28 != 29 != 30",
        "31 < 32 > 33 <= 34 >= 35 == 36 != 37",
        "true < false",
        //std::string("apple" + ">" + "banana"),
        "null <= 42",
        "3.14 >= 2.71"
    };
    Scanner scanner(test_str[3]);
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test term method
/*TEST_F(ParserTest, TermTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", "1.0", 1),
        Token(TokenType::PLUS, "+", "", 1),
        Token(TokenType::NUMBER, "2", "2.0", 1)
    };
    parser p = createParser(tokens);
    auto result = p.term();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test factor method
TEST_F(ParserTest, FactorTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "2", "2.0", 1),
        Token(TokenType::STAR, "*", "", 1),
        Token(TokenType::NUMBER, "3", "3.0", 1)
    };
    parser p = createParser(tokens);
    auto result = p.factor();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test unary method
TEST_F(ParserTest, UnaryTest) {
    std::vector<Token> tokens = {
        Token(TokenType::MINUS, "-", "", 1),
        Token(TokenType::NUMBER, "5", "5.0", 1)
    };
    parser p = createParser(tokens);
    auto result = p.unary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Unary>(*result));
}

// Test primary method with different token types
TEST_F(ParserTest, PrimaryTestNumber) {
    std::vector<Token> tokens = {Token(TokenType::NUMBER, "42", "42.0", 1)};
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
    std::vector<Token> tokens = {Token(TokenType::TRUE, "true", "true", 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestFalse) {
    std::vector<Token> tokens = {Token(TokenType::FALSE, "false", "false", 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestNil) {
    std::vector<Token> tokens = {Token(TokenType::NIL, "nil", "", 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestGrouping) {
    std::vector<Token> tokens = {
        Token(TokenType::LEFT_PAREN, "(", "", 1),
        Token(TokenType::NUMBER, "42", "42.0", 1),
        Token(TokenType::RIGHT_PAREN, ")", "", 1)
    };
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Grouping>(*result));
}

// Test expression method
TEST_F(ParserTest, ExpressionTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", "1.0", 1),
        Token(TokenType::PLUS, "+", "", 1),
        Token(TokenType::NUMBER, "2", "2.0", 1)
    };
    parser p = createParser(tokens);
    auto result = p.expression();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test parse method
TEST_F(ParserTest, ParseTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", "1.0", 1),
        Token(TokenType::PLUS, "+", "", 1),
        Token(TokenType::NUMBER, "2", "2.0", 1)
    };
    parser p = createParser(tokens);
    auto result = p.parse();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test error handling
TEST_F(ParserTest, ParseErrorTest) {
    std::vector<Token> tokens = {
        Token(TokenType::LEFT_PAREN, "(", "", 1),
        Token(TokenType::NUMBER, "42", "42.0", 1)
        // Missing RIGHT_PAREN
    };
    parser p = createParser(tokens);
    auto result = p.parse();
    EXPECT_EQ(result, nullptr);
}*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
