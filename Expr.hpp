#pragma once

#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "common.hpp"
#include "Token.hpp"

class   Grouping;
class   Binary;
class   Literal;
class   Unary;
class   Visitor;

class   Expr {
public:
    virtual ~Expr() {}

    virtual std::string accept(Visitor& visitor) = 0;
};

class   Visitor : public Expr {
public:
    virtual ~Visitor() {}
    virtual std::string visitGroupingExpr(Grouping& expr) = 0;
    virtual std::string visitBinaryExpr(Binary& expr) = 0;
    virtual std::string visitLiteralExpr(Literal& expr) = 0;
    virtual std::string visitUnaryExpr(Unary& expr) = 0;
    virtual std::string accept(Visitor& visitor) = 0;
};

class   Binary : public Expr {
public:
    Binary(std::shared_ptr<Expr> left, std::shared_ptr<Token> opt,
            std::shared_ptr<Expr> right);
    virtual ~Binary();

    virtual std::string accept(Visitor& visitor) override;

    Expr&   getLeft() const;
    Token&  getOpt() const;
    Expr&   getRight() const;

private:
    std::shared_ptr<Expr>   _left;
    std::shared_ptr<Token>  _opt;
    std::shared_ptr<Expr>   _right;
};

class   Grouping : public Expr {
public:
    Grouping(std::shared_ptr<Expr> expression);
    virtual ~Grouping();

    virtual std::string accept(Visitor& visitor) override;

    Expr&   getExpr() const;

private:
    std::shared_ptr<Expr>   _expression;
};

class   Literal : public Expr {
public:
    Literal(const std::string& value);
    virtual ~Literal() {}

    virtual std::string accept(Visitor& visitor) override;

    const std::string&    getValue() const;

private:
    std::string _value;
};

class   Unary : public Expr {
public:
    Unary(std::shared_ptr<Token> opt, std::shared_ptr<Expr> right);
    virtual ~Unary();

    virtual std::string accept(Visitor& visitor) override;

    Token&  getOpt() const;
    Expr&   getRight() const;

private:
    std::shared_ptr<Token>  _opt;
    std::shared_ptr<Expr>   _right;
};

#endif