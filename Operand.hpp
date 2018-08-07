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
    Operand(T val, eOperandType type, int precison) {
        _type = type;
        _precision = precison;
        if (_precision > 0)
            _ssObj << std::fixed << std::setprecision(_precision) << val;
        else
            _ssObj << val;
        _ssObj >> _some_value;
        _str = _ssObj.str();
    }
    Operand(Operand const & rhs){ *this = rhs; }
    Operand & operator=(Operand const & rhs){
        if (this != &rhs){
            getDigitVal() >> _some_value;
            _str = rhs.toString();
            _precision = rhs.getPrecision();
            _type = rhs.getType();
        }
        return *this;
    }
    ~Operand(){}

    int getPrecision( void ) const { return _precision; }
    eOperandType getType(void) const { return _type; }
    std::stringstream   getDigitVal() const { return _ssObj;}

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
        if (_type == Int8)
            _str = std::to_string((int)_ssObj.str().c_str()[0]);
        return _str;
    }
};

#endif
