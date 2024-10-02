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
    class Expr {
        /** ------------------------------------------------------------------------------------------
         * @brief A representation of an abstraction classs which is also considered as a disoriented object
         *
         * @details By creating an abstraction class, and allowing a class to inherit it, you basically are allowing them to communicate with eachother
         *          Which allows it to not be associated with any type of behavior which usually methods/functions etc are what defined the behavior of an object
         * ------------------------------------------------------------------------------------------
        */
        public:
            /** --------------------------------------------------------
             * @brief left represents the left binary node.
             * ---------------------------------------------------------
            */
            Unique<Expr> left;
            /** --------------------------------------------------------
             * @brief right represents the left binary node.
             * ---------------------------------------------------------
            */
            Unique<Expr> right;
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Unique<Token> op;
            /** --------------------------------------------------------
             * @brief expression represents the left/right binary nodes.
             *        It does not represent its own nodes. Used with Grouping class
             * ---------------------------------------------------------
            */
            Unique<Expr> expression;
            virtual ~Expr() noexcept = default;
        protected:
            int idx = 0;
            Expr() = default;
            Expr(const Expr&) = default;
            Expr(Expr&&) = default;
            Expr& operator=(const Expr&) = default;
            Expr& operator=(Expr&&) = default;
    };
    class Binary: public Expr, public Visitor<Binary>, public logging<Binary>, public runtimeerror<Binary>, public catcher<Binary> {
        /** --------------------------------------------------------------------
             * @brief A class that represents a binary abstraction syntax tree
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
            friend class runtimeerror<Binary>; // Use to output TokenType and message
            friend class catcher<Binary>; // Use to output a message
            friend class Visitor<Binary>;
            explicit Binary(Unique<Expr> left_, const Token& op_, Unique<Expr> right_);
            explicit Binary(Unique<Expr> expr, bool move) noexcept;
            Binary(Binary&&) = default;
            ~Binary() noexcept = default; // Using Virtual when it shouldn't. So I am mis-understanding something
            inline Token getToken() { return *op; };
            inline String accept(Binary&) { return visit(std::move(*this)); };
        protected:
            Binary() = default;
            Binary(const Binary&) = default;
            Binary& operator=(const Binary&) = default;
            Binary& operator=(Binary&&) = default;
        private:
            inline static logTable<Map<String, Vector<String>>> logs_;
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Binary>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(TokenType&& type = runtimeerror<Binary>::getType(), const char* msg = runtimeerror<Binary>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                }
                catch(...) {
                    std::cout << "Error! conversion has failed!" << std::endl;
                }
            };
            static String parenthesize(String name, Expr& left, Expr& right);
            inline String visit(Binary&& expr) { return parenthesize(expr.op.get()->getLexeme(), *(expr.left.get()), *(expr.right.get())); };
    };
    class Unary: public Expr, public Visitor<Unary>, public logging<Unary>, public runtimeerror<Unary>, public catcher<Unary> {
        public:
            friend class runtimeerror<Unary>; // Use to output TokenType and message
            friend class catcher<Unary>; // Use to output a message
            friend class Visitor<Unary>;
            explicit Unary(Unique<Expr> right_, const Token& op_);
            explicit Unary(Unique<Expr> expr) noexcept;
            Unary(Unary&&) = default;
            ~Unary() noexcept = default;
            inline Token getToken() { return *op; };
        protected:
            Unary() = default;
            Unary(const Unary&) = default;
            Unary& operator=(const Unary&) = default;
            Unary& operator=(Unary&&) = default;
        private:
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Unary>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(TokenType&& type = runtimeerror<Unary>::getType(), const char* msg = runtimeerror<Unary>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                }
                catch(...) {
                    std::cout << "Error! conversion has failed!" << std::endl;
                }
            };
            static String parenthesize(String name, Expr& expr);
            inline String visit(Unary&& expr) { return parenthesize(expr.op.get()->getLexeme(), *(expr.right.get())); };
            inline String accept(Unary&) { return visit(std::move(*this)); };
    };
    class Grouping: public Expr, public  Visitor<Grouping>, public logging<Grouping>, public runtimeerror<Grouping>, public catcher<Grouping> {
        public:
            friend class runtimeerror<Grouping>; // Use to output TokenType and message
            friend class catcher<Grouping>; // Use to output a message
            friend class Visitor<Grouping>;
            /** ----------------------------------------------------------------------------------------------------------
             * @brief constructor for creating the memory addresses that will later on be accessed by a vector 
             *
             * @param expression is an rvalue that will get destroyed once it leaves the scope
             *
             * 
             * @details expression is used to represent grouping class. 
             *          It points to the left and right binary node trees
            */
            explicit Grouping(Unique<Expr> expression);
            explicit Grouping(Unique<Expr> expression, bool move);
            ~Grouping() noexcept = default;
            Grouping(Grouping&&) = default;
            inline Token getToken() { return *op; };
        //protected:
            Grouping() = default;
            Grouping(const Grouping&) = default;
            Grouping& operator=(const Grouping&) = default;
            Grouping& operator=(Grouping&&) = default;
        private:
           inline static logTable<std::map<String, Vector<String>>> logs_;
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Grouping>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(TokenType&& type = runtimeerror<Grouping>::getType(), const char* msg = runtimeerror<Grouping>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                }
                catch(...) {
                    std::cout << "Error! conversion has failed!" << std::endl;
                }
            };
            static String parenthesize(String name, Expr& expr);
            inline String visit(Grouping&& expr) { return parenthesize("group", *(expr.expression.get())); };
            inline String accept(Grouping&) { return visit(std::move(*this)); };
    };
    class Literal: public Expr, public Visitor<Literal>, public logging<Literal>, public runtimeerror<Literal>, public catcher<Literal> {
        public:
            friend class runtimeerror<Literal>; // Use to output TokenType and message
            friend class catcher<Literal>; // Use to output a message
            friend class Visitor<Literal>;
            explicit Literal(const Token&& oP);
            ~Literal() noexcept = default;
            inline Token getToken() { return *op; };
            inline String accept(Literal&) { return visit(std::move(*this)); };
        private:
            inline static logTable<std::map<String, Vector<String>>> logs_;
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Literal>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(TokenType&& type = runtimeerror<Literal>::getType(), const char* msg = runtimeerror<Literal>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                }
                catch(...) {
                    std::cout << "Error! conversion has failed!" << std::endl;
                }
            };
            String visit(Literal&& expr);
        protected:
            Literal() = default;
            Literal(const Literal&) = default;
            Literal(Literal&&) = default;
            Literal& operator=(const Literal&) = default;
            Literal& operator=(Literal&&) = default;     
    };
    class Methods: public Expr, public  Visitor<Methods>, public logging<Methods>, public runtimeerror<Methods>, public catcher<Methods> {
        public:
            friend class runtimeerror<Methods>; // Use to output TokenType and message
            friend class catcher<Methods>; // Use to output a message
            friend class Visitor<Methods>;
            explicit Methods(Unique<Expr> meth, const Token& op_);
            ~Methods() noexcept = default;
        protected:
            Methods() = default;
            Methods(const Methods&) = default;
            Methods(Methods&&) = default;
            Methods& operator=(const Methods&) = default;
            Methods& operator=(Methods&&) = default;
        private:
            inline static logTable<std::map<String, Vector<String>>> logs_;
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Methods>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(TokenType&& type = runtimeerror<Methods>::getType(), const char* msg = runtimeerror<Methods>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                }
                catch(...) {
                    std::cout << "Error! conversion has failed!" << std::endl;
                }
            };
            static String parenthesize(String name, Expr& expr);
            String visit(Methods&& expr);
            String accept(Methods&);
    };
    class Arguments: public Expr, public Visitor<Arguments>, public logging<Arguments>, public runtimeerror<Arguments>, public catcher<Arguments> {
        public:
            friend class runtimeerror<Arguments>; // Use to output TokenType and message
            friend class catcher<Arguments>; // Use to output a message
            friend class Visitor<Arguments>;
            explicit Arguments(Unique<Expr> arg, const Token& op_);
            ~Arguments() noexcept = default;
        private:
            Unique<Token> op;
            inline static logTable<std::map<String, Vector<String>>> logs_;
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Arguments>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(TokenType&& type = runtimeerror<Arguments>::getType(), const char* msg = runtimeerror<Arguments>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                }
                catch(...) {
                    std::cout << "Error! conversion has failed!" << std::endl;
                }
            };
            static String parenthesize(String name, Expr& expr);
            String visit(Arguments&& expr);
            String accept(Arguments&);
        protected:
            Arguments() = default;
            Arguments(const Arguments&) = default;
            Arguments(Arguments&&) = default;
            Arguments& operator=(const Arguments&) = default;
            Arguments& operator=(Arguments&&) = default;
    };
    class EcoSystem: public Expr, public Visitor<EcoSystem>, public logging<EcoSystem>, public runtimeerror<EcoSystem>, public catcher<EcoSystem> {
        public:
            friend class runtimeerror<EcoSystem>; // Use to output TokenType and message
            friend class catcher<EcoSystem>; // Use to output a message
            friend class Visitor<EcoSystem>;
            explicit EcoSystem(Unique<Expr> ecoSystem, const Token& op_);
            ~EcoSystem() noexcept = default;
        private:
            Unique<Token> op;
            inline static logTable<std::map<String, Vector<String>>> logs_;
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<EcoSystem>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(TokenType&& type = runtimeerror<EcoSystem>::getType(), const char* msg = runtimeerror<EcoSystem>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                }
                catch(...) {
                    std::cout << "Error! conversion has failed!" << std::endl;
                }
            };
            static String parenthesize(String name, Expr& expr);
            String visit(EcoSystem&& expr);
            String accept(EcoSystem&);
        protected:
            EcoSystem() = default;
            EcoSystem(const EcoSystem&) = default;
            EcoSystem(EcoSystem&&) = default;
            EcoSystem& operator=(const EcoSystem&) = default;
            EcoSystem& operator=(EcoSystem&&) = default;
    };
};
using namespace ContextFreeGrammar;
#endif 
