#ifndef _CONTEXT_FREE_GRAMMAR_H_
#define _CONTEXT_FREE_GRAMMAR_H_
#include <run_time_error.h>
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
                    //TODO: Replace the nullptr with something else
                    //runtimeerror<Derived> r(nullptr, std::any_cast<std::string>(visitor.left->op->toString()) + std::any_cast<std::string>(visitor.right->op->toString()));
                    //throw r;
                }
            };
            std::shared_ptr<Expr> right;
            std::shared_ptr<Expr> left;
            std::shared_ptr<Token> op;
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
            friend class ::Parser::parser;
            // List initalize initializes the variable this->left and this->right which there is no need for the copy initialization
            Binary(std::shared_ptr<Expr<Binary>>& left_, const Token& op_, std::shared_ptr<Expr<Binary>>& right_): Left(left_), Right(right_)  {
                try {
                    left = Left; // transfer the object resources to the abstract class data member left
                    right = Right; // transfer the object resources to the abstract class data member right
                    op = std::make_shared<Token>(op_);
                }
                catch(...) {
                    catcher<Binary> cb("Undefined behavior occurred in Class Binary!");
                    throw cb;
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
                    std::string leftResult = expr.left.get() ? expr.left.get()->accept(*this) : "";
                    std::string rightResult = expr.right.get() ? expr.right.get()->accept(*this) : "";
                    return " " + leftResult + " " + rightResult;
                }
                catch(runtimeerror<Binary>& e) {
                    std::string temp = std::string("on line:" + std::to_string(expr.op.get()->getLine()) + " " + e.what());
                    logging<Binary> logs(logs_, temp); 
                    logs.update();
                    logs.write();
                    logs.rotate();
                }
                return "\0";
            };
            inline Token getToken() { return *op; };
        protected:
            Binary() = default;
        private:
            std::shared_ptr<Expr> Left;
            std::shared_ptr<Expr> Right;
            std::shared_ptr<Token> op_;
    };
    class Unary: public Expr<Unary> {
        public:
            friend class ::Parser::parser;
            Unary(std::shared_ptr<Expr<Unary>>& right_, const Token& op_): Right(right_), Op(std::make_shared<Token>(op_))  {
                try {
                    right = Right;
                    op = Op;
                }
                catch(...) {
                    catcher<Unary> cu("Undefined behavior occurred in Class Unary!");
                    throw cu;
                }
            };
            ~Unary() noexcept = default;
            inline std::string visit(Unary&& expr) {
                try {
                    std::string rightResult = expr.right->accept(*this);
                    return " " + rightResult;
                }
                catch(runtimeerror<Unary>& e) {
                    std::string temp = std::string("on line:" + std::to_string(expr.Op.get()->getLine()) + " " + e.what());
                    logging<Unary> logs(logs_, temp); // Keep the logs updated throughout the whole codebase
                    logs.update();
                    logs.write();
                    logs.rotate();
                }
                return "\0";
            };
            inline Token getToken() { return *Op; };
        protected:
            Unary() = default;
        private:
            std::shared_ptr<Expr> Right;
            std::shared_ptr<Token> Op;
    };
    class Grouping: public Expr<Grouping> {
        public:
            friend class ::Parser::parser;
            explicit Grouping(std::shared_ptr<Expr<Grouping>>& expression) {
                expression_->left = expression->left;
                expression_->right = expression->right;
            };
            ~Grouping() noexcept = default;
            inline std::string visit(Grouping&& expr) {
                try {
                    std::string leftResult = expr.left.get()->accept(*this);
                    std::string rightResult = expr.right.get()->accept(*this);
                    return "(" + leftResult + " " + rightResult + ")";
                }
                catch(runtimeerror<Grouping>& e) {
                    std::string temp = std::string("on line:" + std::to_string(expr.op->getLine()) + " " + e.what());
                    logging<Grouping> logs(logs_, temp); // Keep the logs updated throughout the whole codebase
                    logs.update();
                    logs.write();
                    logs.rotate();
                }
                return "\0";
            };
            inline Expr<Grouping> getExpr() { return *expression_; }
        protected:
            Grouping() = default;
        private:
            std::shared_ptr<Expr> expression_;
    };
    class Literal: public MemberConv<Literal>, public Expr<Literal> {
        public:
            friend class ::Parser::parser;
            explicit Literal(const auto& value) {
                try {
                    value_ = std::make_any<std::any>(value);
                    op_ = op;
                }
                catch(...) {
                    catcher<Literal> cl("Undefined behavior occurred in Class Literal!");
                    throw cl;
                }
            };
            ~Literal() = default;
            inline std::string visit(Literal&& expr) {
                try {
                    std::string literal = std::any_cast<bool>(expr) ? expr.accept(*this) : "";
                    return literal;
                }
                catch(runtimeerror<Literal>& e) {
                    std::string temp = std::string("on line:" + std::to_string(expr.op_->getLine()) + " " + e.what());
                    logging<Literal> logs(logs_, temp); // Keep the logs updated throughout the whole codebase
                    logs.update();
                    logs.write();
                    logs.rotate();
                }
                return "\0";
            };
            inline std::any toString() override {
                try {
                    return std::any_cast<std::string>(value_);
                } 
                catch (std::bad_any_cast& e) {
                    auto l = std::any_cast<Literal>(value_);
                    std::string temp = std::to_string(l.op.get()->getLine());
                    logging<Literal> logs(logs_, "on line:" + temp + " " + e.what()); // Keep the logs updated throughout the whole codebase
                    logs.update();
                    logs.write();
                    logs.rotate();
                    return "error:" + std::string(e.what());
                }
            };
            inline std::any getValue() { return value_; };
            inline Token getToken() { return *op_; };
        protected:
            Literal() = default;
        private:
            std::any value_;
            std::shared_ptr<Token> op_;
    };
};
using namespace ContextFreeGrammar;
#endif 
