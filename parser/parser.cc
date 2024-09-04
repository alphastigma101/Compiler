#include <parser.h>
template struct std::shared_ptr<std::variant<Binary, Grouping, Literal>>;
ExprTypes<Binary, Unary, Grouping, Literal> parser::expr;
std::vector<std::variant<Binary, Unary, Grouping, Literal>> parser::instances_;

/**--------------------------------------------------------------------------
 * @brief default constructor that initalizes private object intances_ and expr
 *
 * @param tokens is a list of instances of Tokens class
 * --------------------------------------------------------------------------
*/
parser::parser(std::vector<Token>& tokens): tokens_(tokens) {
    if (!expr) {
        expr = std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(Binary());
        instances_.push_back(*expr);
        expr->emplace<Unary>(Unary());
        instances_.push_back(*expr);
        expr->emplace<Grouping>(Grouping());
        instances_.push_back(*expr);
        expr->emplace<Literal>(Literal());
        instances_.push_back(*expr);
    }        
}

/** ---------------------------------------------------------------------------------------------------------------------------------------
 * @brief ........
 *
 * @detials This method represents the binary section in the grammar in parser.h. It uses variant which is known as a union type safe. 
    It will recrusive call itself functioning just like the grammar in parser.h
 * ---------------------------------------------------------------------------------------------------------------------------------------
*/
ExprTypes<Binary, Unary, Grouping, Literal> parser::equality() {
    // Recursion left !=
    expr = ExprTypes<Binary, Unary, Grouping, Literal>(comparison()); 
    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        const Token op = previous();
        // Recursion right ==
        ExprTypes<Binary, Unary, Grouping, Literal> right = ExprTypes<Binary, Unary, Grouping, Literal>(comparison());
        std::cout << "Executing inside equality!" << std::endl;
        static auto getExpr = [this](bool isLeft) -> Binary* {
            if (expr == nullptr) {
                std::cout << "Not good dude!" << std::endl;
            }
            else {
                std::cout << "expr is not null!" << std::endl;
            }
            auto* binary = std::get_if<Binary>(expr.get());
            for (auto& instance : instances_) {
                if (auto* binaryExpr = std::get_if<Binary>(&instance)) {
                    if (isLeft == true) {
                        //Binary temp = *binaryExpr;
                        binaryExpr->left = std::make_shared<Expr<Binary>>(*binaryExpr);
                        std::swap(instance, *expr);
                        return binaryExpr;
                    }
                    else {
                        binaryExpr->right = std::make_shared<Expr<Binary>>(*binaryExpr);
                        std::swap(instance, *expr);
                        return binaryExpr;
                    }
                }
                else if (binary == nullptr) {
                    // There will always be a Binary instance inside the vector
                    // Because of the parser constructor
                    if (isLeft == true) {
                        // Bug might occur here if instance object is not checked to see if it is actually Binary type
                        Binary* Left = std::get_if<Binary>(&instance);
                        binaryExpr->left = std::make_shared<Expr<Binary>>(*Left);
                        std::swap(instance, *expr);
                        return Left;
                    }
                    else {
                        Binary* Right = std::get_if<Binary>(&instance);
                        binaryExpr->right = std::make_shared<Expr<Binary>>(*Right);
                        std::swap(instance, *expr); // get the underlying of expr
                        return Right;
                    }
                }
            }
            catcher<parser> cp("NO MATCHING BINARY FOUND!");
            throw cp;
        };
        std::shared_ptr<Binary> l_Derived = std::make_shared<Binary>(*getExpr(true));
        std::shared_ptr<Expr<Binary>> L(l_Derived, static_cast<Expr<Binary>*>(l_Derived.get()));
        
        std::shared_ptr<Binary> r_Derived = std::make_shared<Binary>(*getExpr(false));
        std::shared_ptr<Expr<Binary>> R(r_Derived, static_cast<Expr<Binary>*>(r_Derived.get()));
        Binary B(L, op, R);
        expr->emplace<Binary>(B);
        std::cout << "Constructing the New Binary Instance into expr!" << std::endl;
        std::any temp_l = std::make_any<Binary>(std::move(*l_Derived));
        astTree<int, std::string, Binary> lr = compressedAstTree(idx, std::string("Binary"), std::any_cast<Binary>(temp_l));
        node.push_back(lr);
        idx++;
        std::any temp_r = std::make_any<Binary>(std::move(*r_Derived));
        astTree<int, std::string, Binary> rr = compressedAstTree(idx, std::string("Binary"), std::any_cast<Binary>(temp_r));
        node.push_back(rr);
        idx++;
        expr = ExprTypes<Binary, Unary, Grouping, Literal>(right);
    }
    return std::move(expr);
}


/** --------------------------------------------------------------------------
 * @brief ....
 *
 * @detials ...
 * 
 * --------------------------------------------------------------------------
*/
ExprTypes<Binary, Unary, Grouping, Literal> parser::comparison() {
    expr = ExprTypes<Binary, Unary, Grouping, Literal>(term());
    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
       const Token op = previous();
       ExprTypes<Binary, Unary, Grouping, Literal> right = ExprTypes<Binary, Unary, Grouping, Literal>(term());
       std::cout << "Executing inside comparison" << std::endl;
       static auto getExpr = [this](bool isLeft) -> Binary* {
            auto* binary = std::get_if<Binary>(expr.get());
            for (auto& instance : instances_) {
                if (auto* binaryExpr = std::get_if<Binary>(&instance)) {
                    if (isLeft == true) {
                        //Binary temp = *binaryExpr;
                        binaryExpr->left = std::make_shared<Expr<Binary>>(*binaryExpr);
                        std::swap(instance, *expr);
                        return binaryExpr;
                    }
                    else {
                        binaryExpr->right = std::make_shared<Expr<Binary>>(*binaryExpr);
                        std::swap(instance, *expr);
                        return binaryExpr;
                    }
                }
                else if (binary == nullptr) {
                    // There will always be a Binary instance inside the vector
                    // Because of the parser constructor
                    if (isLeft == true) {
                        // Bug might occur here if instance object is not checked to see if it is actually Binary type
                        Binary* Left = std::get_if<Binary>(&instance);
                        binaryExpr->left = std::make_shared<Expr<Binary>>(*Left);
                        std::swap(instance, *expr);
                        return Left;
                    }
                    else {
                        Binary* Right = std::get_if<Binary>(&instance);
                        binaryExpr->right = std::make_shared<Expr<Binary>>(*Right);
                        std::swap(instance, *expr); // get the underlying of expr
                        return Right;
                    }
                }
            }
            catcher<parser> cp("NO MATCHING BINARY FOUND!");
            throw cp;
        };
        std::shared_ptr<Binary> l_Derived = std::make_shared<Binary>(*getExpr(true));
        std::shared_ptr<Expr<Binary>> L(l_Derived, static_cast<Expr<Binary>*>(l_Derived.get()));
        
        std::shared_ptr<Binary> r_Derived = std::make_shared<Binary>(*getExpr(false));
        std::shared_ptr<Expr<Binary>> R(r_Derived, static_cast<Expr<Binary>*>(r_Derived.get()));

        Binary B(L, op, R);
        expr->emplace<Binary>(B);
        std::any temp_l = std::make_any<Binary>(std::move(*l_Derived));
        astTree<int, std::string, Binary> lr = compressedAstTree(idx, std::string("Binary"), std::any_cast<Binary>(temp_l));
        node.push_back(lr);
        idx++;

        std::any temp_r = std::make_any<Binary>(std::move(*r_Derived));
        astTree<int, std::string, Binary> rr = compressedAstTree(idx, std::string("Binary"), std::any_cast<Binary>(temp_r));
        node.push_back(rr);
        idx++;
        expr = ExprTypes<Binary, Unary, Grouping, Literal>(right);
    }
    return expr;
}
/** --------------------------------------------------------------------------
 * @brief ....
 *
 * @detials ...
 * 
 * --------------------------------------------------------------------------
*/

ExprTypes<Binary, Unary, Grouping, Literal> parser::term() {
    expr = ExprTypes<Binary, Unary, Grouping, Literal>(factor());
    while (match({TokenType::MINUS, TokenType::PLUS})) {
      const Token op = previous();
      ExprTypes<Binary, Unary, Grouping, Literal> right = ExprTypes<Binary, Unary, Grouping, Literal>(factor());
      std::cout << "Executing inside term!" << std::endl;
      static auto getExpr = [this](bool isLeft) -> Binary* {
            auto* binary = std::get_if<Binary>(expr.get());
            for (auto& instance : instances_) {
                if (auto* binaryExpr = std::get_if<Binary>(&instance)) {
                    if (isLeft == true) {
                        binaryExpr->left = std::make_shared<Expr<Binary>>(*binaryExpr);
                        std::swap(instance, *expr);
                        return binaryExpr;
                    }
                    else {
                        binaryExpr->right = std::make_shared<Expr<Binary>>(*binaryExpr);
                        std::swap(instance, *expr);
                        return binaryExpr;
                    }
                }
                else if (binary == nullptr) {
                    // There will always be a Binary instance inside the vector
                    // Because of the parser constructor
                    if (isLeft == true) {
                        // Bug might occur here if instance object is not checked to see if it is actually Binary type
                        Binary* Left = std::get_if<Binary>(&instance);
                        binaryExpr->left = std::make_shared<Expr<Binary>>(*Left);
                        std::swap(instance, *expr);
                        return Left;
                    }
                    else {
                        Binary* Right = std::get_if<Binary>(&instance);
                        binaryExpr->right = std::make_shared<Expr<Binary>>(*Right);
                        std::swap(instance, *expr); // get the underlying of expr
                        return Right;
                    }
                }
            }
            catcher<parser> cp("NO MATCHING BINARY FOUND!");
            throw cp;
        };
        std::shared_ptr<Binary> l_Derived = std::make_shared<Binary>(*getExpr(true));
        std::shared_ptr<Expr<Binary>> L(l_Derived, static_cast<Expr<Binary>*>(l_Derived.get()));
        
        std::shared_ptr<Binary> r_Derived = std::make_shared<Binary>(*getExpr(false));
        std::shared_ptr<Expr<Binary>> R(r_Derived, static_cast<Expr<Binary>*>(r_Derived.get()));

        Binary B(L, op, R);
        expr->emplace<Binary>(B);
        std::any temp_l = std::make_any<Binary>(std::move(*l_Derived));
        astTree<int, std::string, Binary> lr = compressedAstTree(idx, std::string("Binary"), std::any_cast<Binary>(temp_l));
        node.push_back(lr);
        idx++;

        std::any temp_r = std::make_any<Binary>(std::move(*r_Derived));
        astTree<int, std::string, Binary> rr = compressedAstTree(idx, std::string("Binary"), std::any_cast<Binary>(temp_r));
        node.push_back(rr);
        idx++;
        expr = ExprTypes<Binary, Unary, Grouping, Literal>(right);

    }
    return expr;
}
/** --------------------------------------------------------------------------
 * @brief ....
 *
 * @detials ...
 * 
 * --------------------------------------------------------------------------
*/
ExprTypes<Binary, Unary, Grouping, Literal> parser::factor() {
    expr = ExprTypes<Binary, Unary, Grouping, Literal>(unary());
    while (match({TokenType::SLASH, TokenType::STAR})) {
        const Token op = previous();
        ExprTypes<Binary, Unary, Grouping, Literal> right = ExprTypes<Binary, Unary, Grouping, Literal>(unary());
        std::cout << "Executing inside factor!" << std::endl;
        static auto getExpr = [this](bool isLeft) -> Binary* {
            auto* binary = std::get_if<Binary>(expr.get());
            for (auto& instance : instances_) {
                if (auto* binaryExpr = std::get_if<Binary>(&instance)) {
                    if (isLeft == true) {
                        binaryExpr->left = std::make_shared<Expr<Binary>>(*binaryExpr);
                        std::swap(instance, *expr);
                        return binaryExpr;
                    }
                    else {
                        binaryExpr->right = std::make_shared<Expr<Binary>>(*binaryExpr);
                        std::swap(instance, *expr);
                        return binaryExpr;
                    }
                }
                else if (binary == nullptr) {
                    // There will always be a Binary instance inside the vector
                    // Because of the parser constructor
                    if (isLeft == true) {
                        // Bug might occur here if instance object is not checked to see if it is actually Binary type
                        Binary* Left = std::get_if<Binary>(&instance);
                        binaryExpr->left = std::make_shared<Expr<Binary>>(*Left);
                        std::swap(instance, *expr);
                        return Left;
                    }
                    else {
                        Binary* Right = std::get_if<Binary>(&instance);
                        binaryExpr->right = std::make_shared<Expr<Binary>>(*Right);
                        std::swap(instance, *expr); // get the underlying of expr
                        return Right;
                    }
                }
            }
            catcher<parser> cp("NO MATCHING BINARY FOUND!");
            throw cp;
        };
        std::shared_ptr<Binary> l_Derived = std::make_shared<Binary>(*getExpr(true));
        std::shared_ptr<Expr<Binary>> L(l_Derived, static_cast<Expr<Binary>*>(l_Derived.get()));
        
        std::shared_ptr<Binary> r_Derived = std::make_shared<Binary>(*getExpr(false));
        std::shared_ptr<Expr<Binary>> R(r_Derived, static_cast<Expr<Binary>*>(r_Derived.get()));

        Binary B(L, op, R);
        expr->emplace<Binary>(B);
        std::any temp_l = std::make_any<Binary>(std::move(*l_Derived));
        astTree<int, std::string, Binary> lr = compressedAstTree(idx, std::string("Binary"), std::any_cast<Binary>(temp_l));
        node.push_back(lr);
        idx++;

        std::any temp_r = std::make_any<Binary>(std::move(*r_Derived));
        astTree<int, std::string, Binary> rr = compressedAstTree(idx, std::string("Binary"), std::any_cast<Binary>(temp_r));
        node.push_back(rr);
        idx++;
        expr = ExprTypes<Binary, Unary, Grouping, Literal>(right);
    }
    return expr;
}
/** --------------------------------------------------------------------------
 * @brief ....
 *
 * @detials ...
 * 
 * --------------------------------------------------------------------------
*/
ExprTypes<Binary, Unary, Grouping, Literal> parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS})) {
        const Token op = previous();
        expr = ExprTypes<Binary, Unary, Grouping, Literal>(unary());
        std::cout << "Executing inside unary!" << std::endl;
        auto getExpr = [this]() -> Unary* {
            std::variant<Binary, Unary, Grouping, Literal> temp = *expr; // deference to get the underlying 
            auto *unary = std::get_if<Unary>(&temp); // get the type
            for (auto& instance : instances_) {
                if (unary == nullptr) {
                    std::cout << "Unary is null" << std::endl;
                    if (auto* uV = std::get_if<Unary>(&instance)) {
                        std::cout << "Returning not Null!" << std::endl;
                        return uV;
                    }
                }
                else {
                    if (auto* uV = std::get_if<Unary>(&instance)) {
                        if (typeid(*uV) == typeid(*unary)) {
                            // Swap the variants if matched
                            std::swap(instance, *expr);
                            // Return pointer to Literal in the swapped variant
                            return std::get_if<Unary>(&instance);
                        }
                    }
                }
            }
            catcher<parser> cp("NO MATCH WAS FOUND UNARY Line 257!");
            throw cp;
        };
        std::shared_ptr<Unary> r_Derived = std::make_shared<Unary>(*getExpr());
        std::shared_ptr<Expr<Unary>> R(r_Derived, static_cast<Expr<Unary>*>(r_Derived.get()));
        Unary U(R, op);
        expr->emplace<Unary>(U);
        std::any temp_r = std::make_any<Unary>(std::move(*r_Derived));
        astTree<int, std::string, Unary> rr = compressedAstTree(idx, std::string("Unary"), std::any_cast<Unary>(temp_r));
        node.push_back(rr);
        idx++;
        std::cout << "Returning expr back! Line 268" << std::endl;
        return expr;
    }
    // Check and see if expr is not null
    return primary();
}
/** --------------------------------------------------------------------------
 * @brief ....
 *
 * @detials ...
 * 
 * --------------------------------------------------------------------------
*/
ExprTypes<Binary, Unary, Grouping, Literal> parser::primary() {
    if (match({TokenType::FALSE})) {
        std::cout << "Executing inside primary TokenType::FALSE" << std::endl;
        Literal l(false);
        expr->emplace<Literal>(l);
        static auto getExpr = [this]() -> Literal* {
            std::variant<Binary, Unary, Grouping, Literal> temp = *expr; // deference to get the underlying 
            auto *literal = std::get_if<Literal>(&temp); // get the type
            for (auto& instance : instances_) {
                if (literal == nullptr) {
                    std::cout << "literal is null" << std::endl;
                    if (auto* lV = std::get_if<Literal>(&instance)) {
                        std::cout << "Returning not Null!" << std::endl;
                        return lV;
                    }
                }
                else {
                    if (auto* lV = std::get_if<Literal>(&instance)) {
                        if (typeid(*lV) == typeid(*literal)) {
                            // Swap the variants if matched
                            std::swap(instance, *expr);
                            // Return pointer to Literal in the swapped variant
                            return std::get_if<Literal>(&instance);
                        }
                    }
                }
            }
            catcher<parser> cp("NO MATCH WAS FOUND FOR LITERAL");
            throw cp;
        };
        std::shared_ptr<Literal> Derived = std::make_shared<Literal>(*getExpr());
        std::shared_ptr<Expr<Literal>> L(Derived, static_cast<Expr<Literal>*>(Derived.get()));
        std::any temp = std::make_any<Literal>(std::move(*Derived));
        astTree<int, std::string, Literal> res = compressedAstTree(idx, std::string("Literal"), std::any_cast<Literal>(temp));
        node.push_back(res);
        idx++;
        return expr;
    }
    if (match({TokenType::TRUE})) {
        std::cout << "Executing inside primary TokenType::TRUE" << std::endl;
        Literal l(true);
        expr->emplace<Literal>(l);
        auto getExpr = [this]() -> Literal* {
            std::variant<Binary, Unary, Grouping, Literal> temp = *expr; // deference to get the underlying 
            auto *literal = std::get_if<Literal>(&temp); // get the type
            for (auto& instance : instances_) {
                if (literal == nullptr) {
                    std::cout << "literal is null" << std::endl;
                    if (auto* lV = std::get_if<Literal>(&instance)) {
                        std::cout << "Returning not Null!" << std::endl;
                        return lV;
                    }
                }
                else {
                    if (auto* lV = std::get_if<Literal>(&instance)) {
                        if (typeid(*lV) == typeid(*literal)) {
                            // Swap the variants if matched
                            std::swap(instance, *expr);
                            // Return pointer to Literal in the swapped variant
                            return std::get_if<Literal>(&instance);
                        }
                    }
                }
            }
            catcher<parser> cp("NO MATCH WAS FOUND FOR LITERAL");
            throw cp;
        };
        std::shared_ptr<Literal> Derived = std::make_shared<Literal>(*getExpr());
        std::shared_ptr<Expr<Literal>> L(Derived, static_cast<Expr<Literal>*>(Derived.get()));
        std::any temp = std::make_any<Literal>(std::move(*Derived));
        astTree<int, std::string, Literal> res = compressedAstTree(idx, std::string("Literal"), std::any_cast<Literal>(temp));
        node.push_back(res);
        idx++;
        return expr;
    }
    if (match({TokenType::NIL})) {
        std::cout << "Executing inside primary TokenType::NIL" << std::endl;
        Literal l(NULL);
         expr->emplace<Literal>(l);
         auto getExpr = [this]() -> Literal* {
             std::variant<Binary, Unary, Grouping, Literal> temp = *expr; // deference to get the underlying 
             auto *literal = std::get_if<Literal>(&temp); // get the type
             for (auto& instance : instances_) {
                 if (literal == nullptr) {
                    std::cout << "literal is null" << std::endl;
                    if (auto* lV = std::get_if<Literal>(&instance)) {
                        std::cout << "Returning not Null!" << std::endl;
                        return lV;
                    }
                }
                else {
                    if (auto* lV = std::get_if<Literal>(&instance)) {
                        if (typeid(*lV) == typeid(*literal)) {
                            // Swap the variants if matched
                            std::swap(instance, *expr);
                            // Return pointer to Literal in the swapped variant
                            return std::get_if<Literal>(&instance);
                        }
                    }
                }
            }
            std::cout << "NO MATCH WAS FOUND ON LINE 334" << std::endl;
            return nullptr;
        };
        std::shared_ptr<Literal> Derived = std::make_shared<Literal>(*getExpr());
        std::shared_ptr<Expr<Literal>> L(Derived, static_cast<Expr<Literal>*>(Derived.get()));
        std::any temp = std::make_any<Literal>(std::move(*Derived));
        astTree<int, std::string, Literal> res = compressedAstTree(idx, std::string("Literal"), std::any_cast<Literal>(temp));
        node.push_back(res);
        idx++;
        return std::move(expr);
    }
    if (match({TokenType::NUMBER, TokenType::STRING})) {
        std::cout << "Executing inside primary TokenType::NUMBER, TokenType::STRING" << std::endl;
        Literal l(previous().getLiteral());
        expr->emplace<Literal>(l);
        auto getExpr = [this]() -> Literal* {
            std::variant<Binary, Unary, Grouping, Literal> temp = *expr; // deference to get the underlying 
            auto *literal = std::get_if<Literal>(&temp); // get the type
            std::cout << "Executing line 335 TokenType::NUMBER, TokenType::STRING" << std::endl;
            for (auto& instance : instances_) {
                if (literal == nullptr) {
                    std::cout << "literal is null" << std::endl;
                    if (auto* lV = std::get_if<Literal>(&instance)) {
                        std::cout << "Returning not Null!" << std::endl;
                        return lV;
                    }
                }
                else {
                    if (auto* lV = std::get_if<Literal>(&instance)) {
                        if (typeid(*lV) == typeid(*literal)) {
                            // Swap the variants if matched
                            std::swap(instance, *expr);
                            // Return pointer to Literal in the swapped variant
                            return std::get_if<Literal>(&instance);
                        }
                    }
                }
            }
            std::cout << "NO MATCH WAS FOUND" << std::endl;
            return nullptr;
        };
        std::shared_ptr<Literal> Derived = std::make_shared<Literal>(*getExpr());
        std::cout << "Executing line 366!" << std::endl;
        std::shared_ptr<Expr<Literal>> L(Derived, static_cast<Expr<Literal>*>(Derived.get()));
        std::any temp = std::make_any<Literal>(std::move(*Derived));
        astTree<int, std::string, Literal> res = compressedAstTree(idx, std::string("Literal"), std::any_cast<Literal>(temp));
        node.push_back(res);
        idx++;
        std::cout << "Returning the expression!" << std::endl;
        return expr;
    }
    if (match({TokenType::LEFT_PAREN})) {
        std::cout << "Executing inside primary TokenType::LEFT_PARAN" << std::endl;
        expr = expression();
        auto getExpr = [this]() -> Grouping* {
            std::variant<Binary, Unary, Grouping, Literal> temp = *expr; // deference to get the underlying 
            auto *grouping = std::get_if<Grouping>(&temp); // get the type
            for (auto& instance : instances_) {
                if (grouping == nullptr) {
                    std::cout << "grouping is null" << std::endl;
                    if (auto* gV = std::get_if<Grouping>(&instance)) {
                        std::cout << "Returning not Null!" << std::endl;
                        return gV;
                    }
                }
                else {
                    if (auto* gV = std::get_if<Grouping>(&instance)) {
                        if (typeid(*gV) == typeid(*grouping)) {
                            // Swap the variants if matched
                            std::swap(instance, *expr);
                            // Return pointer to Literal in the swapped variant
                            return std::get_if<Grouping>(&instance);
                        }
                    }
                }
            }
            std::cout << "NO MATCH WAS FOUND FOR GROUPING" << std::endl;
            return nullptr;

        };
        std::shared_ptr<Grouping> Derived = std::make_shared<Grouping>(*getExpr());
        std::shared_ptr<Expr<Grouping>> L(Derived, static_cast<Expr<Grouping>*>(Derived.get()));
        Grouping G(L);
        expr->emplace<Grouping>(G);
        std::any temp = std::make_any<Grouping>(std::move(*Derived));
        astTree<int, std::string, Grouping> res = compressedAstTree(idx, std::string("Grouping"), std::any_cast<Grouping>(temp));
        node.push_back(res);
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        idx++;
        std::cout << "Returning expr in Grouping! Line 406" << std::endl;
        return expr;
    }
    throw error(peek(), "Expect expression.");
}
/** --------------------------------------------------------------------------
 * @brief ....
 *
 * @detials ...
 * 
 * --------------------------------------------------------------------------
*/
ExprTypes<Binary, Unary, Grouping, Literal> parser::expression() {
    return std::move(equality());
}
/** --------------------------------------------------------------------------
 * @brief ....
 *
 * @detials ...
 * 
 * --------------------------------------------------------------------------
*/
ExprTypes<Binary, Unary, Grouping, Literal> parser::parse() {
    try { return std::move(expression());}
    catch(catcher<parser>& e) {
        std::cout << e.what() << std::endl;
        return NULL;
    }
    catch (parseError<parser>& e) { 
        std::cout << e.what() << std::endl;
        return NULL; 
    }
}

// Additional rules go above this line
//
//
