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
    Binary(Expr* left, Token* opt, Expr* right);
    virtual ~Binary();

    virtual std::string accept(Visitor& visitor) override;

    Expr&   getLeft() const;
    Token&  getOpt() const;
    Expr&   getRight() const;

private:
    Expr*   _left;
    Token*  _opt;
    Expr*   _right;
};

class   Grouping : public Expr {
public:
    Grouping(Expr* expression);
    virtual ~Grouping();

    virtual std::string accept(Visitor& visitor) override;

    Expr&   getExpr() const;

private:
    Expr*   _expression;
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
    Unary(Token* opt, Expr* right);
    virtual ~Unary();

    virtual std::string accept(Visitor& visitor) override;

    Token&  getOpt() const;
    Expr&   getRight() const;

private:
    Token*  _opt;
    Expr*   _right;
};

#endif