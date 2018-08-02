//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#ifndef AVM_A_VM_HPP
#define AVM_A_VM_HPP

#include "Operand.hpp"

//template<typename T_>
/*emplate <typename T>

{
private:
    typedef    std::stack<T> base;
public:
    MutantStack(void) {}
    ~MutantStack(void) {}
    MutantStack(MutantStack const & o): base(o) {}
    typedef typename base::container_type::iterator iterator;
    using		base::operator=;

    iterator	begin() { return base::c.begin(); }
    iterator	end() { return base::c.end() ; }
};*/

//template <typename T>

class Virtual_Machine {
public:
    Virtual_Machine();
    ~Virtual_Machine();
    std::vector<IOperand*> getVector() const;
    void                   setVector(IOperand *);
private:
    std::vector<IOperand *> _vec;
};

#endif //AVM_A_VM_HPP
