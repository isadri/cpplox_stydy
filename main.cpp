#include "Lox.hpp"
#include "AstPrinter.hpp"

[[noreturn]] void   fatal(const std::string& msg, const int& exit_status) {
    std::cerr << msg << std::endl;
    std::exit(exit_status);
}

void    f() { system("leaks cpplox"); }

int	main(int argc, char* argv[]) {
	if (argc > 2) {
		fatal(std::string("Usage") + argv[0] + "[script]", USGERR);
	}
    Lox lobj;

    if (argc == 2) {
        lobj.runFile(argv[1]);
    } else {
        lobj.runPrompt();
    }
    //f();
    std::exit(EXIT_SUCCESS);
}
