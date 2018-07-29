//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#include "Virtual_Machine.hpp"

Virtual_Machine::Virtual_Machine() { }

Virtual_Machine::~Virtual_Machine() { }

std::vector<IOperand*> Virtual_Machine::getVector() const { return _vec; }
