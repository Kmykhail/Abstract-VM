//
// Created by Kostiantyn MYKHAILENKO on 7/26/18.
//
#ifndef AVM_FACTORY_HPP
#define AVM_FACTORY_HPP

#include "IOperand.hpp"

//class Factory;

class Factory {
public:
    Factory();
    ~Factory();
    Factory(Factory const & rhs);
    Factory &operator=(Factory const & rhs);
    IOperand const* createOperand( eOperandType type, std::string const & value) const;
private:
    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;
};


#endif //AVM_FACTORY_HPP
