#include <context_free_grammar.h>

/** --------------------------------------------------------------------------
 * @brief This class will represent the Binary node tree in a absraction syntax tree
 *
 * @details it moves the left and right variant resources and the token resources that were passed into it 
 *          to it's own data members 
 *
 * @param left_ an object that was recrusively called to the left 
 * @param right_ an object that was recrusively called to the right
 * @param op_ is an instance of the token class 
 *
 * @details the parameters for this constructor are unique such that they are only useful when used with the parser 
 *
 * ---------------------------------------------------------------------------
*/
Binary::Binary(std::shared_ptr<ExprVariant>& left_, const Token& op_, std::shared_ptr<ExprVariant>& right_) {
    try {
        Left = std::move(left_); // move the current left_ resources memory location into Left 
        Right = std::move(right_);
        op = std::make_shared<Token>(op_);
    }
    catch(...) {
        catcher<Binary> cb("Undefined behavior occurred in Class Binary!");
        throw cb;
    }
}
/** --------------------------------------------------------------------------
 * @brief This class will represent the Binary node tree in a absraction syntax tree
 *
 * @details it moves the right variant resources and the token resources that were passed into it 
 *          to it's own data members 
 *
 * @param right_ an object that was recrusively called to the right
 * @param op_ is a indexed element from a vector of token instances 
 *
 * @details the parameters for this constructor are unique such that they are only useful when used with the parser 
 *
 * ---------------------------------------------------------------------------
*/
Unary::Unary(std::shared_ptr<ExprVariant>& right_, const Token& op_)  {
    try {
        Right = std::move(right_);
        op = std::make_shared<Token>(op_);
    }
    catch(...) {
        catcher<Unary> cu("Undefined behavior occurred in Class Unary!");
        throw cu;
    }
}
/** ---------------------------------------------------------------
 * @brief Initializes the expression_ and moves the resources into it 
 *
 * @param expression is a type of variant that is wrapped in a shared_ptr 
 * @param oP is a indexed element from a vector of Token instances
 *
 * @detials Moves left's stored pointer resources into data member Left 
 * @detials with left's and Right with the
 * @detials 1. A snippet of the ast tree would look like: ...., Binary, Grouping, Binary, Binary, Grouping
 * @detials 2. A snippet of the ast tree would look like: ...., Binary, Grouping, Binary, Unary, Unary, Grouping
 * @detials 3. A snippet of the ast tree would look like: ...., Binary, Grouping, Grouping, Unary, Unary, Grouping, Binary, Grouping, Grouping
 * ----------------------------------------------------------------
*/
Grouping::Grouping(std::shared_ptr<ExprVariant>& expression, Token&& oP) {
    if (oP.getLexeme() == "(") {
        Left = std::move(expression);
        op = std::make_shared<Token>(std::move(oP));
    }
    else if (oP.getLexeme() == ")") {
        Right = std::move(expression);
        op = std::make_shared<Token>(std::move(oP));
    }
}



