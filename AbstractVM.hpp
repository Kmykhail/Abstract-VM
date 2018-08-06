//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include "Virtual_Machine.hpp"

class AbstractVM {
private:
    void    Ask();
    int     Parse_error(std::string line, std::regex rule);
    void    Print_map();
    int     checkValid(std::string line);
    void    initVM();
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
    mutable std::map<int, std::string> _lex_map;
    int             _prec;
    bool            _fd;
    bool            _fin;
    bool            _all;
    int             _check;
public:
    explicit AbstractVM();
    ~AbstractVM();
    int                        readCommand(int ac, char* av);
    double                     StrToDouble(const std::string, const size_t);

    class Read_ex: public std::exception{
    public:
        Read_ex();
        virtual ~Read_ex() _NOEXCEPT;
        Read_ex(Read_ex const & cpy);
        Read_ex & operator=(Read_ex const & rhs);
        virtual const char* what() const throw();
    };
};


#endif //AVM_ABSTRACTVM_HPP
