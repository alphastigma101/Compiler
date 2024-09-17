#include <scanner.h>
#include <parser.h>
#include <interpreter.h> 
struct testCurrentLanguageType {
        void setTokenLanguage(const LanguageTokenTypes& value);
        LanguageTokenTypes getTokenLanguage();
        LanguageTokenTypes currentLanguage;
    };
void testCurrentLanguageType::setTokenLanguage(const LanguageTokenTypes& value) { currentLanguage = value; };
LanguageType<LanguageTokenTypes> testCurrentLanguageType::getTokenLanguage() { return currentLanguage; };
testCurrentLanguageType user_type;
auto temp = user_type.getTokenLanguage();

int main(int argc, char **argv) {
    user_type.setTokenLanguage(LanguageTokenTypes::Python);
    Scanner scanner("((34 + 15) / (12 * 6))");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.parse();
    interpreter interp(std::move(p.nodes), std::move(temp));
    return 0;
}
