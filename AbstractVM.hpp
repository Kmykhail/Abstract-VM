//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#ifndef AVM_ABSTRACTVM_HPP
#define AVM_ABSTRACTVM_HPP

#include "Virtual_Machine.hpp"
#define Over_int8 (str.find("int8") != std::string::npos && (sz > INT8_MAX || sz < INT8_MIN))
#define Over_int16 (str.find("int16") != std::string::npos && (sz > INT16_MAX || sz < INT16_MIN))
#define Over_int32 (str.find("int32") != std::string::npos && (sz > INT32_MAX || sz < INT32_MIN))
#define Over_float (str.find("float") != std::string::npos && (sz > FLT_MAX || sz < FLT_MIN))
#define Diff_val (sz != std::stod(_vec_class->getLastValFromVector()))

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
    mutable std::map<int, std::string> _lex_map;
    size_t             _prec;
public:
    AbstractVM();
    ~AbstractVM();
    void    readCommand();
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
        virtual ~Overflow_ex() throw();
        Overflow_ex(Overflow_ex const & cpy);
        Overflow_ex &operator=(Overflow_ex const & rhs);
        virtual const char* what() const throw();
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
};


#endif //AVM_ABSTRACTVM_HPP
