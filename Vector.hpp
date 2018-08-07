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
    std::vector<IOperand*> getVector() const;
    std::string            getLastValFromVector() const;
    eOperandType           getLastTypeOperand() const;
    void                   setVector(IOperand * op);
    void                   popVector(size_t num);
private:
    std::vector<IOperand *> _vec;
};

#endif
