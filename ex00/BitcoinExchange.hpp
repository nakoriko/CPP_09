/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:32:41 by nakoriko          #+#    #+#             */
/*   Updated: 2026/03/01 15:43:48 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, double> _database;

    void loadDatabase(const std::string &dbFile);
    double getRate(const std::string &date) const;
    bool isValidDate(const std::string &date) const;
    bool isValidAmount(const std::string &amount, const std::string &line) const;

public:
    BitcoinExchange();
    BitcoinExchange(const std::string &dbFile);
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    void processInputFile(const std::string &inputFile) const;
    void processLine(const std::string &line) const;
    void printBadInput(const std::string &line) const;

    static std::string trim(const std::string &str);
    static bool isLeap(int year);


};

#endif