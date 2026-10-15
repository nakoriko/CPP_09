/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoriko <nakoriko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:32:45 by nakoriko          #+#    #+#             */
/*   Updated: 2026/03/06 13:15:52 by nakoriko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const std::string &dbFile) {
    loadDatabase(dbFile);
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database) {}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other)
        _database = other._database;
    return *this;
}
BitcoinExchange::~BitcoinExchange() {}


void BitcoinExchange::loadDatabase(const std::string &dbFile) {
    std::ifstream file(dbFile.c_str()); 
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open file.");
    }
    std::string line;
    std::getline(file, line);
    while(std::getline(file, line)) {
        std::istringstream iss(line); 
        std::string date;
        std::string value;
        if (std::getline(iss, date, ',') && std::getline(iss, value)) 
            _database[date] = atof(value.c_str()); 
    }
    file.close();
}

double BitcoinExchange::getRate(const std::string &date) const {
    std::map<std::string, double>::const_iterator it = _database.find(date);
    if (it != _database.end())
        return it->second; 
    it = _database.lower_bound(date); 
    if(it == _database.begin() && it->first != date)
        return 0.0;
    if(it == _database.end() || it->first != date) {  
        it--;
    }
    return it->second;
}

bool BitcoinExchange::isLeap(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}


bool BitcoinExchange::isValidDate(const std::string &date) const {
    if(date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month < 1 || month > 12 || day < 1 || day > 31) 
        return false;
    if (isLeap(year))
        daysInMonth[1] = 29;
    if (day > daysInMonth[month - 1])
        return false;
    return true;
}

bool BitcoinExchange::isValidAmount(const std::string &amount, const std::string &line) const {
    char *end;
    double val = std::strtod(amount.c_str(), &end);
    if (*end != '\0') {
        printBadInput(line);
        return false;
    }
    if (val < 0 || amount[0] == '-') {
        std::cout << "Error: not a positive number." << std::endl;
        return false;
    }
    if (val > 1000) {
        std::cout << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

std::string BitcoinExchange::trim(const std::string &str) {
    std::string::const_iterator it = str.begin();
    while(it != str.end() && std::isspace(*it))
        ++it;
    std::string::const_iterator itend = str.end();
    while(itend != it && std::isspace(*(itend -1)))
        --itend;
    return std::string(it, itend);
}

void BitcoinExchange::printBadInput(const std::string &line) const {
    std::cout << "Error: bad input => " << line <<std::endl;
}


void BitcoinExchange::processLine(const std::string &line) const {
    if (line.empty())
        return;
    std::istringstream iss(line);
    std::string date;
    std::string amount;
    if(!std::getline(iss, date, '|') || date.empty() || date[date.size() - 1] != ' ') {
        printBadInput(line);
        return;
    }
    date = trim(date);
    if(!isValidDate(date)) {
        printBadInput(line);
        return ;
    }
    if (!std::getline(iss, amount) || amount.empty() || amount[0] != ' ') {
        printBadInput(line);
        return;
    }
    amount = trim(amount);
    if(amount.empty()) {
        printBadInput(line);
        return ;
    }
    if (!isValidAmount(amount, line)) {
        return ;
    }
    double d_amount = std::atof(amount.c_str());
    double rate = getRate(date);
    std::cout << date << " => " << amount << " = " << d_amount * rate << std::endl;
}

void BitcoinExchange::processInputFile(const std::string &inputFile) const {
    std::ifstream file (inputFile.c_str());
    if (!file.is_open()) {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
        processLine(line);
    file.close();
}