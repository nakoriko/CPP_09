/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:36:19 by nakoriko          #+#    #+#             */
/*   Updated: 2026/03/01 17:40:02 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stdexcept>
#include <iostream>

RPN::RPN() {}
RPN::RPN(const RPN &other) : _stack(other._stack) {}
RPN &RPN::operator=(const RPN &other) {
    if (this != &other) 
        _stack = other._stack;
    return *this;
}
RPN::~RPN() {}


bool RPN::isOperator(char c) const {
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}


void RPN::calc(const std::string &input) {
    for (std::size_t i = 0; i < input.size(); i++) {
        char c = input[i];
        if (c == ' ')
            continue;
        if (std::isdigit(c))
            _stack.push(c - '0');
        else if(isOperator(c))
            applyOperator(c);
        else
            throw std::runtime_error("Error: invalid token");
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Error: invalid expression");
    std::cout << _stack.top() << std::endl;
    _stack.pop();
}

void RPN::applyOperator(char c) {
    if (_stack.size() < 2)
        throw std::runtime_error("Error: not enough operands");
    int b = _stack.top();
    _stack.pop();
    int a = _stack.top();
    _stack.pop();
    if (c == '+')
        _stack.push(a + b);
    else if (c == '-')
        _stack.push(a - b);
    else if (c == '*')
        _stack.push(a * b);
    else {
        if (b == 0)
            throw std::runtime_error("Error: division by 0");
        _stack.push(a / b);
    }
}


