#include <abstraction_tree_syntax.h>
#include <gtest/gtest.h>
#include <filesystem>
//#include <tuple>

// Test fixture for AbstractionTreeSyntax classes
class AbstractionTreeSyntaxTest : public testing::Test {
    protected:
        void SetUp() override {
            // Set up any necessary test environment
        }

        void TearDown() override {
            // Clean up after each test
        }
};

// Test compressedAstTree function
TEST(CompressedAstTreeTest, ReturnsCorrectTuple) {
    auto result = compressedAstTree(1, "test", 3.14);
    EXPECT_EQ(std::get<0>(result), 1);
    EXPECT_EQ(std::get<1>(std::get<1>(result)), "test");
    EXPECT_FLOAT_EQ(std::get<2>(std::get<1>(result)), 3.14);
}

// Test generateAst constructor
TEST_F(AbstractionTreeSyntaxTest, GenerateAstConstructor) {
    EXPECT_NO_THROW({
        generateAst ast;
    });
}

// Test generateAst constructor with invalid path
TEST_F(AbstractionTreeSyntaxTest, GenerateAstConstructorInvalidPath) {
    // Temporarily set an invalid environment variable
    setenv("Public-Projects", "/invalid/path", 1);
    EXPECT_THROW({
        generateAst ast;
    }, catcher);
    // Reset the environment variable
    unsetenv("Public-Projects");
}

// Test ast constructor
TEST_F(AbstractionTreeSyntaxTest, AstConstructor) {
    ExprTypes expr; // You need to define this type and provide a valid instance
    EXPECT_NO_THROW({
        ast tree(expr);
    });
}

// Test ast setTable and getTable methods
TEST_F(AbstractionTreeSyntaxTest, AstSetAndGetTable) {
    ExprTypes expr; // You need to define this type and provide a valid instance
    ast tree(expr);
    tree.setTable();
    EXPECT_NO_THROW({
        Table table = tree.getTable();
    });
}

// Test analyzeSemantics constructor
TEST_F(AbstractionTreeSyntaxTest, AnalyzeSemanticsConstructor) {
    ExprTypes expr; // You need to define this type and provide a valid instance
    ast tree(expr);
    EXPECT_NO_THROW({
        analyzeSemantics semantics(tree);
    });
}

// Test intermediateRepresentation constructor and generate method
TEST_F(AbstractionTreeSyntaxTest, IntermediateRepresentationConstructorAndGenerate) {
    ExprTypes expr; // You need to define this type and provide a valid instance
    ast tree(expr);
    analyzeSemantics semantics(tree);
    EXPECT_NO_THROW({
        intermediateRepresentation ir(semantics);
        ir.generate();
    });
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
