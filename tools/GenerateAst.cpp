#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <list>

static void	defineAst(const std::string& outputDir, const std::string& baseName,
					std::list<std::string>& types);

int	main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: generate_as <output directory>\n";
		exit(EXIT_FAILURE);
	}
	std::list<std::string>	types;

	types.insert(types.end(), "Binary		:	Expr left, Token operator, Expr right");
	types.insert(types.end(), "Grouping	:	Expr expression");
	types.insert(types.end(), "Literal	:	std::string value");
	types.insert(types.end(), "Unary		:	Token operator, Expr right");
	defineAst(argv[1], "Expr", types);
}

static void	defineAst(const std::string& outputDir, const std::string& baseName,
				std::list<std::string>& types)
{
	std::string		path(outputDir + "/" + baseName + ".hpp");
	std::ofstream	outFile(path);

	outFile << "#pragma once\n\n";
	outFile << "#include <string>\n\n";
	outFile << "class\t" << baseName << " {";

	outFile << "};";
	outFile.close();
}
