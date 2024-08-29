#include <parser.h>
/* -------------------------------------------------------------------
 * (equality) Description:
    This method represents the binary section in the grammar in parser.h. It uses variant which is known as a union type safe. 
    It will recrusive call itself functioning just like the grammar in parser.h
 *
 *
*/
ExprTypes<Binary, Unary, Grouping, Literal>* parser::equality() {
    // TODO: For each function, use Binary and add the tokens and the line 
    expr = comparison(); // recrusion left !=
    while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        const Token op = previous(); // TODO: Need to copy op to *op Expr object
        ExprTypes<Binary, Unary, Grouping, Literal>* right = comparison(); // recrusion right ==
        auto getExpr = [](ExprTypes<Binary, Unary, Grouping, Literal>* e) -> Expr<Binary> {
            if (auto* binary = std::get_if<Binary>(e)) {
                return std::move(*binary);
            } else { throw std::runtime_error("Expected Binary expression");}
        };
        //TODO: Threading is going to be needed here 
        Binary B(static_cast<Expr<Binary>&>(*(getExpr(expr).left)), op, static_cast<Expr<Binary>&>(*(getExpr(right).right)));
        expr->emplace<0>(B);
        node.push_back(compressedAstTree(idx, std::string("Binary: "), *getExpr));
        idx++;
        ExprTypes<Binary, Unary, Grouping, Literal>* expr = new std::variant<Binary, Unary, Grouping, Literal>(*right);
    }
    return expr;
}
/*
 *
 *
*/
ExprTypes<Binary, Unary, Grouping, Literal>* parser::comparison() {
    expr = term();
    while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
        const Token op = previous();
        ExprTypes<Binary, Unary, Grouping, Literal>* right = term();
        auto getExpr = [](ExprTypes<Binary, Unary, Grouping, Literal>* e) -> Expr<Binary> {
            if (auto* binary = std::get_if<Binary>(e)) {
                return std::move(*binary);
            } else { throw std::runtime_error("Expected Binary expression");}
        };
        //TODO: Threading is going to be needed here 
        Binary B(static_cast<Expr<Binary>&>(*(getExpr(expr).left)), op, static_cast<Expr<Binary>&>(*(getExpr(expr).right)));
        expr->emplace<0>(B);
        node.push_back(compressedAstTree(idx, std::string("Binary: "), *getExpr));
        idx++;
        ExprTypes<Binary, Unary, Grouping, Literal>* expr = new std::variant<Binary, Unary, Grouping, Literal>(*right);
    }
    return expr;
}
/*
 *
 *
*/
ExprTypes<Binary, Unary, Grouping, Literal>* parser::term() {
    expr = factor();
    while (match(TokenType::MINUS, TokenType::PLUS)) {
      const Token op = previous();
      ExprTypes<Binary, Unary, Grouping, Literal>* right = factor();
      auto getExpr = [](ExprTypes<Binary, Unary, Grouping, Literal>* e) -> Expr<Binary> {
          if (auto* binary = std::get_if<Binary>(e)) {
                return std::move(*binary);
            } else { throw std::runtime_error("Expected Binary expression");}
        };
        //TODO: Threading is going to be needed here 
        Binary B(static_cast<Expr<Binary>&>(*(getExpr(expr).left)), op, static_cast<Expr<Binary>&>(*(getExpr(right).right)));
        expr->emplace<0>(B);
        node.push_back(compressedAstTree(idx, std::string("Binary: "), *getExpr));
        idx++;
        ExprTypes<Binary, Unary, Grouping, Literal>* expr = new std::variant<Binary, Unary, Grouping, Literal>(*right);
    }
    return expr;
}
/*
 *
 *
*/
ExprTypes<Binary, Unary, Grouping, Literal>* parser::factor() {
    expr = unary();
    while (match(TokenType::SLASH, TokenType::STAR)) {
        const Token op = previous();
        ExprTypes<Binary, Unary, Grouping, Literal>* right = unary();
        auto getExpr = [](ExprTypes<Binary, Unary, Grouping, Literal>* e) -> Expr<Binary> {
            if (auto* binary = std::get_if<Binary>(e)) {
                return std::move(*binary);
            } else { throw std::runtime_error("Expected Binary expression");}
        };
        //TODO: Threading is going to be needed here 
        Binary B(static_cast<Expr<Binary>&>(*(getExpr(expr).left)), op, static_cast<Expr<Binary>&>(*(getExpr(right).right)));
        expr->emplace<0>(B);
        node.push_back(compressedAstTree(idx, std::string("Binary: "), *getExpr));
        idx++;
        ExprTypes<Binary, Unary, Grouping, Literal>* expr = new std::variant<Binary, Unary, Grouping, Literal>(*right);
    }
    return expr;
}
/*
 *
 *
*/
ExprTypes<Binary, Unary, Grouping, Literal>* parser::unary() {
    if (match(TokenType::BANG, TokenType::MINUS)) {
        const Token op = previous();
        expr = unary();
        auto getExpr = [](ExprTypes<Binary, Unary, Grouping, Literal>* e) -> Expr<Unary> {
            if (auto* unary = std::get_if<Unary>(e)) {
                return std::move(*unary);
            } else { throw std::runtime_error("Expected Unary expression");}
        };
        //TODO: Threading is going to be needed here 
        Unary U(static_cast<Expr<Unary>&>(*(getExpr(expr).right)), op);
        expr->emplace<1>(U);
        node.push_back(compressedAstTree(idx, std::string("Unary: "), *getExpr));
        idx++;
        ExprTypes<Binary, Unary, Grouping, Literal>* expr = new std::variant<Binary, Unary, Grouping, Literal>(*expr); 
        return expr;
    }
    return primary();
}
/*
 *
 *
*/
ExprTypes<Binary, Unary, Grouping, Literal>* parser::primary() {
    if (match(TokenType::FALSE)) {
        Literal l(false);
        auto res = expr;
        res->emplace<3>(l);
        auto getExpr = [](ExprTypes<Binary, Unary, Grouping, Literal>* e) -> Expr<Literal> {
            if (auto* literal = std::get_if<Literal>(e)) {
                return std::move(*literal);
            } else { throw std::runtime_error("Expected Literal expression");}
        };
        node.push_back(compressedAstTree(idx, std::string("Literal: "), *getExpr));
        idx++;
        ExprTypes<Binary, Unary, Grouping, Literal>* expr = new std::variant<Binary, Unary, Grouping, Literal>(*res);
        auto Expr = expr;
        return expr;
    }
    if (match(TokenType::TRUE)) {
         Literal l(true);
         auto res = expr;
         res->emplace<3>(l);
         auto getExpr = [](ExprTypes<Binary, Unary, Grouping, Literal>* e) -> Expr<Literal> {
            if (auto* literal = std::get_if<Literal>(e)) {
                return std::move(*literal);
            } else { throw std::runtime_error("Expected Literal expression");}
         };
         node.push_back(compressedAstTree(idx, std::string("Literal: "), *getExpr));
         idx++;
         ExprTypes<Binary, Unary, Grouping, Literal>* expr = new std::variant<Binary, Unary, Grouping, Literal>(*res);
         return expr;
    }
    if (match(TokenType::NIL)) {
         Literal l(NULL);
         auto res = expr;
         res->emplace<3>(l);
         // TODO: Could be a bug here would inspect with debugger. All in this scope
         auto getExpr = [](ExprTypes<Binary, Unary, Grouping, Literal>* e) -> Expr<Literal> {
            if (auto* literal = std::get_if<Literal>(e)) {
                return std::move(*literal);
            } else { throw std::runtime_error("Expected Literal expression");}
        };
         node.push_back(compressedAstTree(idx, std::string("Literal: "), *getExpr));
         idx++;
         ExprTypes<Binary, Unary, Grouping, Literal>* expr = new std::variant<Binary, Unary, Grouping, Literal>(*res);
         return expr;
    }
    if (match(TokenType::NUMBER, TokenType::STRING)) {
       Literal l(previous().getLiteral());
       auto res = expr;
       res->emplace<3>(l);
       auto getExpr = [](ExprTypes<Binary, Unary, Grouping, Literal>* e) -> Expr<Literal> {
            if (auto* literal = std::get_if<Literal>(e)) {
                return std::move(*literal);
            } else { throw std::runtime_error("Expected Literal expression");}
        };
       node.push_back(compressedAstTree(idx, std::string("Literal: "), *getExpr));
       idx++;
       ExprTypes<Binary, Unary, Grouping, Literal>* expr = new std::variant<Binary, Unary, Grouping, Literal>(*res);
       return expr;
    }
    if (match(TokenType::LEFT_PAREN)) {
      expr = expression();
      auto getExpr = [](ExprTypes<Binary, Unary, Grouping, Literal>* e) -> Expr<Grouping> {
            if (auto* grouping = std::get_if<Grouping>(e)) {
                return std::move(*grouping);
            } else { throw std::runtime_error("Expected Grouping expression");}
        };
        //TODO: Threading is going to be needed here 
        Grouping G(static_cast<Expr<Grouping>>(getExpr(expr)));
        expr->emplace<2>(G);
        node.push_back(compressedAstTree(idx, std::string("Grouping: "), *expr));
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        idx++;
        return expr;
    }
    throw error(peek(), "Expect expression.");
}
/*
 *
 *
*/
ExprTypes<Binary, Unary, Grouping, Literal>* parser::expression() {
    return equality();
}
/*
 *
 *
*/
ExprTypes<Binary, Unary, Grouping, Literal>* parser::parse() {
    try { return expression();} 
    catch (parseError& error) { return NULL; }
}

// Additional rules go above this line
//
//
