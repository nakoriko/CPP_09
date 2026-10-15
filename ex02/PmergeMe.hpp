/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:38:08 by nakoriko          #+#    #+#             */
/*   Updated: 2026/03/06 13:22:32 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>


class PmergeMe {
private:
    std::vector<int> _vec; 
    std::deque<int> _deq;

    void sortVector(std::vector<int> &vec); 
    void sortDeque(std::deque<int> &deq);

    void insertVector(std::vector<int> &chain, std::vector <int> &pend); 
    void insertDeque(std::deque<int> &chain, std::deque<int> &pending);

    
    public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();
    
    void parse(int ac, char **av); 
    void run(); 
    static int jacobsthal(int n); 
};

#endif