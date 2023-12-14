#include "AstPrinter.hpp"

void    AstPrinter::print(Expr& expr) {
    expr.accept(*this);
}

void    AstPrinter::visitBinaryExpr(Binary& expr) {
    parenthesize(expr.getOpt().getLexeme(), expr.getLeft(), expr.getRight());
}

void    AstPrinter::visitGroupingExpr(Grouping& expr) {
    parenthesize("group", expr.getExpr());
}

void    AstPrinter::visitLiteralExpr(Literal& expr) {
    if (expr.getValue().empty())
        std::cout << "nil";
    else
        std::cout << expr.getValue();
}

void    AstPrinter::visitUnaryExpr(Unary& expr) {
    parenthesize(expr.getOpt().getLexeme(), expr.getRight());
}

void    AstPrinter::parenthesize(const std::string& name, Expr& expr1,
                                Expr& expr2)
{
    std::cout << "(" << name;
    std::cout << " ";
    expr1.accept(*this);
    std::cout << " ";
    expr2.accept(*this);
    std::cout << ")";
}

void    AstPrinter::parenthesize(const std::string& name, Expr& expr) {
    std::cout << "(" << name << " ";
    expr.accept(*this);
    std::cout << ")";
}
