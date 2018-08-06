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
    _check = 0;
    _fd = false;
    _fin = false;
    _all = false;
}

AbstractVM::~AbstractVM() {
    delete _vec_class;
}

void AbstractVM::Ask() {
    std::string i;
    std::cout << GRN << "Enter 1 - mixed output [command + result]" <<std::endl;
    std::cout << "Enter 2 or else - you will see only result" << CL << std::endl;
    std::cin >> i;
    _all = (i == "1") ? true : _all;
    std::cin.clear();
}

int    AbstractVM::readCommand(int ac, char *av) {
    std::string buff;
    std::ifstream file;
    file.open(av);
    if (ac > 2 || (!file.is_open() && ac == 2))
        throw AbstractVM::Read_ex();
    if (ac == 1)
    {
        for (int i = 0; !_fin && std::getline(std::cin, buff); i++) {
            if (buff.empty() || std::regex_match(buff.begin(), buff.end(), std::regex("[ \t]*|\\n*")))
                continue;
            _check = checkValid(buff);
            if (_check < 0 || _check == 1)
                _lex_map[_filed_num++] = (_check < 0) ? ("Error: Lexical error") : ("Comment");
        }
    }
    else {
        _fd = true;
        for (int i = 0; std::getline(file, buff); ++i) {
            _check = checkValid(buff);
            if (_check < 0 || _check == 1)
                _lex_map[_filed_num++] = (_check < 0) ? ("Error: Lexical error") : ("Comment");
        }
        file.close();
    }
    std::cout << "-------------------" << std::endl;
    if(_lex_map.empty() && _fd)
        std::cout << "Error: Empty file" << std::endl;
    else
        Print_map();
    return 0;
}

void AbstractVM::Print_map() {
    Ask();
    for (std::map<int, std::string>::iterator it = _lex_map.begin(); it != _lex_map.end() ; it++) {
            if (it->second.find("Error") != std::string::npos)
                std::cout << RED << "Line:" << "[" << it->first + 1 << "] =>" << CL << it->second << std::endl;
            else if (std::regex_search(it->second.begin(), it->second.end(), std::regex("dump|print")))
                std::cout << GRN << "Line:" << "[" << it->first + 1 << "] =>" << CL << it->second << std::endl;
            else if (_all)
                std::cout << "Line:" << "[" << it->first + 1 << "] =>" << it->second << std::endl;
    }
}

double AbstractVM::StrToDouble(const std::string str, const size_t l) {
    std::stringstream ssobj;
    ssobj << std::fixed << std::setprecision(l) << str.c_str() + 1 << std::endl;
    double res;
    ssobj >> res;
    return res;
}

int AbstractVM::Parse_error(std::string line, std::regex rule) {
    if (Lex_error) {
        return -1;
    }
    else if (Stdin_exit){
        _fin = true;
        return (_filed_num && _lex_map[_filed_num - 1].find("exit") != std::string::npos) ? 0 : -1;
    }
    else
        return 1;
}

int AbstractVM::checkValid(std::string line) {
    std::cmatch result;
    std::regex rule("(^[ \\t]*?push [ \\t]*?((?=int8|int16|int32)int[0-9]{1,2})\\([-]*?[0-9]+\\)[ \\t]*?((?=[\\;]).*|$)"
                            "|^[ \\t]*?push [ \\t]*?((?=double)|double|float)\\([-]*?[0-9]*[.]?[0-9]+\\)[ \\t]*?((?=[\\;]).*|$)"
                            "|(^[ \\t]*?assert [ \\t]*?((?=int8|int16|int32)int[0-9]{1,2}\\([-]*?[0-9]+\\)|float\\([-]*?[0-9]*[.]?[0-9]+\\)|double\\([-]*?[0-9]*[.]?[0-9]+\\))[ \\t]*?((?=[\\;]).*|$))"
                            "|(^[ \\t]*?((?=add|sub|mul|div|mod|pop)[a-z]{3}|print|dump|exit)[ \\t]*?((?=[\\;]).*|$))"
                            "|(^[ \\t]*?;((?=[\\;]);$|.*)))");
    std::string nameFunc[11] = {"push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit"};
    if (Lex_error || Stdin_exit || Comment)
        return (Parse_error(line, rule));
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

void AbstractVM::push(std::string str) {
    std::smatch sm;
    std::regex_search(str, sm, std::regex("[\\(][-]*?[0-9]*[.]?[0-9]+"));
    _prec = (sm.str().find('.') != std::string::npos) ? sm.str().size() - 1 - sm.str().find('.') : 0;
    double sz = StrToDouble(sm.str(), _prec);
    if (Over_int8 || Over_int16 || Over_int32 || Over_float) {
        std::regex_search(str, sm, std::regex("[a-z]+[0-9]+|double|float"));
        _lex_map[_filed_num++] = "Error: Push=>[Overflow on " + sm.str() + "]";
        return;
    }
    if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?int8")))
        _vec_class->setVector(new Operand<int8_t >(sz, Int8, 0));
    else if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?int16")))
        _vec_class->setVector(new Operand<int16_t >(sz, Int16, 0));
    else if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?int32")))
        _vec_class->setVector(new Operand<int32_t >(sz, Int32, 0));
    else if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?((?=float)float|double)")))
    {
        if (std::regex_search(str, sm, std::regex("^(?!;)[ \\t]*?push[ \\t]*?float")))
            _vec_class->setVector(new Operand<float>(sz, Float, _prec));
        else
            _vec_class->setVector(new Operand<double>(sz, Double, _prec));
    }
    _lex_map[_filed_num++] = str;
}

void AbstractVM::dump(std::string str) {
    if (!_vec_class->getVector().size()) {
        _lex_map[_filed_num++] = "Error: Dump=>[Stack size is ZERO]";
        return;
    }
    _lex_map[_filed_num] = str + ":";
    for (size_t i = _vec_class->getVector().size() - 1; i != SIZE_MAX ; --i)
        _lex_map[_filed_num] += "\n " + _vec_class->getVector().at(i)->toString();
    _filed_num++;
}
void AbstractVM::pop(std::string str) {
    if (!(_vec_class->getVector().size())) {
        _lex_map[_filed_num++] = "Error: Pop=>[Stack size is ZERO]";
        return;
    }
    _vec_class->popVector(1);
    _lex_map[_filed_num++] = str;
}

void AbstractVM::assert(std::string str) {
    std::smatch sm;
    int eType = typeStr(str);
    std::regex_search(str, sm, std::regex("[\\(][-]*?[0-9]*[.]?[0-9]+"));
    double sz = std::stod(sm.str().c_str() + 1);
    if (Over_int8 || Over_int16 || Over_int32 || Over_float || !_vec_class->getVector().size()) {
        std::regex_search(str, sm, std::regex("[a-z]+[0-9]+|double|float"));
        _lex_map[_filed_num] = "Error: Assert=>[";
        _lex_map[_filed_num++] += (!_vec_class->getVector().size()) ? "Stack size is ZERO]" : ("Overflow on " + sm.str() + "]");
        return;
    }
    else if (eType != _vec_class->getLastTypeOperand() || sm.str() != _vec_class->getLastValFromVector()) {
        _lex_map[_filed_num] = "Error: Assert=>[Wrong ";
        _lex_map[_filed_num++] += (eType != _vec_class->getLastTypeOperand()) ? "type]" : "value]";
        return;
    }
    _lex_map[_filed_num++] = str + ":\n  " + _vec_class->getLastValFromVector();
}

void AbstractVM::add(std::string str) {
    size_t ln = _vec_class->getVector().size();
    if (ln < 2) {
        _lex_map[_filed_num++] = "Error: Add=>[Stack must contain at least 2 values]";
        return ;
    }
    try {
        IOperand *nw = const_cast<IOperand *>((*_vec_class->getVector()[ln - 2]) + (*_vec_class->getVector()[ln - 1]));
        _vec_class->popVector(2);
        _vec_class->setVector(nw);
        _lex_map[_filed_num++] = str;
    }
    catch(const char *text){
        _lex_map[_filed_num++] = "Error: Add=>" + std::string(text);
    }
}

void AbstractVM::sub(std::string str) {
    size_t ln = _vec_class->getVector().size();
    if (ln < 2) {
        _lex_map[_filed_num++] = "Error: Sub=>[Stack must contain at least 2 values]";
        return ;
    }
    try {
        IOperand *nw = const_cast<IOperand *>((*_vec_class->getVector()[ln - 2]) - (*_vec_class->getVector()[ln - 1]));
        _vec_class->popVector(2);
        _vec_class->setVector(nw);
        _lex_map[_filed_num++] = str;
    }
    catch(const char *text){
        _lex_map[_filed_num++] = "Error: Sub=>" + std::string(text);
    }
}

void AbstractVM::mul(std::string str) {
    size_t ln = _vec_class->getVector().size();
    if (ln < 2) {
        _lex_map[_filed_num++] = "Error: Mul=>[Stack size less than 2 values]";
        return ;
    }
    try {
        IOperand *nw = const_cast<IOperand *>((*_vec_class->getVector()[ln - 2]) * (*_vec_class->getVector()[ln - 1]));
        _vec_class->popVector(2);
        _vec_class->setVector(nw);
        _lex_map[_filed_num++] = str;
    }
    catch(const char *text){
        _lex_map[_filed_num++] = "Error: Mul=>" + std::string(text);
    }
}

void AbstractVM::div(std::string str) {
    size_t ln = _vec_class->getVector().size();
    if (ln < 2 || !std::stod(_vec_class->getLastValFromVector())){
        _lex_map[_filed_num] = "Error: Div=>[";
        _lex_map[_filed_num++] += (ln < 2) ? "Stack size less than 2 values]" : "Division by ZERO]";
        return;
    }
    try{
        IOperand* nw = const_cast<IOperand*>((*_vec_class->getVector()[ln - 2]) / (*_vec_class->getVector()[ln - 1]));
        _vec_class->popVector(2);
        _vec_class->setVector(nw);
        _lex_map[_filed_num++] = str;
    }
    catch(const char *text){
        _lex_map[_filed_num++] = "Error: Div=>" + std::string(text);
    }
}

void AbstractVM::mod(std::string str) {
    size_t ln = _vec_class->getVector().size();
    if (ln < 2 || !std::stod(_vec_class->getLastValFromVector())){
        _lex_map[_filed_num] = "Error: Mod=>[";
        _lex_map[_filed_num++] += (ln < 2) ? "Stack size less than 2 values]" : "Module by ZERO]";
        return;
    }
    try {
        IOperand *nw = const_cast<IOperand *>((*_vec_class->getVector()[ln - 2]) % (*_vec_class->getVector()[ln - 1]));
        _vec_class->popVector(2);
        _vec_class->setVector(nw);
        _lex_map[_filed_num++] = str;
    }
    catch(const char *text){
        _lex_map[_filed_num++] = "Error: Mod=>" + std::string(text);
    }
}

void AbstractVM::print(std::string str) {
    size_t ln = _vec_class->getVector().size();
    if (!ln || _vec_class->getLastTypeOperand() != Int8){
        _lex_map[_filed_num] = "Error: Print=>[";
        _lex_map[_filed_num++] += (!ln) ? "Stack size is ZERO]" : "Expects at the top of the stack 8-bit integer]";
        return;
    }
    const char *buff = _vec_class->getLastValFromVector().c_str();
    _lex_map[_filed_num] = str + ":";
    _lex_map[_filed_num++] += "\n "+ std::string(buff) + " [" + ((char)std::stod(buff)) + "]";
}

void AbstractVM::exit(std::string str) {
    _lex_map[_filed_num++] = str;
}

AbstractVM::Read_ex::Read_ex() {}
AbstractVM::Read_ex::~Read_ex() _NOEXCEPT {}
AbstractVM::Read_ex::Read_ex(Read_ex const &cpy) { *this = cpy;}
AbstractVM::Read_ex& AbstractVM::Read_ex::operator=(Read_ex const &rhs) {
    (void)rhs;
    return *this;
}

const char* AbstractVM::Read_ex::what() const throw() {
    return "Usage: [./a.out] | [./a.out][valid file] | [./a.out][valid file]\n";
}