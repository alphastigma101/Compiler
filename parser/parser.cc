#include <parser.h>
#include <stdexcept> // runtime_error can be used

/* -------------------------------------------------------------------
 * (equality) Description:
    This method represents the binary section in the grammar in parser.h. It uses variant which is known as a union type safe. 
    It will recrusive call itself functioning just like the grammar in parser.h
 *
 *
*/
ExprTypes* parser::equality() {
    ExprTypes* expr = comparison();
    while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        const Token op = previous();
        ExprTypes* right = comparison();
        auto getExpr = [](ExprTypes* e) -> Expr<Binary> {
            if (auto* binary = std::get_if<Binary>(e)) {
                return std::move(*binary);
            } else { throw std::runtime_error("Expected Binary expression");}
        };
        //TODO: Threading is going to be needed here 
        Binary B(std::forward<Expr<Binary>>(*(getExpr(expr).left)), op, std::forward<Expr<Binary>>(*(getExpr(right).right))); // uses && which makes a temp object 
        visitBinaryExpr(B); // uses the temp object for recrusion
        expr->emplace<0>(B);
    }
    return expr;
}
/*
 *
 *
*/
ExprTypes* parser::comparison() {
    ExprTypes* expr = term();
    while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
        const Token op = previous();
        expr = term();
        ExprTypes* left = expr;
        auto getExpr = [](ExprTypes* e) -> Expr<Binary> {
            if (auto* binary = std::get_if<Binary>(e)) {
                return std::move(*binary);
            } else { throw std::runtime_error("Expected Binary expression");}
        };
        //TODO: Threading is going to be needed here 
        Binary B(std::forward<Expr<Binary>>(*(getExpr(left).left)), op, std::forward<Expr<Binary>>(*(getExpr(expr).right))); // uses && which makes a temp object 
        visitBinaryExpr(B); // uses the temp object for recrusion
        expr->emplace<0>(B);
    }
    return expr;
}
/*
 *
 *
*/
ExprTypes* parser::term() {
    ExprTypes* expr = factor();
    while (match(TokenType::MINUS, TokenType::PLUS)) {
      const Token op = previous();
      ExprTypes* right = factor();
      auto getExpr = [](ExprTypes* e) -> Expr<Binary> {
          if (auto* binary = std::get_if<Binary>(e)) {
                return std::move(*binary);
            } else { throw std::runtime_error("Expected Binary expression");}
        };
        //TODO: Threading is going to be needed here 
        Binary B(std::forward<Expr<Binary>>(*(getExpr(expr).left)), op, std::forward<Expr<Binary>>(*(getExpr(right).right))); // uses && which makes a temp object 
        visitBinaryExpr(B); // uses the temp object for recrusion
        expr->emplace<0>(B);
    }
    return expr;
}
/*
 *
 *
*/
ExprTypes* parser::factor() {
    ExprTypes* expr = unary();
    while (match(TokenType::SLASH, TokenType::STAR)) {
        const Token op = previous();
        ExprTypes* right = unary();
        auto getExpr = [](ExprTypes* e) -> Expr<Binary> {
            if (auto* binary = std::get_if<Binary>(e)) {
                return std::move(*binary);
            } else { throw std::runtime_error("Expected Binary expression");}
        };
        //TODO: Threading is going to be needed here 
        Binary B(std::forward<Expr<Binary>>(*(getExpr(expr).left)), op, std::forward<Expr<Binary>>(*(getExpr(right).right))); // uses && which makes a temp object 
        visitBinaryExpr(B); // uses the temp object for recrusion
        expr->emplace<0>(B);
    }
    return expr;
}
/*
 *
 *
*/
ExprTypes* parser::unary() {
    if (match(TokenType::BANG, TokenType::MINUS)) {
        const Token op = previous();
        ExprTypes* expr = unary();
        auto getExpr = [](ExprTypes* e) -> Expr<Unary> {
            if (auto* unary = std::get_if<Unary>(e)) {
                return std::move(*unary);
            } else { throw std::runtime_error("Expected Unary expression");}
        };
        //TODO: Threading is going to be needed here 
        Unary U(std::forward<Expr<Unary>>(*(getExpr(expr).right)), op); // uses && which makes a temp object 
        visitUnaryExpr(U); // uses the temp object for recrusion
        expr->emplace<1>(U);
        return expr;
    }
    return primary();
}
/*
 *
 *
*/
ExprTypes* parser::primary() {
    if (match(TokenType::FALSE)) {
        Literal l(false);
        visitLiteralExpr(l);
        expr->emplace<3>(Literal(std::forward<Expr<Literal>>(static_cast<Expr<Literal>&>(l))));
        return expr;
    }
    if (match(TokenType::TRUE)) {
         Literal l(true);
         visitLiteralExpr(l);
         expr->emplace<3>(Literal(std::forward<Expr<Literal>>(static_cast<Expr<Literal>&>(l))));
         return expr;
    }
    if (match(TokenType::NIL)) {
         Literal l(NULL);
         visitLiteralExpr(l);
         expr->emplace<3>(Literal(std::forward<Expr<Literal>>(static_cast<Expr<Literal>&>(l))));
         return expr;
    }
    if (match(TokenType::NUMBER, TokenType::STRING)) {
       Literal l(previous().getLiteral());
       visitLiteralExpr(l);
       expr->emplace<3>(Literal(std::forward<Expr<Literal>>(static_cast<Expr<Literal>&>(l))));
       return expr;
    }
    if (match(TokenType::LEFT_PAREN)) {
      ExprTypes* expr = expression();
      auto getExpr = [](ExprTypes* e) -> Expr<Grouping> {
            if (auto* grouping = std::get_if<Grouping>(e)) {
                return std::move(*grouping);
            } else { throw std::runtime_error("Expected Binary expression");}
        };
        //TODO: Threading is going to be needed here 
        Grouping G(std::forward<Expr<Grouping>>(getExpr(expr))); // uses && which makes a temp object 
        visitGroupingExpr(G); // uses the temp object for recrusion
        expr->emplace<2>(G);
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return expr;
    }
    throw error(peek(), "Expect expression.");
}
/*
 *
 *
*/
ExprTypes* parser::expression() {
    return equality();
}
/*
 *
 *
*/
ExprTypes* parser::parse() {
    try { return expression();} 
    catch (parseError& error) { return NULL; }
}

// Additional rules go above this line
//
//
