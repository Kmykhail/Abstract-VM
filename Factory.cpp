//
// Created by Kostiantyn MYKHAILENKO on 7/26/18.
//

#include "Factory.hpp"

IOperand const* Factory::createInt8(std::string const &value) const {

}

IOperand const* Factory::createOperand(eOperandType type, std::string const &value) const {
    int someType[5] = {0, 1, 2, 3, 4};
    IOperand const *  (Factory::*chose[5])(std::string const &) = {
        &Factory::createInt8,
        &Factory::createInt16,
        &Factory::createInt32,
        &Factory::createFloat,
        &Factory::createDouble
    };
    for (int i = 0; i < 5; ++i) {
        if (someType[i] == type)
            this->*chose[i](value);
    }
}