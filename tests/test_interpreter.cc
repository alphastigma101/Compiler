#include <gtest/gtest.h>
#include "interpreter.h" // Include the header file for your interpreter class

class InterpreterTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any necessary test environment
    }

    void TearDown() override {
        // Clean up after each test
    }

    // Helper function to create an interpreter with expressions and language
    interpreter createInterpreter(ExprTypes<Binary, Unary, Grouping, Literal>& expr, LanguageTokenTypes& lang) {
        return interpreter(expr, lang);
    }
};

// Test interpreter constructor
TEST_F(InterpreterTest, ConstructorTest) {
    ExprTypes<Binary, Unary, Grouping, Literal> expr;
    LanguageTokenTypes lang = LanguageTokenTypes::Python;
    EXPECT_NO_THROW({
        interpreter interp(expr, lang);
    });
}

// Test visitUnaryExpr method
TEST_F(InterpreterTest, VisitUnaryExprTest) {
    ExprTypes<Binary, Unary, Grouping, Literal> expr;
    LanguageTokenTypes lang = LanguageTokenTypes::Python;
    interpreter interp = createInterpreter(expr, lang);
    
    std::any unaryExpr = Unary(Token(TokenType::MINUS, "-", nullptr, 1), Literal(5.0));
    auto result = interp.visitUnaryExpr(unaryExpr);
    EXPECT_EQ(std::any_cast<double>(result), -5.0);
}

// Test visitBinaryExpr method
TEST_F(InterpreterTest, VisitBinaryExprTest) {
    ExprTypes<Binary, Unary, Grouping, Literal> expr;
    LanguageTokenTypes lang = LanguageTokenTypes::Python;
    interpreter interp = createInterpreter(expr, lang);
    
    std::any binaryExpr = Binary(Literal(3.0), Token(TokenType::PLUS, "+", nullptr, 1), Literal(4.0));
    auto result = interp.visitBinaryExpr(binaryExpr);
    EXPECT_EQ(std::any_cast<double>(result), 7.0);
}

// Test isTruthy method for Python
TEST_F(InterpreterTest, IsTruthyPythonTest) {
    ExprTypes<Binary, Unary, Grouping, Literal> expr;
    LanguageTokenTypes lang = LanguageTokenTypes::Python;
    interpreter interp = createInterpreter(expr, lang);
    
    EXPECT_TRUE(interp.isTruthy(true));
    EXPECT_FALSE(interp.isTruthy(LanguageTokenTypes::Python::None()));
    EXPECT_TRUE(interp.isTruthy(1));
    EXPECT_FALSE(interp.isTruthy(false));
}

// Test isTruthy method for JavaScript
TEST_F(InterpreterTest, IsTruthyJavaScriptTest) {
    ExprTypes<Binary, Unary, Grouping, Literal> expr;
    LanguageTokenTypes lang = LanguageTokenTypes::JavaScript;
    interpreter interp = createInterpreter(expr, lang);
    
    EXPECT_TRUE(interp.isTruthy(true));
    EXPECT_FALSE(interp.isTruthy(LanguageTokenTypes::JavaScript::Null()));
    EXPECT_FALSE(interp.isTruthy(LanguageTokenTypes::JavaScript::Undefined()));
    EXPECT_TRUE(interp.isTruthy(1));
    EXPECT_FALSE(interp.isTruthy(false));
}

// Test arithmetic operations for different languages
TEST_F(InterpreterTest, ArithmeticOperationsTest) {
    ExprTypes<Binary, Unary, Grouping, Literal> expr;
    std::vector<LanguageTokenTypes> languages = {
        LanguageTokenTypes::Python,
        LanguageTokenTypes::JavaScript,
        LanguageTokenTypes::Ruby,
        LanguageTokenTypes::CPP
    };

    for (auto lang : languages) {
        interpreter interp = createInterpreter(expr, lang);
        std::any binaryExpr = Binary(Literal(10.0), Token(TokenType::MINUS, "-", nullptr, 1), Literal(3.0));
        auto result = interp.visitBinaryExpr(binaryExpr);
        EXPECT_EQ(std::any_cast<double>(result), 7.0);
    }
}

// Test error handling for unsupported operations
TEST_F(InterpreterTest, UnsupportedOperationTest) {
    ExprTypes<Binary, Unary, Grouping, Literal> expr;
    LanguageTokenTypes lang = LanguageTokenTypes::Shell;
    interpreter interp = createInterpreter(expr, lang);
    
    std::any unaryExpr = Unary(Token(TokenType::MINUS, "-", nullptr, 1), Literal(5.0));
    EXPECT_THROW({
        interp.visitUnaryExpr(unaryExpr);
    }, std::runtime_error);
}

// Test custom language support
TEST_F(InterpreterTest, CustomLanguageTest) {
    ExprTypes<Binary, Unary, Grouping, Literal> expr;
    LanguageTokenTypes lang = LanguageTokenTypes::Custom;
    interpreter interp = createInterpreter(expr, lang);
    
    std::any binaryExpr = Binary(Literal(5.0), Token(TokenType::PLUS, "+", nullptr, 1), Literal(3.0));
    auto result = interp.visitBinaryExpr(binaryExpr);
    EXPECT_EQ(std::any_cast<double>(result), 8.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
