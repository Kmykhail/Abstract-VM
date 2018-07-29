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
    readCommand();
}

AbstractVM::~AbstractVM() { }

void    AbstractVM::readCommand() {
    std::string buff;
    std::cout << "Enter: "<< std::endl;
    while (std::getline(std::cin, buff) && std::cin){
        _filed_num++;
        checkValid(buff);
    }
}

int AbstractVM::checkValid(std::string line) {
    std::cmatch result;
    std::regex push("(^[ \\t]*?push [ \\t]*?((?=int8|int16|int32)int[0-9]{1,2})\\([-]*?[0-9]+\\)[ \\t]*?((?=[\\;]).*|$)"
                            "|^[ \\t]*?push [ \\t]*?((?=double)|double|float)\\([-]*?[0-9]*[.]?[0-9]+\\)[ \\t]*?((?=[\\;]).*|$)"
                            "|(^[ \\t]*?assert [ \\t]*?((?=int8|int16|int32)int[0-9]{1,2}\\([-]*?[0-9]+\\)|float\\([-]*?[0-9]*[.]?[0-9]+\\)|double\\([-]*?[0-9]*[.]?[0-9]+\\))[ \\t]*?((?=[\\;]).*|$))"
                            "|(^[ \\t]*?((?=add|sub|mul|div|mod|pop)[a-z]{3}|print|exit)[ \\t]*?((?=[\\;]).*|$))"
                            "|(^[ \\t]*?;((?=[\\;]);$|.*)))");
    if (std::regex_match(line.c_str(), result, push))
        std::cout << result.str() << std::endl;
    else
        std::cout << "False" << std::endl;
    return 0;
}
