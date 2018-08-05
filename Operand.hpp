//
// Created by Kostiantyn MYKHAILENKO on 7/27/18.
//

#ifndef AVM_OPERAND_CLASS_HPP
#define AVM_OPERAND_CLASS_HPP

#include "IOperand.hpp"
#include "Factory.hpp"

template <class T>

class Operand : public IOperand {
private:
    T _some_value;
    int _precision;
    eOperandType _type;
    mutable std::string _str;
    std::stringstream _ssObj;
public:
    Operand(){}
    Operand(T val, eOperandType type, std::string precison) {
        _type = type;
        _precision = std::stoi(precison);
        _ssObj << std:: fixed << std::setprecision(_precision) << val;
        this->toString();
        _ssObj >> _some_value;
    }
    Operand(Operand const & rhs){ *this = rhs; }
    Operand & operator=(Operand const & rhs){
        if (this != &rhs){
            _some_value = rhs._some_value;
            _str = rhs.toString();
            _precision = rhs.getPrecision();
            _type = rhs.getType();
        }
        return *this;
    }
    ~Operand(){}

    int getPrecision( void ) const { return _precision; }
    eOperandType getType(void) const { return _type; }

    IOperand const * operator+(IOperand const & rhs) const {
        Factory factory;
        double num = _some_value + std::stod(rhs.toString());
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num))\
        : factory.createOperand(_type, std::to_string(num));
        return fin;
    }
    IOperand const * operator-(IOperand const & rhs) const {
        Factory factory;
        double num = std::abs(_some_value - std::stod(rhs.toString()));
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num))\
        : factory.createOperand(_type, std::to_string(num));
        return fin;
    }
    IOperand const * operator*(IOperand const & rhs) const {
        Factory factory;
        double num = _some_value * std::stod(rhs.toString());
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num))\
        : factory.createOperand(_type, std::to_string(num));
        return fin;
    }

    IOperand const * operator/(IOperand const & rhs) const {
        Factory factory;
        double num = _some_value / std::stod(rhs.toString());
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num))\
        : factory.createOperand(_type, std::to_string(num));
        return fin;
    }
    IOperand const *operator%(IOperand const & rhs) const {
        Factory factory;
        double num = std::fmod(_some_value, std::stod(rhs.toString()));
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num))\
        : factory.createOperand(_type, std::to_string(num));
        return fin;
    }
    std::string const & toString(void) const {
        _str = _ssObj.str();
        return _str;
    }
};

#endif //AVM_OPERAND_CLASS_HPP
