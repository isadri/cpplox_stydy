#include "Lox.hpp"

void    Lox::runFile(const char* file) {
    std::ifstream       infile(file);
    
    if (!infile.is_open()) {
        fatal(std::string("Can't open file: ") + file, 1);
    }
    std::stringstream   buffer;
    
    buffer << infile.rdbuf();
    run(buffer.str());
}

void    Lox::runPrompt() {
    std::string line;

    std::cout << "> ";
    while (readLine(std::cin, line)) {
        run(line);
        ErrorReporter::hadError = false;
        std::cout << "> ";
    }
}

void    Lox::run(const std::string& source) {
    Scanner             scanner(source);
    std::list<Token>    tokens = scanner.scanTokens();

    for (auto token : tokens)
        std::cout << token << std::endl;
}

bool Lox::readLine(std::istream& infile, std::string& line) {
    if (!std::getline(infile, line))
        return false;
    line += '\n';
    return true;
}
