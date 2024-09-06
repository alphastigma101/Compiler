#include <parser.h>
template struct std::shared_ptr<std::variant<Binary, Unary, Grouping, Literal>>; // define the underlying of ExprTypes
ExprTypes<Binary, Unary, Grouping, Literal> parser::expr;
int parser::idx = 0;
template<typename T>
std::vector<std::tuple<int, std::pair<std::string, std::shared_ptr<ListOfType<T>>>>> parser::nodes;
/**--------------------------------------------------------------------------
 * @brief default constructor
 *
 * @param tokens is a list of instances of Tokens class
 * --------------------------------------------------------------------------
*/
parser::parser(std::vector<Token>& tokens): tokens_(tokens) {}

/** ---------------------------------------------------------------------------------------------------------------------------------------
 * @brief ........
 *
 * @detials This method represents the binary section in the grammar in parser.h. It uses variant which is known as a union type safe. 
    It will recrusive call itself functioning just like the grammar in parser.h
 * ---------------------------------------------------------------------------------------------------------------------------------------
*/
ExprTypes<Binary, Unary, Grouping, Literal> parser::equality()  {
    // Recursion left !=
    auto expr_ = comparison(); 
    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        const Token op = previous();
        // Recursion right ==
        auto right = comparison();
        std::cout << "Executing inside equality!" << std::endl;
        ExprTypes<std::monostate, Expr<Binary>> L,R;
        if (expr_ && std::get_if<Binary>(expr_.get())) { L = std::make_shared<std::variant<std::monostate, Expr<Binary>>>(std::variant<std::monostate, Expr<Binary>>(std::get<Binary>(*expr_))); }
        else { L = std::make_shared<std::variant<std::monostate, Expr<Binary>>>(std::monostate{}); }
        if (right && std::get_if<Binary>(right.get())) { R = std::make_shared<std::variant<std::monostate, Expr<Binary>>>(std::variant<std::monostate, Expr<Binary>>(std::get<Binary>(*right))); }
        else { R = std::make_shared<std::variant<std::monostate, Expr<Binary>>>(std::monostate{}); }
        expr = std::make_shared<ExprVariant>(Binary(L, op, R)); // initialize it with Binary instance
        auto res = compressedAstTree(idx, std::string("Binary"), {*L, *R});
        nodes<std::variant<std::monostate, Expr<Binary>>>.push_back(res);
        idx++;
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
ExprTypes<Binary, Unary, Grouping, Literal> parser::comparison()  {
    /*auto expr_ = term();
    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
       const Token op = previous();
       auto right = term();
       std::cout << "Executing inside comparison" << std::endl;
    }*/
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
    auto expr_ = factor();
    while (match({TokenType::MINUS, TokenType::PLUS})) {
        const Token op = previous();
        auto right = factor();
        std::cout << "Executing inside term!" << std::endl;
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
    auto expr_ = unary();
    while (match({TokenType::SLASH, TokenType::STAR})) {
        const Token op = previous();
        auto right = unary();
        std::cout << "Executing inside factor!" << std::endl;
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
        auto right = unary();
        std::cout << "Executing inside unary!" << std::endl;
        return expr;
    }
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
        return expr;
    }
    if (match({TokenType::TRUE})) {
        std::cout << "Executing inside primary TokenType::TRUE" << std::endl;
        Literal l(true);
        return expr;
    }
    if (match({TokenType::NIL})) {
        std::cout << "Executing inside primary TokenType::NIL" << std::endl;
        Literal l(NULL);
        return expr;
    }
    if (match({TokenType::NUMBER, TokenType::STRING})) {
        std::cout << "Executing inside primary TokenType::NUMBER, TokenType::STRING" << std::endl;
        Literal l(previous().getLiteral());
        return expr;
    }
    if (match({TokenType::LEFT_PAREN})) {
        std::cout << "Executing inside primary TokenType::LEFT_PARAN" << std::endl;
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
    return equality();
}
/** --------------------------------------------------------------------------
 * @brief ....
 *
 * @detials ...
 * 
 * --------------------------------------------------------------------------
*/
ExprTypes<Binary, Unary, Grouping, Literal> parser::parse() {
    try { return expression();}
    catch(catcher<parser>& e) {
        std::cout << e.what() << std::endl;
        return expr;
    }
    catch (parseError<parser>& e) { 
        std::cout << e.what() << std::endl;
        return expr; 
    }
}

// Additional rules go above this line
//
//
//

