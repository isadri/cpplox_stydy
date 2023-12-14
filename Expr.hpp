#pragma once

#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include "common.hpp"
#include "Token.hpp"

class   Binary;
class   Grouping;
class   Literal;
class   Unary;
class   Visitor;

class   Expr {
public:
    virtual ~Expr() {}

    virtual void accept(Visitor& visitor) = 0;
};

class   Visitor {
public:
    virtual ~Visitor() {}
    virtual void    visitGroupingExpr(Grouping& expr) = 0;
    virtual void    visitBinaryExpr(Binary& expr) = 0;
    virtual void    visitLiteralExpr(Literal& expr) = 0;
    virtual void    visitUnaryExpr(Unary& expr) = 0;
};

class   Binary : public Expr {
public:
    Binary(std::shared_ptr<Expr> left, std::shared_ptr<Token> opt,
            std::shared_ptr<Expr> right);
    virtual ~Binary();

    virtual void accept(Visitor& visitor) override;

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

    virtual void accept(Visitor& visitor) override;

    Expr&   getExpr() const;

private:
    std::shared_ptr<Expr>   _expression;
};

class   Literal : public Expr {
public:
    Literal(const std::string& value);
    virtual ~Literal() {}

    virtual void accept(Visitor& visitor) override;

    const std::string&    getValue() const;

private:
    std::string _value;
};

class   Unary : public Expr {
public:
    Unary(std::shared_ptr<Token> opt, std::shared_ptr<Expr> right);
    virtual ~Unary();

    virtual void accept(Visitor& visitor) override;

    Token&  getOpt() const;
    Expr&   getRight() const;

private:
    std::shared_ptr<Token>  _opt;
    std::shared_ptr<Expr>   _right;
};

#endif