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
Binary::Binary(Expr* left_, const Token& op_, Expr* right_) {
    this->left = std::move(left_);
    this->right = std::move(right_);
    this->op = std::move(op_);
    auto binary = compressedAstTree(idx + 1, String("Binary"), this);
    cTree.insert(std::move(binary));
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
Unary::Unary(Expr* right_, const Token& op_)  {
   this->right = std::move(right_);
   this->op = std::move(op_);
   auto unary = compressedAstTree(idx + 1, String("Unary"), this);
   cTree.insert(std::move(unary));
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
Grouping::Grouping(Expr* expression) {
    this->expression = std::move(expression);
    auto grouping = compressedAstTree(idx + 1, String("Grouping"), this);
    cTree.insert(std::move(grouping));
}

Literal::Literal(const Token&& oP) {
    try { 
        this->op = std::move(oP); 
        auto literal = compressedAstTree(idx + 1, String("Literal"), this);
        cTree.insert(std::move(literal));
    }
    catch(...) {
        catcher<Literal> cl("Undefined behavior occurred in Class Literal!");
        throw cl;
    }
}

Methods::Methods(Expr* meth, const Token& op_) {


}

Arguments::Arguments(Expr* arg, const Token& op_) {

}

EcoSystem::EcoSystem(Expr* ecoSystem, const Token& op_) {


}
// Helper methods for constructing the AST
//
//
String Binary::parenthesize(String name, Expr* left, Expr* right) {
    String result = "(" + name;
    if (left) {
        result += " " + left->accept(this);
    }
    if (right) {
        result += " " + right->accept(this);
    }
    return result + ")";
}

String Unary::parenthesize(String name, Expr* expr) {
    String result = "(" + name + " ";
    if (expr) result += expr->accept(this);
    return result + ")";
}

String Grouping::parenthesize(String name, Expr* expr) {
    String result = "(" + name + " ";
    if (expr) result += expr->accept(this);
    return result + ")";
}
//
String Methods::parenthesize(String name, Expr* expr) {
    /*builder.append("(").append(name);
    for (Expr expr : exprs) {
      builder.append(" ");
      builder.append(expr.accept(this));
    }
    builder.append(")");

    return builder.toString();*/
    return "\0";
}
//
String Arguments::parenthesize(String name, Expr* expr) {
    /*builder.append("(").append(name);
    for (Expr expr : exprs) {
      builder.append(" ");
      builder.append(expr.accept(this));
    }
    builder.append(")");

    return builder.toString();*/
    return "\0";
}
//
String EcoSystem::parenthesize(String name, Expr* expr) {
    /*builder.append("(").append(name);
    for (Expr expr : exprs) {
      builder.append(" ");
      builder.append(expr.accept(this));
    }
    builder.append(")");

    return builder.toString();*/
    return "\0";
}
#if ENABLE_TREE_BUILD
   Set<astTree<int, String, ExprVariant>> cTree;
#endif
