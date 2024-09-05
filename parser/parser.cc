#include <parser.h>
template struct std::shared_ptr<std::variant<Binary, Unary, Grouping, Literal>>;
template struct std::vector<std::pair<std::string, std::shared_ptr<std::variant<Binary, Unary, Grouping, Literal>>>>;
ExprTypes<Binary, Unary, Grouping, Literal> parser::expr;
grammarParser<std::string, Binary, Unary, Grouping, Literal> parser::instances_;
int parser::idx = 0;
std::vector<std::tuple<int, std::pair<std::string, std::any>>> parser::node;
bool parser::isLeft = true;
/**--------------------------------------------------------------------------
 * @brief default constructor that initalizes private object expr
 *
 * @param tokens is a list of instances of Tokens class
 * --------------------------------------------------------------------------
*/
parser::parser(std::vector<Token>& tokens): tokens_(tokens) {
    if (!expr) { expr = std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(Binary()); }        
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
    instances_.push_back(std::make_pair("Left", ExprTypes<Binary, Unary, Grouping, Literal>(comparison()))); 
    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        const Token op = previous();
        // Recursion right ==
        instances_.push_back(std::make_pair("Right", ExprTypes<Binary, Unary, Grouping, Literal>(comparison())));
        std::cout << "Executing inside equality!" << std::endl;
        static auto getExpr = [this](bool isLeft) -> Binary* {
            if (expr == nullptr) {
                catcher<parser> cp("EXPR IS NULL!");
                throw cp;
            }
            if (instances_.size() == 0) {
                std::cout << "Code broken!" << std::endl;
            }   
            for (int i = 0; i < instances_.size(); i++) {
                if (idx == i && instances_[i].first == "Left") {
                    if (auto* binaryL = std::get_if<Binary>(instances_[i].second.get())) {
                        std::cout << "Returning Left!" << std::endl;
                        return binaryL;
                    }
                    else {
                        std::cout << "Left is Null!" << std::endl;
                        return nullptr;
                    }
                }
                else if (idx == i && instances_[i].first == "Right") {
                    if (auto* binaryR = std::get_if<Binary>(instances_[i].second.get())) {
                        std::cout << "Returning Right!" << std::endl;
                        return binaryR;
                    }
                    else {
                        std::cout << "Right is Null!" << std::endl;
                        return nullptr;
                    }
                }
            }
            // No match was found. Return nullptr
            return nullptr;
        };
        handleBinaryExprAndUpdateNodes(getExpr, op); 
        std::cout << "Executing Line 126!" << std::endl;
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
ExprTypes<Binary, Unary, Grouping, Literal> parser::comparison() {
    instances_.push_back(std::make_pair("Left", ExprTypes<Binary, Unary, Grouping, Literal>(term())));
    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
       const Token op = previous();
       instances_.push_back(std::make_pair("Right", ExprTypes<Binary, Unary, Grouping, Literal>(term())));
       std::cout << "Executing inside comparison" << std::endl;
       static auto getExpr = [this](bool isLeft) -> Binary* {
            if (expr == nullptr) {
                catcher<parser> cp("EXPR IS NULL!");
                throw cp;
            }
            if (instances_.size() == 0) {
                std::cout << "Code broken!" << std::endl;
            }   
            for (int i = 0; i < instances_.size(); i++) {
                if (idx == i && instances_[i].first == "Left") {
                    if (auto* binaryL = std::get_if<Binary>(instances_[i].second.get())) {
                        std::cout << "Returning Left!" << std::endl;
                        return binaryL;
                    }
                    else {
                        std::cout << "Left is Null!" << std::endl;
                        return nullptr;
                    }
                }
                else if (idx == i && instances_[i].first == "Right") {
                    if (auto* binaryR = std::get_if<Binary>(instances_[i].second.get())) {
                        std::cout << "Returning Right!" << std::endl;
                        return binaryR;
                    }
                    else {
                        std::cout << "Right is Null!" << std::endl;
                        return nullptr;
                    }
                }
            }
            // No match was found. Return nullptr
            return nullptr;
        };
       handleBinaryExprAndUpdateNodes(getExpr, op); 
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
    instances_.push_back(std::make_pair("Left", ExprTypes<Binary, Unary, Grouping, Literal>(factor())));
    while (match({TokenType::MINUS, TokenType::PLUS})) {
      const Token op = previous();
      instances_.push_back(std::make_pair("Right", ExprTypes<Binary, Unary, Grouping, Literal>(factor())));
      std::cout << "Executing inside term!" << std::endl;
      static auto getExpr = [this](bool isLeft) -> Binary* {
            if (expr == nullptr) {
                catcher<parser> cp("EXPR IS NULL!");
                throw cp;
            }
            if (instances_.size() == 0) {
                std::cout << "Code broken!" << std::endl;
            }   
            for (int i = 0; i < instances_.size(); i++) {
                if (idx == i && instances_[i].first == "Left") {
                    if (auto* binaryL = std::get_if<Binary>(instances_[i].second.get())) {
                        std::cout << "Returning Left!" << std::endl;
                        return binaryL;
                    }
                    else {
                        std::cout << "Left is Null!" << std::endl;
                        return nullptr;
                    }
                }
                else if (idx == i && instances_[i].first == "Right") {
                    if (auto* binaryR = std::get_if<Binary>(instances_[i].second.get())) {
                        std::cout << "Returning Right!" << std::endl;
                        return binaryR;
                    }
                    else {
                        std::cout << "Right is Null!" << std::endl;
                        return nullptr;
                    }
                }
            }
            // No match was found. Return nullptr
            return nullptr;
      };
      handleBinaryExprAndUpdateNodes(getExpr, op);  
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
    instances_.push_back(std::make_pair("Left", ExprTypes<Binary, Unary, Grouping, Literal>(unary())));
    while (match({TokenType::SLASH, TokenType::STAR})) {
        const Token op = previous();
        instances_.push_back(std::make_pair("Right", ExprTypes<Binary, Unary, Grouping, Literal>(unary())));
        std::cout << "Executing inside factor!" << std::endl;
        static auto getExpr = [this](bool isLeft) -> Binary* {
            if (expr == nullptr) {
                catcher<parser> cp("EXPR IS NULL!");
                throw cp;
            }
            if (instances_.size() == 0) {
                std::cout << "Code broken!" << std::endl;
            }   
            for (int i = 0; i < instances_.size(); i++) {
                if (idx == i && instances_[i].first == "Left") {
                    if (auto* binaryL = std::get_if<Binary>(instances_[i].second.get())) {
                        std::cout << "Returning Left!" << std::endl;
                        return binaryL;
                    }
                    else {
                        std::cout << "Left is Null!" << std::endl;
                        return nullptr;
                    }
                }
                else if (idx == i && instances_[i].first == "Right") {
                    if (auto* binaryR = std::get_if<Binary>(instances_[i].second.get())) {
                        std::cout << "Returning Right!" << std::endl;
                        return binaryR;
                    }
                    else {
                        std::cout << "Right is Null!" << std::endl;
                        return nullptr;
                    }
                }
            }
            // No match was found. Return nullptr
            return nullptr;
        };
        handleBinaryExprAndUpdateNodes(getExpr, op);
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
        instances_.push_back(std::make_pair("Unary", ExprTypes<Binary, Unary, Grouping, Literal>(unary())));
        std::cout << "Executing inside unary!" << std::endl;
        auto getExpr = [this]() -> Unary* {
            //
            if (expr == nullptr) {
                catcher<parser> cp("EXPR IS NULL!");
                throw cp;
            }
            if (instances_.size() == 0) {
                std::cout << "Code broken!" << std::endl;
            }   
            for (int i = 0; i < instances_.size(); i++) {
                if (idx == i && instances_[i].first == "Unary") {
                    if (auto* unary = std::get_if<Unary>(instances_[i].second.get())) {
                        std::cout << "Returning Unary!" << std::endl;
                        return unary;
                    }
                    else {
                        std::cout << "Unary is Null!" << std::endl;
                        return nullptr;
                    }
                }
            }
            // No match was found. Return nullptr
            return nullptr;

        };
        handleUnaryExprAndUpdateNodes(getExpr, op);
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
        instances_.push_back(std::make_pair("Literal", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(l)));
        static auto getExpr = [this]() -> Literal* {
            if (instances_.size() == 0) {
                std::cout << "Code broken!" << std::endl;
            }   
            for (int i = 0; i < instances_.size(); i++) {
                if (idx == i && instances_[i].first == "Literal") {
                    if (auto* literal = std::get_if<Literal>(instances_[i].second.get())) {
                        std::cout << "Found a match!" << std::endl;
                        return literal;
                    }
                    else {
                        std::cout << "Literal is Null!" << std::endl;
                        // Execption should be thrown here
                        return nullptr;
                    }
                }
            }
            // No match was found. Return nullptr
            return nullptr;
        };
        handleLiteralExprAndUpdateNodes(getExpr);
        return expr;
    }
    if (match({TokenType::TRUE})) {
        std::cout << "Executing inside primary TokenType::TRUE" << std::endl;
        Literal l(true);
        instances_.push_back(std::make_pair("Literal", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(l)));
        auto getExpr = [this]() -> Literal* {
            if (expr == nullptr) {
                catcher<parser> cp("EXPR IS NULL!");
                throw cp;
            }
            if (instances_.size() == 0) {
                std::cout << "Code broken!" << std::endl;
            }   
            for (int i = 0; i < instances_.size(); i++) {
                if (idx == i && instances_[i].first == "Literal") {
                    if (auto* literal = std::get_if<Literal>(instances_[i].second.get())) {
                        return literal;
                    }
                    else {
                        std::cout << "literal is Null!" << std::endl;
                        return nullptr;
                    }
                }
            }
            // No match was found. Return nullptr
            return nullptr;
        };
        handleLiteralExprAndUpdateNodes(getExpr);
        return expr;
    }
    if (match({TokenType::NIL})) {
        std::cout << "Executing inside primary TokenType::NIL" << std::endl;
        Literal l(NULL);
        instances_.push_back(std::make_pair("Literal", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(l)));
        static auto getExpr = [this]() -> Literal* {
            if (expr == nullptr) {
                catcher<parser> cp("EXPR IS NULL!");
                throw cp;
            }
            if (instances_.size() == 0) {
                std::cout << "Code broken!" << std::endl;
            }   
            for (int i = 0; i < instances_.size(); i++) {
                if (idx == i && instances_[i].first == "Literal") {
                    if (auto* literal = std::get_if<Literal>(instances_[i].second.get())) {
                        return literal;
                    }
                    else {
                        std::cout << "Literal is Null!" << std::endl;
                        return nullptr;
                    }
                }
            }
            // No match was found. Return nullptr
            return nullptr;
        };
        handleLiteralExprAndUpdateNodes(getExpr);
        return expr;
    }
    if (match({TokenType::NUMBER, TokenType::STRING})) {
        std::cout << "Executing inside primary TokenType::NUMBER, TokenType::STRING" << std::endl;
        Literal l(previous().getLiteral());
        instances_.push_back(std::make_pair("Literal", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(l)));
        auto getExpr = [this]() -> Literal* {
            if (expr == nullptr) {
                catcher<parser> cp("EXPR IS NULL!");
                throw cp;
            }
            if (instances_.size() == 0) {
                std::cout << "Code broken!" << std::endl;
            }   
            for (int i = 0; i < instances_.size(); i++) {
                if (idx == i && instances_[i].first == "Literal") {
                    if (auto* literal = std::get_if<Literal>(instances_[i].second.get())) {
                        return literal;
                    }
                    else {
                        std::cout << "Literal is Null!" << std::endl;
                        return nullptr;
                    }
                }
            }
            // No match was found. Return nullptr
            return nullptr;
        };
        handleLiteralExprAndUpdateNodes(getExpr);
        return expr;
    }
    if (match({TokenType::LEFT_PAREN})) {
        std::cout << "Executing inside primary TokenType::LEFT_PARAN" << std::endl;
        instances_.push_back(std::make_pair("Grouping", ExprTypes<Binary, Unary, Grouping, Literal>(expression())));
        auto getExpr = [this]() -> Grouping* {
            if (expr == nullptr) {
                catcher<parser> cp("EXPR IS NULL!");
                throw cp;
            }
            if (instances_.size() == 0) {
                std::cout << "Code broken!" << std::endl;
            }   
            for (int i = 0; i < instances_.size(); i++) {
                if (idx == i && instances_[i].first == "Grouping") {
                    if (auto* grouping = std::get_if<Grouping>(instances_[i].second.get())) {
                        return grouping;
                    }
                    else {
                        std::cout << "Grouping is Null!" << std::endl;
                        return nullptr;
                    }
                }
            }
            // No match was found. Return nullptr
            return nullptr;
        };
        handleGroupingExprAndUpdateNodes(getExpr);
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
