//
// Created by Kostiantyn MYKHAILENKO on 7/26/18.
//

#ifndef AVM_IOPERAND_HPP
#define AVM_IOPERAND_HPP

#include <string>
#include <iostream>

enum eOperandType {Int8, Int16, Int32, Float, Double};

class IOperand {
public:
    virtual int getPrecision( void ) const = 0;
    virtual eOperandType getType( void ) const = 0;
    virtual IOperand const * operator+(IOperand const & rhs) const = 0;
    virtual IOperand const * operator-(IOperand const & rhs) const = 0;
    virtual IOperand const * operator*(IOperand const & rhs) const = 0;
    virtual IOperand const *operator/(IOperand const & rhs) const = 0;
    virtual IOperand const * operator%(IOperand const & rhs) const = 0;
    virtual std::string const & toString(void) const = 0;
    virtual ~IOperand( void ) {}
};


#endif //AVM_IOPERAND_HPP
