//
// Created by Kostiantyn MYKHAILENKO on 7/26/18.
//

#include "Factory.hpp"
#include "Operand.hpp"

Factory::Factory() {}

Factory::~Factory() {}

Factory::Factory(Factory const &rhs) { *this = rhs; }

Factory& Factory::operator=(Factory const &rhs) {
    (void)rhs;
    return *this;
}

IOperand const* Factory::createInt8(std::string const &value) const {
    return new Operand<int8_t>(static_cast<int8_t >(std::stod(value)), Int8, 0);
}

IOperand const* Factory::createInt16(std::string const &value) const {
    return new Operand<int16_t >(static_cast<int16_t >(std::stod(value)), Int16, 0);
}

IOperand const* Factory::createInt32(std::string const &value) const {
    return new Operand<int32_t >(static_cast<int32_t >(std::stod(value)), Int32, 0);
}

IOperand const* Factory::createFloat(std::string const &value) const {
    return new Operand<float >(static_cast<float >(std::stod(value)), Float, 0);
}

IOperand const* Factory::createDouble(std::string const &value) const {
    return new Operand<double>(static_cast<double>(std::stod(value)), Double, 0);
}

IOperand const* Factory::createOperand(eOperandType type, std::string const &value) const {
    IOperand const *  (Factory::*chose[5])(std::string const &) const = {
            &Factory::createInt8,
            &Factory::createInt16,
            &Factory::createInt32,
            &Factory::createFloat,
            &Factory::createDouble
    };
    IOperand const *  give  = (this->*chose[type])(value);
    return give;
}
