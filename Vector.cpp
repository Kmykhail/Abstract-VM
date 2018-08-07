//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#include "Vector.hpp"

My_Vector::My_Vector() { }

My_Vector::~My_Vector() { }

My_Vector::My_Vector(My_Vector const &rhs) { *this = rhs; }

My_Vector& My_Vector::operator=(My_Vector const &rhs) {
    if (this != &rhs)
        _vec = rhs.getVector();
    return *this;
}

std::vector<IOperand*> My_Vector::getVector() const { return _vec; }

void My_Vector::setVector(IOperand * op) { _vec.push_back(op);}

void My_Vector::setVector(std::vector<IOperand *> rhs) { _vec = rhs; }

void My_Vector::popVector(size_t num) {
    for (size_t i = 0; i < num ; ++i)
        _vec.pop_back();
}

std::string My_Vector::getLastValFromVector() const { return _vec.back()->toString();}

eOperandType My_Vector::getLastTypeOperand() const { return _vec.back()->getType();}