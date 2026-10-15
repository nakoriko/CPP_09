/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:38:24 by nakoriko          #+#    #+#             */
/*   Updated: 2026/03/01 17:24:55 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main (int ac, char **av) {
    if (ac  != 2) {
        std::cerr << "Error: not enough arguments" << std::endl;
        return 1;
    }
    try {
        RPN rpn;
        rpn.calc(av[1]);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}