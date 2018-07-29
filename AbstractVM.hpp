//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include "Virtual_Machine.hpp"

class AbstractVM {
private:
    int               _filed_num;
    Virtual_Machine *_my_arr;
    Factory         *_factory;
    std::map<int, std::string> _map_err;
public:
    AbstractVM();
    ~AbstractVM();
    void    readCommand();
    int     checkValid(std::string line);
    void    dump();
    void    assert();
    void    add();
    void    sub();
    void    mul();
    void    div();
    void    mod();
    void    printf();
};


#endif //AVM_ABSTRACTVM_HPP
