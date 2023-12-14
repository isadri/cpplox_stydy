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
    Parser              parser(tokens);
    std::shared_ptr<Expr>   expression(parser.parse());

    if (ErrorReporter::hadError)
        return;
    AstPrinter  ap;
    std::cout << ap.print(*expression.get()) << std::endl;
}

bool Lox::readLine(std::istream& infile, std::string& line) {
    if (!std::getline(infile, line))
        return false;
    line += '\n';
    return true;
}

void    Lox::error(Token token, const std::string &message) {
    if (token.getType() == END) {
        ErrorReporter::report(token.getLine(), " at end", message);
    } else {
        ErrorReporter::report(token.getLine(), " at '" + token.getLexeme()
                            + "'", message);
    }
}
