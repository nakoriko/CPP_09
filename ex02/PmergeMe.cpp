/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:38:12 by nakoriko          #+#    #+#             */
/*   Updated: 2026/03/06 13:22:27 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <climits>
#include <exception>
#include <vector>
#include <sys/time.h>
#include <cstdlib>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq) {}
PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}
PmergeMe::~PmergeMe() {}

int PmergeMe::jacobsthal(int n) {
    if (n == 0 || n == 1)
        return n;
    int prev2 = 0;
    int prev1 = 1;
    int cur = 0;
    for (int i = 2; i <= n; i++) {
        cur = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return cur;
}

static std::vector<int> jacobsthalOrder(int n) {
    std::vector<int> order;
    int jac = 1;
    int prev = 0;
    while (prev < n) {
        int cur = PmergeMe::jacobsthal(jac + 1);
        if (cur > n)
            cur = n;
        for (int i = cur - 1; i >= prev; i--)
            order.push_back(i);
        prev = cur;
            jac++;
        // if (cur >= n)
        //     break;
    }
    return order;
}

template<typename T>
static void binaryInsert(T &chain, int val) {
    int low = 0;
    int high = chain.size();
    while (low < high) {
        int mid = (low + high) / 2;
        if (chain[mid] < val)
            low = mid + 1;
        else
            high = mid;
    }
    chain.insert(chain.begin() + low, val);
    
}

template <typename T>
static void insertJacobsthal(T &chain, T &pend) {
    if (pend.empty())
        return ;
    std::vector<int> order = jacobsthalOrder(pend.size());
        for (int i = 0; i < (int)order.size(); i++)
            binaryInsert(chain, pend[order[i]]);
}


void PmergeMe::insertVector(std::vector<int> &chain, std::vector<int> &pend) {
    insertJacobsthal(chain, pend);
}

void PmergeMe::insertDeque(std::deque<int> &chain, std::deque<int> &pend) {
    insertJacobsthal(chain, pend);
}



void PmergeMe::sortVector(std::vector<int> &vec) {
    if (vec.size() <= 1)
        return;
    bool hasOdd = vec.size() % 2 != 0;
    int odd = 0;
    if (hasOdd) {
        odd = vec.back();
        vec.pop_back();
    }
    int s = vec.size() / 2;
    std::vector<std::pair<int,int> > pairs(s);
    for (int i = 0; i < s; i++) {
        int a = vec[2 *  i];
        int b = vec[2 * i + 1];
        if (a < b) 
            std::swap(a, b);
        pairs[i] = std::make_pair(a, b);
    }

    std::vector<int> firsts(s);
    for (int i = 0; i < s; i++)
        firsts[i] = pairs[i].first;
    sortVector(firsts);

    std::vector<std::pair<int, int> > sorted_pairs(s);
    std::vector<std::pair<int, int> > temp = pairs;
    for (int i  = 0; i < s; i++) {
        for (int j = 0; j < (int)temp.size(); j++) {
            if (temp[j].first == firsts[i]) {
                sorted_pairs[i] = temp[j];
                temp.erase(temp.begin() + j);
                break;
            }
        }
    }

    std::vector<int> chain;
    std::vector <int> pend;
    chain.push_back(sorted_pairs[0].second);
    for (int i = 0; i < s; i++) 
        chain.push_back(sorted_pairs[i].first);
    for (int i = 1; i < s; i++) 
        pend.push_back(sorted_pairs[i].second);
    if (hasOdd)
        pend.push_back(odd);
    insertVector(chain, pend);
    vec = chain;
}



void PmergeMe::sortDeque(std::deque<int> &deq) {
    if (deq.size() <= 1)
        return;
    bool hasOdd = deq.size() % 2 != 0;
    int odd = 0;
    if (hasOdd) {
        odd = deq.back();
        deq.pop_back();
    }
    int s = deq.size() / 2;
    std::deque<std::pair<int,int> > pairs(s);
    for (int i = 0; i < s; i++) {
        int a = deq[2 *  i];
        int b = deq[2 * i + 1];
        if (a < b) 
            std::swap(a, b);
        pairs[i] = std::make_pair(a, b);
    }

    std::deque<int> firsts(s);
    for (int i = 0; i < s; i++)
        firsts[i] = pairs[i].first;
    sortDeque(firsts);

    std::deque<std::pair<int, int> > sorted_pairs(s);
    std::deque<std::pair<int, int> > temp = pairs;
    for (int i  = 0; i < s; i++) {
        for (int j = 0; j < static_cast<int>(temp.size()); j++) {
            if (temp[j].first == firsts[i]) {
                sorted_pairs[i] = temp[j];
                temp.erase(temp.begin() + j);
                break;
            }
        }
    }

    std::deque<int> chain;
    std::deque <int> pend;
    chain.push_back(sorted_pairs[0].second);
    for (int i = 0; i < s; i++) 
        chain.push_back(sorted_pairs[i].first);
    for (int i = 1; i < s; i++) 
        pend.push_back(sorted_pairs[i].second);
    if (hasOdd)
        pend.push_back(odd);
    insertDeque(chain, pend);
    deq = chain;
}    


void PmergeMe::parse(int ac, char **av) {
    char *end;
    for (int i = 1; i < ac; i++) {
        long val = 0;
            val = std::strtol(av[i], &end, 10);
            if (*end != '\0' || end == av[i])
                throw std::runtime_error("Error: Invalid argument"); // or throw?
            if (val <= 0)
                throw std::runtime_error("Error: positive int needs");
            if (val > INT_MAX)
                throw std::runtime_error("Error: too large number");
            _vec.push_back(static_cast<int>(val));
            _deq.push_back(static_cast<int>(val));
        }
}

void PmergeMe::run() {
    std::cout << "Before:";
    for (size_t i = 0; i < _vec.size(); i++) {
        std::cout << " " << _vec[i];
    }
    std::cout << std::endl;

    struct timeval t1;
    struct timeval t2;

    gettimeofday(&t1, NULL);
    sortVector(_vec);
    gettimeofday(&t2, NULL);
    double time_vec = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);

    gettimeofday(&t1, NULL);
    sortDeque(_deq);
    gettimeofday(&t2, NULL);
    double time_deq = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);

    std::cout << "After:";
    for (size_t i = 0; i < _vec.size(); i++) {
        std::cout << " " << _vec[i];
    }
    std::cout <<std::endl;
    std:: cout << "Time to process a range of " << _vec.size()
        << " elements with std::vector: "  << time_vec << " us" << std::endl;
    std:: cout << "Time to process a range of " << _vec.size()
        << " elements with std::deque: "  << time_deq << " us" << std::endl;

} 