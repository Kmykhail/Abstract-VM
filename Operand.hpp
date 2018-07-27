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
    Operand(Operand const & rhs){}
    Operand & operator=(Operand const & rhs){
        if (this != &rhs){

        }
        return *this;
    }
    ~Operand(){}

    /*
    IOperand const *	result_elem;
	OperandFactory		factory;
	double				result;

	result = std::stod(toString()) + std::stod(r.toString());
	if (getType() > r.getType())
		result_elem = factory.createOperand(getType(), std::to_string(result));
	else
		result_elem = factory.createOperand(r.getType(), std::to_string(result));
	return result_elem;
     */

    int getPrecision( void ) const { return _precision; }
    eOperandType getType(void) const { return _type; }
    IOperand const * operator+(IOperand const & rhs) const {
        Factory factory;
        double num = std::stod(_str) + std::stod(rhs.toString());
        IOperand const * fin = (_type <= rhs.getType()) ? factory.createOperand(rhs.getType(), std::to_string(num)) : factory.createOperand(_type, std::to_string(num));
        return fin;
    }
    IOperand const * operator-(IOperand const & rhs) const {
        return nullptr;
    }
    IOperand const * operator*(IOperand const & rhs) const {
        return nullptr;
    }

    IOperand const * operator/(IOperand const & rhs) const {
        return nullptr;
    }
    IOperand const *operator%(IOperand const & rhs) const {
        return nullptr;
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
