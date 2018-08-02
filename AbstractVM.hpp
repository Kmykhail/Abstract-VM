//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include "Virtual_Machine.hpp"
#define Over_int8 (str.find("int8") != std::string::npos && (sz > INT8_MAX || sz < INT8_MIN))
#define Over_int16 (str.find("int16") != std::string::npos && (sz > INT16_MAX || sz < INT16_MIN))
#define Over_int32 (str.find("int32") != std::string::npos && (sz > INT32_MAX || sz < INT32_MIN))

class AbstractVM {
private:
    int     checkValid(std::string line);
    void    push(std::string);
    void    dump(std::string);
    void    pop(std::string);
    void    assert(std::string);
    void    add(std::string);
    void    sub(std::string);
    void    mul(std::string);
    void    div(std::string);
    void    mod(std::string);
    void    print(std::string);
    void    exit(std::string);
    int               _filed_num;
    Virtual_Machine *_vec_class;
    Factory         *_factory;
    std::map<int, std::string> _lex_map;
public:
    AbstractVM();
    ~AbstractVM();
    void    readCommand();
    class Overflow: public std::exception{
    private:
        std::string _str_type;
    public:
        Overflow();
        Overflow(std::string);
        virtual ~Overflow() throw();
        Overflow(Overflow const & cpy);
        Overflow &operator=(Overflow const & rhs);
        virtual const char* what() const throw();
    };
};


#endif //AVM_ABSTRACTVM_HPP
