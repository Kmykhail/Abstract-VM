//
// Created by Kostiantyn MYKHAILENKO on 7/28/18.
//


/*
 *  _map_err[0] = "Error";
    _map_err[1] = "Norm";
    _map_err[2] = "Norman look Cool today";


    for (std::map<int, std::string>::iterator it = _map_err.begin(); it != _map_err.end() ; it++) {
        std::size_t found = it->second.find("Cool");
        if (found != std::string::npos)
            std::cout << it->first << "=>" << it->second << std::endl;
    }
    */

/*
push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
push int32(42)
dump
pop
assert double(42.42)
exit*/

#include "AbstractVM.hpp"

AbstractVM::AbstractVM() : _filed_num(0){
    std::cout << "::::" << INT8_MAX << INT8_MIN << std::endl;
    _vec_class = new Virtual_Machine;
    readCommand();
}

AbstractVM::~AbstractVM() { }

void    AbstractVM::readCommand() {
    int check = 0;
    std::string buff;
    std::cout << "Enter: "<< std::endl;
    for (int i = 0; std::getline(std::cin, buff) && std::cin; i++){
        _filed_num++;
        check = checkValid(buff);
        if (check < 0 || check == 1)
            _lex_map[i] = (check < 0) ? ("Error: Lexical error") : ("Comment");
        else
            _lex_map[i] = "Norm command";
    }
}

int AbstractVM::checkValid(std::string line) {
    std::cmatch result;
    std::cmatch buff;
    std::regex rule("(^[ \\t]*?push [ \\t]*?((?=int8|int16|int32)int[0-9]{1,2})\\([-]*?[0-9]+\\)[ \\t]*?((?=[\\;]).*|$)"
                            "|^[ \\t]*?push [ \\t]*?((?=double)|double|float)\\([-]*?[0-9]*[.]?[0-9]+\\)[ \\t]*?((?=[\\;]).*|$)"
                            "|(^[ \\t]*?assert [ \\t]*?((?=int8|int16|int32)int[0-9]{1,2}\\([-]*?[0-9]+\\)|float\\([-]*?[0-9]*[.]?[0-9]+\\)|double\\([-]*?[0-9]*[.]?[0-9]+\\))[ \\t]*?((?=[\\;]).*|$))"
                            "|(^[ \\t]*?((?=add|sub|mul|div|mod|pop)[a-z]{3}|print|exit)[ \\t]*?((?=[\\;]).*|$))"
                            "|(^[ \\t]*?;((?=[\\;]);$|.*)))");
    std::string nameFunc[11] = {"push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit"};
    if (!std::regex_match(line.c_str(), result, rule))
        return -1;
    if (std::regex_match(line.c_str(), buff, std::regex("^;(?!;).*")))
        return 1;
    void    (AbstractVM::*arrFunc[11])(std::string) = {
        &AbstractVM::push, &AbstractVM::pop, &AbstractVM::dump, &AbstractVM::assert, &AbstractVM::add, &AbstractVM::sub,
        &AbstractVM::mul, &AbstractVM::div, &AbstractVM::mod, &AbstractVM::print, &AbstractVM::exit
    };
    for (int i = 0; i < 11; ++i)
        if (result.str().find(nameFunc[i]) != std::string::npos)
            (this->*arrFunc[i])(result.str());
    return 0;
}

void AbstractVM::push(std::string str) {
    std::smatch sm;
    std::regex rule("[\\(][-]*?[0-9]*[.]?[0-9]+");
    std::regex_search(str, sm, rule);
    double sz = std::stod(sm.str().c_str() + 1);
    std::cout << "!push" << std::endl;
    if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?int8")))
        _vec_class->setVector(new Operand<int8_t >(sz, Int8, "0"));
    else if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?int16")))
        _vec_class->setVector(new Operand<int16_t >(sz, Int16, "0"));
    else if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?int32")))
        _vec_class->setVector(new Operand<int32_t >(sz, Int32, "0"));
    else if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?((?=float)float|double)")))
    {
        int prec = 0;
        std::string slen = std::to_string(sz);
        for (size_t i = 0; i != slen.size() ; ++i)
            prec += (slen[i] == '.' || prec > 0) ? 1 : 0;
        if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?float")))
            _vec_class->setVector(new Operand<float>(sz, Float, std::to_string(prec)));
        else
            _vec_class->setVector(new Operand<double>(sz, Double, std::to_string(prec)));
    }

}

void AbstractVM::dump(std::string str) {std::cout << "!dump" << std::endl;}
void AbstractVM::pop(std::string str) {std::cout << "!pop" << std::endl;}
void AbstractVM::assert(std::string str) {std::cout << "!assert" << std::endl;}
void AbstractVM::add(std::string str) {std::cout << "!add" << std::endl;}
void AbstractVM::sub(std::string str) {std::cout << "!sub" << std::endl;}
void AbstractVM::mul(std::string str) {std::cout << "!mul" << std::endl;}
void AbstractVM::div(std::string str) {std::cout << "!div" << std::endl;}
void AbstractVM::mod(std::string str) {std::cout << "!mod" << std::endl;}
void AbstractVM::print(std::string str) {std::cout << "!print" << std::endl;}
void AbstractVM::exit(std::string str) {std::cout << "!exit" << std::endl;}

AbstractVM::Overflow::Overflow() {}
AbstractVM::Overflow::Overflow(std::string str) :_str_type(str){}
AbstractVM::Overflow::~Overflow() throw(){}
AbstractVM::Overflow::Overflow(Overflow const &cpy) { *this = cpy; }
AbstractVM::Overflow & AbstractVM::Overflow::operator=(Overflow const &rhs) {
    (void)rhs;
    return *this;
}
const char* AbstractVM::Overflow::what() const throw() {
    return "some Overflow";
}

