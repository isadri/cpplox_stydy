#include "Scanner.hpp"
#include <cstdlib>
#include <iostream>
#include <list>

static void	runPrompt();
static void	run(std::string& source);

int	main(int argc, __attribute__((unused))char* argv[]) {
	if (argc != 1) {
		std::cerr << "Usage: ./RPN\n";
		exit(EXIT_FAILURE);
	}
	runPrompt();
}

static void	runPrompt() {
	std::string	line;

	while (true) {
		std::cout << "> ";
		std::getline(std::cin, line);
		if (!std::cin.good())
			break;
		run(line);
	}
}

static void	run(std::string& source) {
	Scanner	scanner(source);
	std::list<Token>	tokens = scanner.scanTokens();

	for (auto token : tokens) {
		if (token.getType() != "END")
			std::cout << token.getType() << "\t:\t" << token.getLexeme() << '\n';
	}

}
