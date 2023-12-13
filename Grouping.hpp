#pragma once

#ifndef __GROUPING_HPP__
#define __GROUPING_HPP__

#include "Expr.hpp"

template<typename T>
class   Grouping : public Expr<T> {
public:
    Grouping(Expr<T>* expr);
    virtual ~Grouping();

    virtual T   accept(typename Expr<T>::Vistor& visitor);

    Expr<T>&    getExpre() const;

private:
    Expr<T>   _expr;
};

template<typename T>
Grouping<T>::Grouping(Expr<T>* expr) : _expr(expr) {}

template<typename T>
Grouping<T>::~Grouping() {
    delete _expr;
}

template<typename T>
T   Grouping<T>::accept(typename Expr<T>::Vistor& visitor) {
    return visitor.visitGroupingExpr(*this);
}

template<typename T>
Expr<T>&    Grouping<T>::getExpre() const { return _expr; }

#endif