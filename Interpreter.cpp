//#include "Interpreter.hpp"

//std::string Interpreter::visitLiteralExpr(Literal& expr) {
//    return expr.getValue();
//}

//std::string Interpreter::visitGroupingExpr(Grouping& expr) {
//    return evaluate(expr.getExpr());
//}

//double Interpreter::visitUnaryExpr(Unary& expr) {
//    std::string right = evaluate(expr.getRight());

//    switch (expr.getOpt().getType()) {
//        case MINUS:
//            return -(std::stof(right));
//    }
//}

//std::string Interpreter::evaluate(Expr& expr) {
//    return expr.accept(*this);
//}
