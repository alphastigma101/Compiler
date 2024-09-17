#ifndef _CONTEXT_FREE_GRAMMAR_H_
#define _CONTEXT_FREE_GRAMMAR_H_
#include <logging.h>
#include <token.h>
#include <filesystem>
/*
 * A Context Free Grammar consists of a head and a body, which describes what it can generate.
 * The body's purest form will be a list of symbols and these symbols are:
    * (Terminal):
        * letter from the grammar’s alphabet, which you can think of it as a literal value.  They are the endpoints in a sense as you only produce one symbol
        * In a sense, the symbol will represent a token of some sort 
    * (Nonterminal):
        * is a reference of another grammar rule, which allows you to pick any rules for it 
 * The rule is on the very left side of the ->. On the other side of it are: 
    * Quoted strings which represent the "terminal"
    * Lowercase letters that are  "nonterminal"
*/


namespace ContextFreeGrammar {
    template<typename Derived>
    class VisitExpr: public logging<Derived>, public runtimeerror<Derived>, public catcher<Derived> {
        /* ------------------------------------------------------------------------------------------
         * @brief A representation of an abstraction classs which is also considered as a disoriented object
         *
         * @details By creating an abstraction class, and allowing a class to inherit it, you basically are allowing them to communicate with eachother
         *          Which allows it to not be associated with any type of behavior which usually methods/functions etc are what defined the behavior of an object
         * ------------------------------------------------------------------------------------------
        */
        public:
            friend class Binary;
            friend class Unary;
            friend class Grouping;
            friend class Literal;
            friend class runtimeerror<Derived>;
            friend class catcher<Derived>;
            ~VisitExpr() noexcept {};
            /**
             * @brief Accepts a visitor for processing this node.
             *
             * This method is part of the Visitor design pattern. It accepts a visitor instance that performs operations on this node.
             *
             * @details When you call `Binary_1->accept(visitor)`, the traversal starts with the node `Binary_1`.
             *          Inside `Binary_1::accept(visitor)`, the `visit(*this)` call is made. Here, `*this` refers to `Binary_1`.
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
            inline std::string accept(VisitExpr& visitor) {
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
                    return "\0";
                }
                return "\0";
            };
        private:
            inline static logTable<std::map<std::string, std::vector<std::string>>> logs_;
            inline static const char* what(const char* msg = catcher<Derived>::getMsg()) throw() { return msg;};
            inline const char* what(TokenType&& type = runtimeerror<Derived>::getType(), const char* msg = runtimeerror<Derived>::getMsg()) throw() { 
                return static_cast<Derived*>(this)->what(type, msg); 
            }; 
     };
    class Binary: public VisitExpr<Binary> {
        /* --------------------------------------------------------------------
             * @breif A class that represents a binary abstraction syntax tree
             * 
             * @details The 'visiting design pattern' is crucial for the abstraction syntax tree to work as it will visit the nodes
             *          It relies on recrusion to visit every node in a graph or tree 
             *          ---------------(Example of Ast Tree)--------------
                                              *
                                             / \
                                            /   \
                                            -   ()
                                           /      \
                                          123      45.67
             *          Would print out this: (* (- 123) (group 45.67)) Note: Parathesis are always included 
         */
        public:
            explicit Binary(std::shared_ptr<ExprVariant>& left_, const Token& op_, std::shared_ptr<ExprVariant>& right_); 
            ~Binary() noexcept = default;
            /* ----------------------------------------------------------------------------------------------------------
             * @brief visitor will visit each binary node forming a tree of some sort 
             *
             * @param expr is an rvalue that will get destroyed once it leaves the scope
             *
             * @details visitor gets called finit amount of times and is placed on the call stack with it's own variables
            */
            inline std::string visit(Binary&& expr) {
                try {
                    std::string leftResult = (expr.Left.get() && std::get_if<Binary>(expr.Left.get())) ? std::get_if<Binary>(expr.Left.get())->accept(*this) : "";
                    std::string rightResult = (expr.Right.get() && std::get_if<Binary>(expr.Left.get())) ? std::get_if<Binary>(expr.Right.get())->accept(*this) : "";
                    return " " + leftResult + " " + rightResult;
                }
                catch(runtimeerror<Binary>& e) {
                    //std::string temp = std::string("on line:" + std::to_string(expr.getToken().getLine()) + " " + e.what());
                    //logging<Binary> logs(logs_, temp); 
                    //logs.update();
                    //logs.write();
                    //logs.rotate();
                }
                return "\0";
            };
            inline static Token getToken() { return *op; };
        private:
            inline static std::shared_ptr<ExprVariant> Left;
            inline static std::shared_ptr<ExprVariant> Right;
            inline static std::shared_ptr<Token> op;
    };
    class Unary: public VisitExpr<Unary> {
        public:
            explicit Unary(std::shared_ptr<ExprVariant>& right_, const Token& op_);  
            ~Unary() noexcept = default;
            /* ----------------------------------------------------------------------------------------------------------
             * @brief visitor will visit each unary node forming a tree of some sort 
             *
             * @param expr is an rvalue that will get destroyed once it leaves the scope
             *
             * @details visitor gets called finit amount of times and is placed on the call stack with it's own variables
            */
            inline std::string visit(Unary&& expr) {
                try {
                    std::string rightResult = (expr.Right.get() && std::get_if<Unary>(expr.Right.get())) ? std::get_if<Unary>(expr.Right.get())->accept(*this) : "";
                    return " " + rightResult;
                }
                catch(runtimeerror<Unary>& e) {
                    //std::string temp = std::string("on line:" + std::to_string(expr.getToken().getLine()) + " " + e.what());
                    //logging<Unary> logs(logs_, temp); // Keep the logs updated throughout the whole codebase
                    //logs.update();
                    //logs.write();
                    //logs.rotate();
                }
                return "\0";
            };
            inline static Token getToken() { return *op; };
        private:
            inline static std::shared_ptr<ExprVariant> Right;
            inline static std::shared_ptr<Token> op;
    };
    class Grouping: public VisitExpr<Grouping> {
        public:
            explicit Grouping(std::shared_ptr<ExprVariant>& expression, Token&& oP);
            ~Grouping() noexcept = default;
            /* ----------------------------------------------------------------------------------------------------------
             * @brief visitor will visit each unary node forming a tree of some sort 
             *
             * @param expr is an rvalue that will get destroyed once it leaves the scope
             *
             * @details visitor gets called finit amount of times and is placed on the call stack with it's own variables
            */
            inline std::string visit(Grouping&& expr) {
                try {
                    std::string leftResult = (expr.Left.get() && std::get_if<Grouping>(expr.Left.get())) ? std::get_if<Grouping>(expr.Left.get())->accept(*this) : "";
                    std::string rightResult = (expr.Right.get() && std::get_if<Grouping>(expr.Right.get())) ? std::get_if<Grouping>(expr.Right.get())->accept(*this) : "";
                    return "(" + leftResult + " " + rightResult + ")";
                }
                catch(runtimeerror<Grouping>& e) {
                    //std::string temp = std::string("on line:" + std::to_string(expr.getToken().getLine()) + " " + e.what());
                    //logging<Grouping> logs(logs_, temp); // Keep the logs updated throughout the whole codebase
                    //logs.update();
                    //logs.write();
                    //logs.rotate();
                }
                return "\0";
            };
            inline static Token getToken() { return *op; };
        private:
           inline static std::shared_ptr<ExprVariant> expression_;
           inline static std::shared_ptr<ExprVariant> Left, Right; 
           inline static std::shared_ptr<Token> op;
    };
    class Literal: public MemberConv<Literal>, public VisitExpr<Literal> {
        public:
            explicit Literal(const auto& value, Token&& op_) {
                try {
                    value_ = std::make_any<std::any>(value);
                    op = std::make_shared<Token>(std::move(op_));
                }
                catch(...) {
                    catcher<Literal> cl("Undefined behavior occurred in Class Literal!");
                    throw cl;
                }
            };
            ~Literal() noexcept = default;
            inline std::string visit(Literal&& expr) {
                try {
                    std::string literal = std::any_cast<bool>(expr) ? expr.accept(*this) : "";
                    return literal;
                }
                catch(runtimeerror<Literal>& e) {
                    //std::string temp = std::string("on line:" + std::to_string(expr.getToken().getLine()) + " " + e.what());
                    //logging<Literal> logs(logs_, temp); // Keep the logs updated throughout the whole codebase
                    //logs.update();
                    //logs.write();
                    //logs.rotate();
                }
                return "\0";
            };
            inline std::any toString() {
                try {
                    return std::any_cast<std::string>(value_);
                } 
                catch (std::bad_any_cast& e) {
                    std::string temp = std::to_string(getToken().getLine());
                    logging<Literal> logs(logs_, "on line:" + temp + " " + e.what()); // Keep the logs updated throughout the whole codebase
                    logs.update();
                    logs.write();
                    logs.rotate();
                    return "error:" + std::string(e.what());
                }
            };
            inline static std::any getValue() { return value_; };
            inline static Token getToken() { return *op; };
        private:
            inline static std::any value_;
            inline static std::shared_ptr<Token> op;
    };
    /*class Methods: public VisitExpr<Methods>, public catcher<Methods>, public logging<Methods> {
        public:
            explicit Methods(std::shared_ptr<ExprVariant> methods_, const Token& op_);
            ~Methods() noexcept = default;
        private:
            inline static Shared<Token> op;
    };
    class Arguments: VisitExpr<Arguments>, public catcher<Arguments>, public logging<Arguments> {
        public:
            explicit Arguments(std::shared_ptr<ExprVariant> arg, const Token& op_);
            ~Arguments() noexcept = default;
        private:
            inline static Shared<Token> op;
        
    };
    class EcoSystem: public VisitExpr<EcoSystem>, public catcher<Arguments>, public logging<EcoSystem> {
        public:
            explicit EcoSystem(std::shared_ptr<ExprVariant> ecoSystem, const Token& op_);
            ~EcoSystem() noexcept = default;
        private:
            inline static Shared<Token> op;
    };*/
};
using namespace ContextFreeGrammar;
#endif 
