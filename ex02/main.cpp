/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:38:37 by nakoriko          #+#    #+#             */
/*   Updated: 2026/03/06 13:22:34 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>


int main (int ac, char **av) {
    if (ac < 2) {
        std::cerr << "Error: not enough arguments";
        return 1;
    }

    PmergeMe pmerge;
    try {
        pmerge.parse(ac, av);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    pmerge.run();
    return 0;
}