#pragma once
#include <parser.h>

/** -------------------------------------------------------------------------
 * @brief Updates the Abstraction Syntax Tree Data Structure
 *
 * @param getExpr is a lambda function
 * @param op is a Token class instance
 *
 * @return it retuns nothing
 * --------------------------------------------------------------------------
*/
void parser::handleBinaryExprAndUpdateNodes(auto& getExpr, const Token& op) {
    auto Left  = getExpr(true);
    std::shared_ptr<Binary> l_Derived = (Left != nullptr) ? std::make_shared<Binary>(*Left) : nullptr;
    std::shared_ptr<Expr<Binary>> L(l_Derived, static_cast<Expr<Binary>*>(l_Derived.get()));
    // Update the Left Expression
    if (isLeft == true) {
        std::any temp_l;
        std::shared_ptr<astTree<int, std::string, std::any>> lr;
        if (l_Derived != nullptr) {
            std::cout << "l_Derived is not Null!" << std::endl;
            temp_l = std::make_any<Binary>(*l_Derived);
            if (typeid(temp_l) == typeid(Binary)) {
                std::cout << "Has Value!" << std::endl;
            }
            astTree<int, std::string, std::any> t = compressedAstTree(idx, "Binary", std::any_cast<Binary>(temp_l));
            lr = std::make_shared<astTree<int, std::string, std::any>>(t);
            instances_.push_back(std::make_pair("Left", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(*l_Derived)));
        }
        else {
            std::cout << "l_Derived is Null!" << std::endl;
            temp_l = std::monostate{};
            astTree<int, std::string, std::any> t = compressedAstTree(idx, "Binary", std::any_cast<std::monostate>(temp_l));
            lr = std::make_shared<astTree<int, std::string, std::any>>(t);
            instances_.push_back(std::make_pair("Left", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(std::any_cast<Binary>(t))));
        }
        node.push_back(*lr);
        idx++;
        isLeft = false;
    }
    else {
        auto Right = getExpr(false);
        std::shared_ptr<Binary> r_Derived = (Right != nullptr) ? std::make_shared<Binary>(*Right) : nullptr;
        std::cout << "Finished calling Right!" << std::endl;
        std::shared_ptr<Expr<Binary>> R(r_Derived, static_cast<Expr<Binary>*>(r_Derived.get()));
        Binary B(L, op, R);
        expr->emplace<Binary>(B);
        // Update the Right Expression
        std::any temp_r;
        std::shared_ptr<astTree<int, std::string, std::any>> rr;
        if (r_Derived != nullptr) {
            temp_r = std::make_any<Binary>(std::move(*r_Derived));
            astTree<int, std::string, std::any> t = compressedAstTree(idx, "Binary", std::any_cast<Binary>(temp_r));
            rr = std::make_shared<astTree<int, std::string, std::any>>(t);
            std::cout << "r_Derived is not null!" << std::endl;
            instances_.push_back(std::make_pair("Right", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(*r_Derived)));
            std::cout << "updated instances_" << std::endl;
        }
        else {
            // NOTE: If both left and right's instance equal the same then we have reached the end of the recrusion 
            // Something that'll be useful for the visitor method 
            std::cout << "r_Derived is null!" << std::endl;
            temp_r = std::monostate{};
            astTree<int, std::string, std::any> t = compressedAstTree(idx, "Binary", std::any_cast<std::monostate>(temp_r));
            rr = std::make_shared<astTree<int, std::string, std::any>>(t);
            instances_.push_back(std::make_pair("Right", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(Binary())));
            std::cout << "updated instances_" << std::endl;
        }
        node.push_back(*rr);
        idx++;
        isLeft = true;
    }
    std::cout << "Executing Line 61" << std::endl;
    return;
}

void parser::handleUnaryExprAndUpdateNodes(auto& getExpr, const Token& op) {
    std::cout << "Finished updating Unary Nodes!" << std::endl;
    std::shared_ptr<Unary> r_Derived = std::make_shared<Unary>(*getExpr());
    std::shared_ptr<Expr<Unary>> R(r_Derived, static_cast<Expr<Unary>*>(r_Derived.get()));
    Unary U(R, op);
    instances_.push_back(std::make_pair("Unary", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(U)));
    std::any temp_r = std::make_any<Unary>(std::move(*r_Derived));
    astTree<int, std::string, Unary> rr = compressedAstTree(idx, std::string("Unary"), std::any_cast<Unary>(temp_r));
    node.push_back(rr);
    idx++;
    std::cout << "Returning expr back! Line 268" << std::endl;
    return;
}

void parser::handleLiteralExprAndUpdateNodes(auto& getExpr) {
    std::shared_ptr<Literal> Derived = std::make_shared<Literal>(*getExpr());
    std::shared_ptr<Expr<Literal>> L(Derived, static_cast<Expr<Literal>*>(Derived.get()));
    std::any temp = std::make_any<Literal>(std::move(*Derived));
    instances_.push_back(std::make_pair("Literal", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(*Derived)));
    astTree<int, std::string, Literal> res = compressedAstTree(idx, std::string("Literal"), std::any_cast<Literal>(temp));
    node.push_back(res);
    idx++;
    return;
}

void parser::handleGroupingExprAndUpdateNodes(auto& getExpr) {
    std::cout << "Updating Group Nodes!" << std::endl;
    auto Grouping_ = getExpr();
    std::shared_ptr<Grouping> Derived = (Grouping_ != nullptr) ? std::make_shared<Grouping>(*Grouping_) : nullptr;
    // Gotta check and see if Derived is null or not 
    std::any temp;
    std::shared_ptr<astTree<int, std::string, std::any>> g;
    if (Derived != nullptr) {
        std::cout << "Grouping is not Null!" << std::endl;
        std::shared_ptr<Expr<Grouping>> L(Derived, static_cast<Expr<Grouping>*>(Derived.get()));
        temp = std::make_any<Grouping>(std::move(*Derived));
        astTree<int, std::string, std::any> t = compressedAstTree(idx, "Binary", std::any_cast<Grouping>(temp));
        g = std::make_shared<astTree<int, std::string, std::any>>(t);
        Grouping G(L);
        instances_.push_back(std::make_pair("Grouping", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(*Derived)));
    }
    else {
        std::cout << "Grouping is Null!" << std::endl;
        temp = std::monostate{};
        astTree<int, std::string, std::any> t = compressedAstTree(idx, "Grouping", std::any_cast<std::monostate>(temp));
        g = std::make_shared<astTree<int, std::string, std::any>>(t);
        instances_.push_back(std::make_pair("Grouping", std::make_shared<std::variant<Binary, Unary, Grouping, Literal>>(Grouping())));
    }
    node.push_back(*g);
    idx++;
    std::cout << "Returning from Updating Group Nodes!" << std::endl;
    return;
}

