#ifndef _CONTEXT_FREE_GRAMMAR_H_
#define _CONTEXT_FREE_GRAMMAR_H_
#include <run_time_error.h>
#include <catch.h>
#include <filesystem>
/*
 * A Context Free Grammar consists of a head and a body, which describes what it can generate.
 * The body's purest form will be a list of symbols and these symbols are:
    * (Terminal):
        * letter from the grammar’s alphabet, which you can think of it as a literal value. They are the endpoints in a sense as you only produce one symbol
    * (Nonterminal):
        * is a reference of another grammar rule, which allows you to pick any rules for it 
 * The rule is on the very left side of the ->. On the other side of it are: 
    * Quoted strings which represent the "terminal"
    * Lowercase letters that are  "nonterminal"
*/


namespace ContextFreeGrammar {
    template<typename Derived>
    class Expr: public logging<Derived>, public runtimeerror<Derived>, public catcher<Derived> {
        /* ------------------------------------------------------------------------------------------
         * A representation of an abstraction classs which is also considered as a disoriented object
         * ------------------------(Additional Info Below)-------------------------------------------
         * By creating an abstraction class, and allowing a class to inherit it, you basically are allowing them to communicate with eachother
         * Which allows it to not be associated with any type of behavior which usually methods/functions etc are what defined the behavior of an object
         * ------------------------------------------------------------------------------------------
         */
        public:
            friend class Binary;
            friend class Unary;
            friend class Grouping;
            friend class Literal;
            ~Expr() noexcept {};
            /**
             * @brief Accepts a visitor for processing this node.
             *
             * This method is part of the Visitor design pattern. It accepts a visitor instance that performs operations on this node.
             *
             * @details
             * When you call `Binary_1->accept(visitor)`, the traversal starts with the node `Binary_1`.
             * Inside `Binary_1::accept(visitor)`, the `visit(*this)` call is made. Here, `*this` refers to `Binary_1`.
             *
             * The method then recursively processes the left and right children:
             * - **Recursive Call to `expr.left`**:
             *   - `expr.left` points to `Binary_2`. So, `expr.left->accept(*this)` translates to `Binary_2->accept(visitor)`.
             *   - Inside `Binary_2::accept(visitor)`, `visit(*this)` is called, where `*this` refers to `Binary_2`.
             * - **Processing `Binary_2`**:
             *   - Inside `Binary_2::accept(visitor)`, `visit(*this)` processes `Binary_2`.
             *   - Since `Binary_2` has no children (both `left` and `right` are `nullptr`), the `visit` method returns an empty string for both `leftResult` and `rightResult`.
             * - **Returning to `Binary_1`**:
             *   - The result from `Binary_2` is returned to `Binary_1`, setting `leftResult` to this result.
             *   - Similarly, `expr.right->accept(*this)` is called for `Binary_3`, following the same process.
             * - **Processing `Binary_3`**:
             *   - The process for `Binary_3` is similar: `visit(*this)` processes `Binary_3`, and since it has no children, empty strings are returned for `leftResult` and `rightResult`.
             * - **Combining Results**:
             *   - After processing both children, `Binary_1` combines the results from `Binary_2` and `Binary_3`, and returns the final result.
             *
             * @param visitor The visitor instance used to process this node.
             *
             * @return A `std::string` representing the result of processing this node and its children.
             *
             * @note Potential Issues:
             * - **Dereferencing Null Pointers**: Ensure that child pointers (`left` and `right`) are checked for `nullptr` before dereferencing to avoid undefined behavior.
             * - **Infinite Recursion**: If the tree structure is not properly maintained (e.g., cycles or incorrect pointers), it may lead to infinite recursion.
             * - **Stack Overflow**: Because c++ uses a call stack. Regardless if the previous call is the same thing. It stil pushes the function call onto the stack with it's own local variables.
             *      - It pushes main on the stack and then followed by other functions which are dynamically allocated using new. 
             *      - Stack overflow can occur if the call stack exceeds the limited size which you could most likely increase for your compiler.
             *
             * The Visitor pattern is used to separate operations from the objects they operate on, allowing new operations to be added without modifying the objects.
             */
            inline std::string accept(Expr& visitor) {
                try {
                    // Derived* points to whatever class was passed. Casts from std::any to Derived 
                    // If a bug occurs here, then potential cases as to why are:
                    // the correct class was not passed 
                    // this referencing the abstract class 
                    // so basically, it is going from reference (this) to pointy (Derived*) which is why the ->visit works 
                    return std::any_cast<Derived*>(this)->visit(std::move(static_cast<Derived&>(visitor)));
                }
                catch(...) {
                    throw runtimeerror<Derived>(nullptr, std::any_cast<std::string>(visitor.left->op->toString()) + std::any_cast<std::string>(visitor.right->op->toString()));
                }
            };
            Expr* right;
            Expr* left;
            Token* op;
        private:
            logTable<std::map<std::string, std::vector<std::string>>> logs_;
     };
    class Binary: public Expr<Binary> {
        /*
         * A class that represents a binary abstraction syntax tree
         * ------------------------(Additional Info Below)-------------------------------------------
         * The 'visiting design pattern' is crucial for the abstraction syntax tree to work as it will visit the nodes
         * It relies on recrusion to visit every node in a graph or tree 
         * ------------------------(Example of Ast Tree)---------------------------------------------
                  *
                 / \
                /   \
                -   ()
               /      \
              123      45.67
         * Would print out this: (* (- 123) (group 45.67)) Note: Parathesis are always included 
         */
        public:
            // List initalize initializes the variable this->left and this->right which there is no need for the copy initialization
            Binary(Expr<Binary>& left_, const Token& op_, Expr<Binary>& right_): left(&left_), right(&right_)  {
                try {
                    // TODO: Swap to smart pointers instead of raw pointers
                    // Initialize the Address of the pointers
                    this->left = left;
                    op = op_;
                    this->op = op;
                }
                catch(...) {
                    throw catcher<Binary>("Undefined behavior occurred in Class Binary!");
                }
            };
            ~Binary() noexcept = default;
            /* ----------------------------------------------------------------------------------------------------------
             * @brief visitor gets called finite amount of times and is placed on the call stack with it's own variables 
             *
             *
             */
            inline std::string visit(Binary&& expr) {
                try {
                    std::string leftResult = expr.left ? expr.left->accept(*this) : "";
                    std::string rightResult = expr.right ? expr.right->accept(*this) : "";
                    return " " + leftResult + " " + rightResult;
                }
                catch(runtimeerror<Binary>& e) {
                    std::string temp = std::string("on line:" + std::to_string(expr.op.getLine()) + " " + e.what());
                    logging(logs_, temp); // Keep the logs updated throughout the whole codebase
                    logging<Binary>update;
                    logging<Binary>rotate;
                }
                return "\0";
            };
            inline Token getToken() { return op; };
        private:
            Expr* left;
            Expr* right;
            Token op;
    };
    class Unary: public Expr<Unary> {
        public:
            Unary(Expr& right_, const Token& op_): right(&right_) {
                try {
                    this->right = right;
                    op = op_;
                    this->op = op_;
                }
                catch(...) {
                    throw catcher<Unary>("Undefined behavior occurred in Class Unary!");
                }
            };
            ~Unary() noexcept = default;
            inline std::string visit(Unary&& expr) {
                try {
                    std::string rightResult = expr.right->accept(*this);
                    return " " + rightResult;
                }
                catch(runtimeerror<Unary>& e) {
                    std::string temp = std::string("on line:" + std::to_string(expr.op.getLine()) + " " + e.what());
                    logging(logs_, temp); // Keep the logs updated throughout the whole codebase
                    logging<Unary>update;
                    logging<Unary>rotate;
                }
                return "\0";
            };
            inline Token getToken() { return op; };
        private:
            Expr* right;
            Token op;
    };
    class Grouping: public Expr<Grouping> {
        public:
            explicit Grouping(const Expr& expression) {
                this->expression->left = expression.left;
                this->expression->right = expression.right;
            };
            ~Grouping() noexcept = default;
            inline std::string visit(Grouping&& expr) {
                try {
                    std::string leftResult = expr.left->accept(*this);
                    std::string rightResult = expr.right->accept(*this);
                    return "(" + leftResult + " " + rightResult + ")";
                }
                catch(runtimeerror<Grouping>& e) {
                    std::string temp = std::string("on line:" + std::to_string(expr.op->getLine()) + " " + e.what());
                    logging(logs_, temp); // Keep the logs updated throughout the whole codebase
                    logging<Grouping>update;
                    logging<Grouping>rotate;
                }
                return "\0";
            };
        inline Expr* getExpr() { return expression; }
        private:
            Expr* expression;
    };
    class Literal: public MemberConv<Literal>, public Expr<Literal> {
        public:
            explicit Literal(const auto& value): value(this->value) {
                try {
                    this->op = op;
                }
                catch(...) {
                    throw catcher<Literal>("Undefined behavior occurred in Class Literal!");
                }
            };
            ~Literal() = default;
            inline std::string visit(Literal&& expr) {
                try {
                    std::string literal = std::any_cast<bool>(expr) ? expr.accept(*this) : "";
                    return literal;
                }
                catch(runtimeerror<Literal>& e) {
                    std::string temp = std::string("on line:" + std::to_string(expr.op->getLine()) + " " + e.what());
                    logging(logs_, temp); // Keep the logs updated throughout the whole codebase
                    logging<Literal>update;
                    logging<Literal>rotate;
                }
                return "\0";
            };
            inline std::any toString() override {
                try {
                    return std::any_cast<std::string>(value);
                } 
                catch (std::bad_any_cast& e) {
                    auto l = std::any_cast<Literal>(value);
                    std::string temp = std::to_string(l.op->getLine());
                    logging(logs_, "on line:" + temp + " " + e.what()); // Keep the logs updated throughout the whole codebase
                    logging<Literal>update;
                    logging<Literal>rotate;
                    return "error:" + std::string(e.what());
                }
            };
            inline std::any getValue() { return value; };
            inline Token* getToken() { return op; };
        private:
            std::any value;
            Token* op;
    };
};
using namespace ContextFreeGrammar;
#endif 
