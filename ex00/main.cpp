/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:38:19 by nakoriko          #+#    #+#             */
/*   Updated: 2026/03/01 12:42:37 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main (int ac, char **av) {
    if (ac != 2) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    try {
        BitcoinExchange btc("data.csv");
        btc.processInputFile(av[1]);
    } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            return 1;
    }
    return 0;
}