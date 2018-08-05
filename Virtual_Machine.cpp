//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#include "Virtual_Machine.hpp"

Virtual_Machine::Virtual_Machine() { }

Virtual_Machine::~Virtual_Machine() { }

std::vector<IOperand*> Virtual_Machine::getVector() const { return _vec; }

void Virtual_Machine::setVector(IOperand * op) { _vec.push_back(op);}

void Virtual_Machine::popVector(size_t num) {
    for (size_t i = 0; i < num ; ++i)
        _vec.pop_back();
}

std::string Virtual_Machine::getLastValFromVector() const { return _vec.back()->toString();}

eOperandType Virtual_Machine::getLastTypeOperand() const { return _vec.back()->getType();}