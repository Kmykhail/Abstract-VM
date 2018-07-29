//
// Created by Kostiantyn MYKHAILENKO on 7/27/18.
//

#ifndef AVM_OPERAND_CLASS_HPP
#define AVM_OPERAND_CLASS_HPP

#include "IOperand.hpp"
#include "Factory.hpp"


template <class T>

class Operand : public IOperand {
public:
    Operand(){}
    Operand(T val, eOperandType type, std::string str) : _some_value(val), _type(type), _str(str){}
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
        double num = std::stod(_str) + std::stod(rhs.toString());
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num))\
        : factory.createOperand(_type, std::to_string(num));
        return fin;
    }
    IOperand const * operator-(IOperand const & rhs) const {
        Factory factory;
        double num = std::abs(std::stod(_str) - std::stod(rhs.toString()));
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num))\
        : factory.createOperand(_type, std::to_string(num));
        return fin;
    }
    IOperand const * operator*(IOperand const & rhs) const {
        Factory factory;
        double num = std::stod(_str) * std::stod(rhs.toString());
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num))\
        : factory.createOperand(_type, std::to_string(num));
        return fin;
    }

    IOperand const * operator/(IOperand const & rhs) const {
        Factory factory;
        try { // exception пока будет тут, НО потом перенести
            if (!std::stod(rhs.toString()))
                throw 0;
        }
        catch(int zero){
            std::cout << "Division by zero" << std::endl;
            return nullptr;
        }
        double num = std::stod(_str) / std::stod(rhs.toString());
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num))\
        : factory.createOperand(_type, std::to_string(num));
        return fin;
    }
    IOperand const *operator%(IOperand const & rhs) const {
        Factory factory;
        try {
            if (!std::stod(rhs.toString()))
                throw 0;
        }catch (int zero){
            std::cout << "Error modulo" << std::endl;
            return nullptr;
        }
        double num = std::fmod(std::stod(_str), std::stod(rhs.toString()));
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num))\
        : factory.createOperand(_type, std::to_string(num));
        return fin;
    }
    std::string const & toString(void) const {
        _str = std::to_string(_some_value);
        return _str;
    }
private:
    T _some_value;
    int _precision;
    eOperandType _type;
    mutable std::string _str;
};

#endif //AVM_OPERAND_CLASS_HPP
