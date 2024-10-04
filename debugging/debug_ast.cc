#include <cxxabi.h>
#include <abstraction_tree_syntax.h>
#include <scanner.h>
#include <parser.h>
int main(void) {
   Vector<String> test_strs = {
        /*"(45 > 67)", 
        "(67 / 70)", 
        "(99 <= 100)",  
        "(88 == 88)",  
        "(34 * 2)",  
        "(16 - 5)",  
        "(23 != 24)", 
        "(56 >= 12)", 
        "(15 + 19)",  
        "(7 * 3)",*/
        "(((32 * 17) + (9 - 11) / 2) >= (49 * 3 / (6 + 2)) + (99 <= 100)) - ((12 * 2 - 45 / 5) != (8 + 9) * (2 - 3))"
        //"(((32 * 17) + (9 - 11) / 2) >= (49 * 3 / (6 + 2)) && (99 <= 100)) || ((12 * 2 - 45 / 5) != (8 + 9) * (2 - 3))",
        //"(((65 / 3) > (10 * 2)) && (45 <= (25 + 20)) || (7 != (7 + 1))) && (16 == (8 * 2)) || ((99 != 100) && (100 < 101))",
        //"(((45 > 67) && (23 != 24)) || (56 >= 12)) && ((5 * (9 / 3)) <= (4 * 2) + (7 / 2)) || ((15 + 19) > (6 * 4))",
        //"(((100 - 45 + 30) * (50 / 5)) >= (67 + 33) && (89 > 12)) || ((56 <= 78) && ((90 - 30) / 3 == 20))",
        //"(((15 + 10 * 2) - (30 / 3)) * ((5 + 6) / (2 + 1)) - ((20 - 7) * 3)) || ((50 > 10) && (60 <= 80) && (90 >= 70))",
        //"((99 * 34 - 67 + (45 / 15)) * ((77 >= 44) && (30 < 60)) || (200 / 25 - (5 * 6)) && ((3 + 3) != (2 * 3)))",
        //"(((100 - 5 * (4 + 6) / 2) > ((99 + 1) * 2)) || ((50 <= 100) && (35 != (45 / 3)))) || ((200 + 50) >= (100 * 3))",
        //"(((45 != 67) || (23 < 24)) && (100 >= 99)) || (((5 + 7) * 9) == (40 / 5) && ((45 > 12) || (88 <= 88)))",
        //"(((25 * 2 - 10 + 45 / 3) == (67 - 3 * 5)) && ((90 >= 45) || (50 < 60))) && (34 != (2 + 1 * 2))",
        //"((((67 + 89) / (34 - 12)) * (45 + 5)) >= ((100 / 2) - (5 * 6))) || ((30 <= 40) && (9 + 7 != (4 * 4)))"
    };
    for (const auto& it : test_strs) {
        Scanner scanner(it);
        Vector<Token> tokens = scanner.ScanTokens();
        parser p(tokens);
        p.beginParse();
        ast aT;
        //#if ENABLE_TREE_DEBUGGING
            //p.printNodes();
        //#else

        //#endif

    }
    return 0;
}
