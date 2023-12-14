#include "AstPrinter.hpp"
#include "Binary.hpp"
#include "Grouping.hpp"
#include "Literal.hpp"
#include "Unary.hpp"

std::string AstPrinter::print(Expr& expr) {
    return expr.accept(*this);
}

std::string AstPrinter::visitBinaryExpr(Binary& expr) {
    return parenthesize(expr.getOpt().getLexeme(), expr.getLeft(),
                        expr.getRight());
}

std::string AstPrinter::visitGroupingExpr(Grouping& expr) {
    return parenthesize("group", expr.getExpr());
}

std::string AstPrinter::visitLiteralExpr(Literal& expr) {
    if (expr.getValue().empty())
        return "nil";
    return expr.getValue();
}

std::string AstPrinter::visitUnaryExpr(Unary& expr) {
    return parenthesize(expr.getOpt().getLexeme(), expr.getRight());
}

std::string AstPrinter::parenthesize(const std::string& name, Expr& left,
                                    Expr& right)
{
    std::string builder;

    builder.append("(").append(name);
    builder.append(" ").append(left.accept(*this));
    builder.append(" ").append(right.accept(*this));
    builder.append(")");
    return builder;
}

std::string AstPrinter::parenthesize(const std::string& name, Expr& expr) {
    std::string builder;

    builder.append("(").append(name);
    builder.append(" ").append(expr.accept(*this));
    builder.append(")");
    return builder;
}

std::string AstPrinter::accept(__attribute__((unused))Visitor& visitor) {
    return "";
}
