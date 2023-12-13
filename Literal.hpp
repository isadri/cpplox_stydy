#pragma once

#ifndef __LITERAL_HPP__
#define __LITERAL_HPP__

#include "Expr.hpp"

template<typename T>
class   Literal : public Expr<T> {
public:
    Literal(T value);
    virtual ~Literal();

    virtual T   accept(typename Expr<T>::Vistor& visitor);

    T&  getValue() const;

private:
    T   _value;
};

template<typename T>
Literal<T>::Literal(T value) : _value(value) {}

template<typename T>
Literal<T>::~Literal() {}

template<typename T>
T   Literal<T>::accept(typename Expr<T>::Vistor& visitor) {
    return visitor.visitLiteralExpr(*this);
}

template<typename T>
T&  Literal<T>::getValue() const { return _value; }

#endif