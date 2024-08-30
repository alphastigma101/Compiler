#include <token.h>
#include <scanner.h>


void debugDefaultConstructor() {
    //Token token;
    return;
}

void ParameterizedConstructor() {
    //Token token(TokenType::IDENTIFIER, "myVar", "myVar", 5);
    return;
}


void debugGetType() {
    Token token(TokenType::NUMBER, "123", "123", 1);
    return;
}


TEST_F(TokenTest, GetLexeme) {
    //Token token(TokenType::STRING, "\"Hello\"", "Hello", 1);
    return;
}


void debugTokenGetLiteral() {
    //Token token(TokenType::STRING, "\"World\"", "World", 1);
    return;
}


void debugGetLine() {
    //Token token(TokenType::PLUS, "+", "+", 10);
    return;
}

void TokenTest, ToString() {
    /*Token token(TokenType::EQUAL, "=", "=", 1);
    std::any result = token.toString();
    ASSERT_TRUE(result.type() == typeid(std::string));
    std::string str_result = std::any_cast<std::string>(result);
    EXPECT_TRUE(str_result.find("EQUAL") != std::string::npos);
    EXPECT_TRUE(str_result.find("=") != std::string::npos);*/
}


TEST_F(TokenTest, MultipleTokens) {
    /*Token token1(TokenType::IF, "if", "if", 1);
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
    EXPECT_EQ(token6.getLexeme(), ")");*/
    return;
}

// Driver Code
int main(void) {
    debugDefaultConstructor();
    ParameterizedConstructor();
    debugGetType();
    debugTokenGetLiteral();
    debugGetLine();
    return 0;
}
