#pragma once

#ifndef __UNARY_HPP__
#define __UNARY_HPP__

#include "Expr.hpp"

template<typename T>
class   Unary : public Expr<T> {
public:
    Unary(Token opt, Expr<T> right);
    virtual ~Unary();

    virtual T   accept(typename Expr<T>::Vistor& visitor);

    Token       getOpt() const;
    Expr<T>&    getRight() const;

private:
    Token   _opt;
    Expr<T>   _right;
};

template<typename T>
Unary<T>::Unary(Token opt, Expr<T> right) : _opt(opt), _right(right) {}

template<typename T>
Unary<T>::~Unary() {
    delete _right;
}

template<typename T>
T   Unary<T>::accept(typename Expr<T>::Vistor& visitor) {
    return visitor.visitUnaryExpr(*this);
}

template<typename T>
Token   Unary<T>::getOpt() const { return _opt; }

template<typename T>
Expr<T>&    Unary<T>::getRight() const { return _right; }

#endif