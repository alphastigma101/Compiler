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
Binary::Binary(Unique<Expr> left_, const Token& op_, Unique<Expr> right_) {
    try {
        if (left_.get() != nullptr) {
            if (left_.get()->op.get() != nullptr) {
                this->left = std::move(left_);
            }
            else {left_.release();}
        }
        else {left_.release();}
        if (right_.get() != nullptr) {
            if (right_.get()->op.get() != nullptr) {
              this->right = std::move(right_);
            }
            else {right_.release();} 
        }
        else {right_.release();}
        this->op = std::make_unique<Token>(std::move(op_));
    }
    catch(...) {
        catcher<Binary> cb("Undefined behavior occurred in Class Binary!");
        throw cb;
    }
}
/** ----------------------------
 * @brief A constructor for converting an Abstract class that uses unique_ptrs into a concrete class 
 * 
 * @param expr the resources that need to be moved over
 * 
 * @details This is needed to convert the abstract class into a concrete class by binding this argument
 *          and moving it over to the right object 
 * @details Whenever you get a compiler error, you most likely need convert something into something, when you're using smart pointers. 
 *          So create a constructor that does such a thing. This is a Binary example.
 * ------------------------------
*/
Binary::Binary(Unique<Expr> expr, bool move) noexcept {
    if (move == true) { this->left = std::move(expr); }
    else { this->right = std::move(expr); }
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
Unary::Unary(Unique<Expr> right_, const Token& op_)  {
    try {
        if (right_.get() != nullptr) {
            if (right_.get()->op.get() != nullptr) {
               auto unary = compressedAstTree(idx, String("Unary"), right_.get());
               cTree.push_back(std::move(unary));
               idx++;
            }
            else {right_.release();} 
        }
        else {right_.release();}
        this->op = std::make_unique<Token>(op_);
    }
    catch(...) {
        catcher<Unary> cu("Undefined behavior occurred in Class Unary!");
        throw cu;
    }
}
/** ----------------------------
 * @brief A constructor for converting an Abstract class that uses unique_ptrs into a concrete class 
 * 
 * @param expr the resources that need to be moved over
 * 
 * @details This is needed to convert the abstract class into a concrete class by binding this argument
 *          and moving it over to the right object 
 * @details Whenever you get a compiler error, you most likely need convert something into something, when you're using smart pointers. 
 *          So create a constructor that does such a thing. This is an Unary example 
 * ------------------------------
*/
Unary::Unary(Unique<Expr> expr) noexcept {
    this->right = std::move(expr);
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
Grouping::Grouping(Unique<Expr> expression) {
    if (expression->left.get() != nullptr ) {
        auto binary = compressedAstTree(idx, String("Binary"), expression->left.get());
        cTree.push_back(std::move(binary));
        idx++;
    }
    if (expression->right.get() != nullptr) {
        auto binary = compressedAstTree(idx, String("Binary"), expression->right.get());
        cTree.push_back(std::move(binary));
        idx++;
    }
    if (expression.get() != nullptr) {
        if (expression.get()->op.get() != nullptr) {
            auto grouping = compressedAstTree(idx, String("Grouping"), std::make_unique<Grouping>(std::move(expression), true));
            cTree.push_back(std::move(grouping));
            idx++;
        }
        else {expression.release(); }
    }
    else {expression.release(); }
}
/** -----------------------------------
 * @brief Move the sources over back to the grouping instance
 * 
 * @details Will get called in if a template that has user defined types inside of it match the arguments below.
 *          Refer to Grouping(Unique<Expr> expression) scope for more info
 * @param expression The resources you are wanting to transfer ownership over too
 * @param move To determine if resources should be moved or not 
*/
Grouping::Grouping(Unique<Expr> expression, bool move) {
   if (move) { this->expression = std::move(expression); }
}

Literal::Literal(const Token&& oP) {
    try {
        this->op = std::make_unique<Token>(std::move(oP));
    }
    catch(...) {
        catcher<Literal> cl("Undefined behavior occurred in Class Literal!");
        throw cl;
    }
}

Methods::Methods(Unique<Expr> meth, const Token& op_) {


}

Arguments::Arguments(Unique<Expr> arg, const Token& op_) {

}

EcoSystem::EcoSystem(Unique<Expr> ecoSystem, const Token& op_) {


}
// Helper methods for constructing the AST
//
//
String Binary::parenthesize(String name, Expr* right, Expr* left) {
    String result;
    result += "(" + name;
    result += " ";
    if (auto literal = dynamic_cast<Literal*>(left)) result += literal->accept(*literal);
    if (auto literal = dynamic_cast<Literal*>(right))  result += literal->accept(*literal);
    return result;
}
//
String Unary::parenthesize(String name, Expr& expr) {
    String result;
    result += "(" + name;
    result += " ";
    if (auto literal = dynamic_cast<Literal*>(&expr)) result += literal->accept(*literal);
    return result + ")";
}
//
String Grouping::parenthesize(String name, Expr& expr) {
    String result;
    //result += "(" + name;
    result += " ";
    if (auto binary = dynamic_cast<Binary*>(&expr)) result += binary->accept(*binary);
    result += " ";
    return result;
}
//
String Literal::visit(Literal&& expr) {
    if (expr.getToken().getTypeStr() == "NULL" || expr.getToken().getTypeStr() == "NIL") return "null";
    return " " + expr.getToken().getLiteral();
}
//
String Methods::parenthesize(String name, Expr& expr) {
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
String Methods::visit(Methods&& expr) {
    return "\0";
}
//
String Methods::accept(Methods&) {
    return visit(std::move(*this));
}
//
String Arguments::parenthesize(String name, Expr& expr) {
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
String Arguments::visit(Arguments&& expr) {
    return "\0";
}
//
String Arguments::accept(Arguments&) {
    return visit(std::move(*this));
}
//
String EcoSystem::parenthesize(String name, Expr& expr) {
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
String EcoSystem::visit(EcoSystem&& expr) {
    return "\0";
}
//
String EcoSystem::accept(EcoSystem&) {
    return visit(std::move(*this));
}

#if ENABLE_TREE_BUILD
   Vector<astTree<int, String, ExprVariant>> cTree;
#endif
