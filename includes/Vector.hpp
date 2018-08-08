//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#ifndef AVM_A_VM_HPP
#define AVM_A_VM_HPP

#include "Operand.hpp"

class My_Vector {
public:
    My_Vector();
    ~My_Vector();
    My_Vector(My_Vector const & rhs);
    My_Vector & operator=(My_Vector const & rhs);
    std::vector<IOperand*> getVector() const;
    std::string            getLastValFromVector() const;
    eOperandType           getLastTypeOperand() const;
    void                   setVector(IOperand * op);
    void                   setVector(std::vector<IOperand*>);
    void                   popVector(size_t num);
private:
    std::vector<IOperand *> _vec;
};

#endif
