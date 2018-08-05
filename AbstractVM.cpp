//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//

#include "AbstractVM.hpp"

int         typeStr(std::string str){
    if (str.find("int8") != std::string::npos)
        return 0;
    else if (str.find("int16") != std::string::npos)
        return 1;
    else if (str.find("int32") != std::string::npos)
        return 2;
    else if (str.find("float") != std::string::npos)
        return 3;
    return 4;
}

AbstractVM::AbstractVM(){
    initVM();
}

void AbstractVM::initVM() {
    _vec_class = new Virtual_Machine;
    _prec = 0;
    _filed_num = 0;
    _fd = false;
    _fin = false;
}

AbstractVM::~AbstractVM() { }

int    AbstractVM::readCommand(int ac, char *av) {
    int check = 0;
    std::string buff;
    std::ifstream file;
    file.open(av);
    if (ac > 2 || (!file.is_open() && ac == 2))
        throw AbstractVM::Read_ex();
    if (ac == 1)
    {
        for (int i = 0; !_fin && std::getline(std::cin, buff); i++) {
            check = checkValid(buff);
            if (check < 0 || check == 1)
                _lex_map[_filed_num++] = (check < 0) ? ("Error: Lexical error") : ("Comment");
        }
    }
    else {
        _fd = true;
        for (int i = 0; std::getline(file, buff); ++i) {
            check = checkValid(buff);
            if (check < 0 || check == 1)
                _lex_map[_filed_num++] = (check < 0) ? ("Error: Lexical error") : ("Comment");
        }
        file.close();
    }
    for (std::map<int, std::string>::iterator it = _lex_map.begin(); it != _lex_map.end() ; it++) {
        if (it->second.find("Error") != std::string::npos || it->second.find("dump") != std::string::npos)
            std::cout << "Line:" << "[" << it->first + 1 << "] =>" << it->second << std::endl;
    }
    return 0;
}

double AbstractVM::StrToDouble(const std::string str, const size_t l) {
    std::stringstream ssobj;
    ssobj << std::fixed << std::setprecision(l) << str.c_str() + 1 << std::endl;
    double res;
    ssobj >> res;
    return res;
}

int AbstractVM::checkValid(std::string line) {
    std::cmatch result;
    std::cmatch buff;
    std::regex rule("(^[ \\t]*?push [ \\t]*?((?=int8|int16|int32)int[0-9]{1,2})\\([-]*?[0-9]+\\)[ \\t]*?((?=[\\;]).*|$)"
                            "|^[ \\t]*?push [ \\t]*?((?=double)|double|float)\\([-]*?[0-9]*[.]?[0-9]+\\)[ \\t]*?((?=[\\;]).*|$)"
                            "|(^[ \\t]*?assert [ \\t]*?((?=int8|int16|int32)int[0-9]{1,2}\\([-]*?[0-9]+\\)|float\\([-]*?[0-9]*[.]?[0-9]+\\)|double\\([-]*?[0-9]*[.]?[0-9]+\\))[ \\t]*?((?=[\\;]).*|$))"
                            "|(^[ \\t]*?((?=add|sub|mul|div|mod|pop)[a-z]{3}|print|dump|exit)[ \\t]*?((?=[\\;]).*|$))"
                            "|(^[ \\t]*?;((?=[\\;]);$|.*)))");
    std::string nameFunc[11] = {"push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit"};
    if (!std::regex_match(line.c_str(), result, rule))
        return -1;
    if (std::regex_match(line.c_str(), result, std::regex("^;;")) && !_fd) {
        _fin = true;
        return (_filed_num && _lex_map[_filed_num - 1].find("exit") != std::string::npos) ? 0 : -1;
    }
    if (std::regex_match(line.c_str(), buff, std::regex("^[ \\t]*?;.*")))
        return 1;
    void    (AbstractVM::*arrFunc[11])(std::string) = {
        &AbstractVM::push, &AbstractVM::pop, &AbstractVM::dump, &AbstractVM::assert, &AbstractVM::add, &AbstractVM::sub,
        &AbstractVM::mul, &AbstractVM::div, &AbstractVM::mod, &AbstractVM::print, &AbstractVM::exit
    };
    line = std::regex_replace(line, std::regex("[\\;].*"), "");
    for (int i = 0; i < 11; ++i)
        if (line.find(nameFunc[i]) != std::string::npos)
            (this->*arrFunc[i])(line);
    return 0;
}

std::map<int, std::string> AbstractVM::getMap() const { return _lex_map; }

void AbstractVM::setMap(int itr, std::string str) const { _lex_map[itr] = str; }

int AbstractVM::getFiled_num() const { return _filed_num; }


void AbstractVM::push(std::string str) {
    std::smatch sm;
    std::regex_search(str, sm, std::regex("[\\(][-]*?[0-9]*[.]?[0-9]+"));
    _prec = (sm.str().find('.') != std::string::npos) ? sm.str().size() - 1 - sm.str().find('.') : 0;
    double sz = StrToDouble(sm.str(), _prec);
    if (Over_int8 || Over_int16 || Over_int32 || Over_float)
        throw AbstractVM::Overflow_ex();
    std::cout << "!push" << std::endl;
    if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?int8")))
        _vec_class->setVector(new Operand<int8_t >(sz, Int8, 0));
    else if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?int16")))
        _vec_class->setVector(new Operand<int16_t >(sz, Int16, 0));
    else if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?int32")))
        _vec_class->setVector(new Operand<int32_t >(sz, Int32, 0));
    else if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?((?=float)float|double)")))
    {
        std::string slen = std::to_string(sz);
        if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?float")))
            _vec_class->setVector(new Operand<float>(sz, Float, _prec));
        else
            _vec_class->setVector(new Operand<double>(sz, Double, _prec));
    }
    _lex_map[_filed_num++] = str;
}

void AbstractVM::dump(std::string str) {
    std::cout << "!dump" << std::endl;
    //if (exception)
        //
    _lex_map[_filed_num] = str + ":";
    for (size_t i = _vec_class->getVector().size() - 1; i != SIZE_MAX ; --i)
        _lex_map[_filed_num] += "\n " + _vec_class->getVector().at(i)->toString();
    _filed_num++;
}
void AbstractVM::pop(std::string str) {
    std::cout << "!pop" << std::endl;
    if (!(_vec_class->getVector().size()))
        throw AbstractVM::Pop_ex();
    else
        _vec_class->popVector(1);
    _lex_map[_filed_num++] = str;
}

void AbstractVM::assert(std::string str) {
    std::cout << "!assert" << std::endl;
    std::smatch sm;
    int eType = typeStr(str);
    str = std::regex_replace(str, std::regex("int8|int16|int32"), "");
    std::regex_search(str, sm, std::regex("[-]*?[0-9]*[.]?[0-9]+"));
    double sz = std::stod(sm.str());
    if (Over_int8 || Over_int16 || Over_int32 || Over_float)
        throw AbstractVM::Overflow_ex();
    else if (eType != _vec_class->getLastTypeOperand() || sm.str() != _vec_class->getLastValFromVector())
        throw AbstractVM::Assert_ex();
    std::cout << "Ok" << std::endl;
    _lex_map[_filed_num++] = str + ":\n  " + _vec_class->getLastValFromVector();
}

void AbstractVM::add(std::string str) {
    std::cout << "!add" << std::endl;
    size_t ln = _vec_class->getVector().size();
    //----------------exception----------------//

    //----------------norm---------------------//
    IOperand* nw = const_cast<IOperand*>((*_vec_class->getVector()[ln - 2]) + (*_vec_class->getVector()[ln - 1]));
    _vec_class->popVector(2);
    _vec_class->setVector(nw);
    _lex_map[_filed_num++] = str;
}

void AbstractVM::sub(std::string str) {
    std::cout << "!sub" << std::endl;
    size_t ln = _vec_class->getVector().size();
    //----------------exception----------------//

    //----------------norm---------------------//
    IOperand* nw = const_cast<IOperand*>((*_vec_class->getVector()[ln - 2]) - (*_vec_class->getVector()[ln - 1]));
    _vec_class->popVector(2);
    _vec_class->setVector(nw);
    _lex_map[_filed_num++] = str;
}

void AbstractVM::mul(std::string str) {
    std::cout << "!mul" << std::endl;
    size_t ln = _vec_class->getVector().size();
    //----------------exception----------------//

    //----------------norm---------------------//
    IOperand* nw = const_cast<IOperand*>((*_vec_class->getVector()[ln - 2]) * (*_vec_class->getVector()[ln - 1]));
    _vec_class->popVector(2);
    _vec_class->setVector(nw);
    _lex_map[_filed_num++] = str;
}

void AbstractVM::div(std::string str) {
    std::cout << "!div" << std::endl;
    size_t ln = _vec_class->getVector().size();
    /*if (!std::stod(_vec_class->getLastValFromVector()) // exception on DIV ZERO
        throw SOME_EXCEPTION*/
    //----------------exception----------------//

    //----------------norm---------------------//
    IOperand* nw = const_cast<IOperand*>((*_vec_class->getVector()[ln - 2]) / (*_vec_class->getVector()[ln - 1]));
    _vec_class->popVector(2);
    _vec_class->setVector(nw);
    _lex_map[_filed_num++] = str;
}

void AbstractVM::mod(std::string str) {
    std::cout << "!mod" << std::endl;
    size_t ln = _vec_class->getVector().size();
    /*if (!std::stod(_vec_class->getLastValFromVector()) // exception on DIV ZERO
    throw SOME_EXCEPTION*/
    //----------------exception----------------//

    //----------------norm---------------------//
    IOperand* nw = const_cast<IOperand*>((*_vec_class->getVector()[ln - 2]) % (*_vec_class->getVector()[ln - 1]));
    _vec_class->popVector(2);
    _vec_class->setVector(nw);
    _lex_map[_filed_num++] = str;
}

void AbstractVM::print(std::string str) {
    std::cout << "!print" << std::endl;
    size_t ln = _vec_class->getVector().size();
    /*if (_vec_class->getLastTypeOperand() != Int8)
        throw;*/
    //----------------exception----------------//

    //----------------norm---------------------//
    _lex_map[_filed_num] = str + ":";
    for (ln -= 1; ln != SIZE_MAX && _vec_class->getVector()[ln]->getType() == Int8; --ln)
        _lex_map[_filed_num] += "\n " + _vec_class->getVector()[ln]->toString();//std::cout << _vec_class->getVector()[ln]->toString() << std::endl;
    _filed_num++;
}

void AbstractVM::exit(std::string str) {
    std::cout << "!exit" << std::endl;
    _lex_map[_filed_num++] = str;
}


//не нужен
AbstractVM::Overflow_ex::Overflow_ex() {}
AbstractVM::Overflow_ex::Overflow_ex(std::string str) :_str_type(str){}
AbstractVM::Overflow_ex::~Overflow_ex() _NOEXCEPT{}
AbstractVM::Overflow_ex::Overflow_ex(Overflow_ex const &cpy) { *this = cpy; }
AbstractVM::Overflow_ex & AbstractVM::Overflow_ex::operator=(Overflow_ex const &rhs) {
    (void)rhs;
    return *this;
}

AbstractVM::Pop_ex::Pop_ex(){}
AbstractVM::Pop_ex::Pop_ex(AbstractVM const & rhs){
    std::string err;
    err = "Line " + std::to_string(rhs.getFiled_num()) + " : Pop on empty stack";
    rhs.setMap(rhs.getFiled_num(), err);
    std::cout << "!!!!" << std::endl;
}
AbstractVM::Pop_ex::~Pop_ex() throw(){}
AbstractVM::Pop_ex::Pop_ex(Pop_ex const &cpy) { *this = cpy;}
AbstractVM::Pop_ex& AbstractVM::Pop_ex::operator=(Pop_ex const &rhs) {
    (void)rhs;
    return *this;
}

AbstractVM::Assert_ex::Assert_ex(){
    std::cout << "Pizda" << std::endl;
}

AbstractVM::Assert_ex::~Assert_ex() throw(){}
AbstractVM::Assert_ex::Assert_ex(Assert_ex const &cpy) { *this = cpy;}
AbstractVM::Assert_ex & AbstractVM::Assert_ex::operator=(Assert_ex const &rhs) {
    (void)rhs;
    return *this;
}

AbstractVM::Read_ex::Read_ex() {}
AbstractVM::Read_ex::~Read_ex() _NOEXCEPT {}
AbstractVM::Read_ex::Read_ex(Read_ex const &cpy) { *this = cpy;}
AbstractVM::Read_ex& AbstractVM::Read_ex::operator=(Read_ex const &rhs) {
    (void)rhs;
    return *this;
}

const char* AbstractVM::Read_ex::what() const throw() {
    return "Usage: [./a.out]  or [./a.out][valid file]\n";
}