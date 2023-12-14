#include "Lox.hpp"
#include "AstPrinter.hpp"

[[noreturn]] void   fatal(const std::string& msg, const int& exit_status) {
    std::cerr << msg << std::endl;
    std::exit(exit_status);
}

int	main(int argc, char* argv[]) {
	//if (argc > 2) {
	//	fatal(std::string("Usage") + argv[0] + "[script]", USGERR);
	//}
    //Lox lobj;

    //if (argc == 2) {
    //    lobj.runFile(argv[1]);
    //} else {
    //    lobj.runPrompt();
    //}

    (void)argc;
    (void)argv;
    Expr*    expr = new Binary(
        new Unary(
            new Token(MINUS, "-", 1),
            new Literal("123")
        ),
        new Token(STAR, "*", 1),
        new Grouping(new Literal("45.57"))
    );

    AstPrinter  sp;

    std::cout << sp.print(*expr) << std::endl;

    std::exit(EXIT_SUCCESS);
}
