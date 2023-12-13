#pragma once

#ifndef __BINARY_HPP__
#define __BINARY_HPP__

#include "Expr.hpp"

template<typename T>
class   Binary : public Expr<T> {
public:
    Binary(Expr<T> left, Token opt, Expr<T> right);
    virtual ~Binary();

    virtual T accept(typename Expr<T>::Vistor& vistor);

    Expr<T>&    getLeft() const;
    Token       getOpt() const;
    Expr<T>&    getRight() const;

private:
    Expr<T> _left;
    Token   _opt;
    Expr<T> _right;
};

template<typename T>
Binary<T>::Binary(Expr<T> left, Token opt, Expr<T> right)
    : _left(left)
    , _opt(opt)
    , _right(right)
{
}

template<typename T>
Binary<T>::~Binary() {
    delete _left;
    delete _right;
}

template<typename T>
T   Binary<T>::accept(typename Expr<T>::Vistor& vistor) {
    return vistor.visitBinaryExpr(*this);
}

template<typename T>
Expr<T>& Binary<T>::getLeft() const { return _left; }

template<typename T>
Token   Binary<T>::getOpt() const { return _opt; }

template<typename T>
Expr<T>& Binary<T>::getRight() const { return _right; }

#endif