#include <parser.h>
// define the visitor functions inside the ast, that call in the visitor method for each class
// and add each object into a vector from the abstraction_syntax_tree.cc
Expr parser::equality() {
    Expr expr = comparison();
    while (match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        const Token op = previous();
        expr->right = comparison();
        expr->left = expr;
        expr = new Binary(expr->left, op, expr->right);
    }
    return expr;
}

Expr parser::comparison() {
    Expr expr = term();
    while (match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL)) {
        const Token op = previous();
        expr->right = term();
        expr->left = expr;
        expr = new Binary(expr->left, op, expr->right);
    }
    return expr;
}

Expr parser::term() {
    Expr expr = factor();
    while (match(TokenType::MINUS, TokenType::PLUS)) {
      const Token op = previous();
      expr->right = factor();
      expr->left = expr;
      expr = new Binary(expr->left, op, expr->right);
    }
    return expr;
  }
}

Expr parser::factor() {
    Expr expr = unary();
    while (match(TokenType::SLASH, TokenType::STAR)) {
        const Token op = previous();
        expr->right = unary();
        expr->left = expr;
        expr = new Binary(expr->left, op, expr->right);
    }
    return expr;
}

Expr parser::unary() {
    if (match(TokenType::BANG, TokenType::MINUS)) {
      const Token op = previous();
      Expr right = unary();
      expr->right = right;
      return new Unary(op, expr->right); // this might not work even though Unary class has the same behavior as Expr
    }
    return primary();
}

Expr parser::primary() {
    if (match(TokenType::FALSE)) return new Literal(false);
    if (match(TokenType::TRUE)) return new Literal(true);
    if (match(TokenType::NIL)) return new Literal(NULL);

    if (match(TokenType::NUMBER, TokenType::STRING)) {
      return new Literal(previous().literal);
    }

    if (match(TokenType::LEFT_PAREN)) {
      Expr expr = expression();
      consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
      return new Grouping(expr);
    }
    throw error(peek(), "Expect expression.");
}
Expr parser::parse() {
    try { return expression();} 
    catch (parseError& error) { return NULL; }
}

// Additional rules go here
//
//

void parser::error(const TokenType type, const std::string message) override {
    if (token.type == TokenType.EOF) { report(token.getLine(), " at end", message);} 
    else { report(token.getline(), " at '" + token.getLexeme() + "'", message); }
}

void parser::report(int line, const std::string where, const std::string message) override {
    std::cout << "[line " <<  line << "] Error" << where << ": " + message;
}

void parser::synchronize() {
    advance();
    while (!isAtEnd()) {
        // TODO: Need to capture other boundaries that will simulate a new statement
        // So instead of semicolons, other programming languages most likely do not use ; to indicate a new statement
        if (previous().type == TokenType::SEMICOLON) return;
        switch (peek().type) {
            case TokenType::CLASS:
            case TokenType::FUN:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            case TokenType::RETURN:
            return;
        }
        advance();
    }
}

