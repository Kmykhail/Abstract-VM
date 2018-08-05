//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include "Virtual_Machine.hpp"

class AbstractVM {
private:
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
public:
    explicit AbstractVM();
    ~AbstractVM();
    int    readCommand(int ac, char* av);
    std::map<int, std::string> getMap() const;
    void                       setMap(int itr, std::string str) const;
    int                        getFiled_num() const;
    double                     StrToDouble(const std::string, const size_t);
    class Overflow_ex: public std::exception{
    private:
        std::string _str_type;
    public:
        Overflow_ex();
        Overflow_ex(std::string);
        virtual ~Overflow_ex() _NOEXCEPT;
        Overflow_ex(Overflow_ex const & cpy);
        Overflow_ex &operator=(Overflow_ex const & rhs);
    };
    class Pop_ex: public std::exception{
    public:
        Pop_ex();
        Pop_ex(AbstractVM const & rhs);
        virtual ~Pop_ex() throw();
        Pop_ex(Pop_ex const & cpy);
        Pop_ex & operator=(Pop_ex const & rhs);
    };
    class Assert_ex : public std::exception{
    public:
        Assert_ex();
        virtual ~Assert_ex() throw();
        Assert_ex(Assert_ex const & cpy);
        Assert_ex & operator=(Assert_ex const & rhs);
    };

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
