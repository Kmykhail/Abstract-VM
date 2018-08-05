//
// Created by Kostiantyn MYKHAILENKO on 7/26/18.
//

#ifndef AVM_IOPERAND_HPP
#define AVM_IOPERAND_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <climits>
#include <cfloat>
#include <vector>
#include <stack>
#include <map>
#include <regex>

#define Over_int8 (str.find("int8") != std::string::npos && (sz > INT8_MAX || sz < INT8_MIN))
#define Over_int16 (str.find("int16") != std::string::npos && (sz > INT16_MAX || sz < INT16_MIN))
#define Over_int32 (str.find("int32") != std::string::npos && (sz > INT32_MAX || sz < INT32_MIN))
#define Over_float (str.find("float") != std::string::npos && (sz > FLT_MAX || sz < FLT_MIN))

enum eOperandType {Int8, Int16, Int32, Float, Double};

class IOperand {
public:
    virtual int getPrecision( void ) const = 0;
    virtual eOperandType getType( void ) const = 0;
    virtual IOperand const * operator+(IOperand const & rhs) const = 0;
    virtual IOperand const * operator-(IOperand const & rhs) const = 0;
    virtual IOperand const * operator*(IOperand const & rhs) const = 0;
    virtual IOperand const *operator/(IOperand const & rhs) const = 0;
    virtual IOperand const * operator%(IOperand const & rhs) const = 0;
    virtual std::string const & toString(void) const = 0;
    virtual ~IOperand( void ) {}
};

#endif //AVM_IOPERAND_HPP
