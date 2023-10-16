#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <exception>
#include <sstream>

#define CSV_DELIMITER ','

static bool	invalidCsvLine(const std::string &line){
	std::string::size_type pos = line.find(CSV_DELIMITER);

	return (pos == std::string::npos ||
		pos != line.rfind(CSV_DELIMITER) || 
		pos == 0 ||
		pos == line.size() - 1);
}

enum eDate{
	Year,
	Month,
	Day
};

static bool	validMonth(std::string month){
	if (month.size() != 2)
		return (false);
	std::stringstream ss(month);
	int i;
	ss >> i;
	return (ss.fail() == false && ss.eof() == true &&
		i >= 1 && i <= 12);
}

static bool	validYear(std::string year){
	if (year.size() != 4)
		return (false);
	std::stringstream ss(year);
	int i;
	ss >> i;
	return (ss.fail() == false && ss.eof() == true &&
		i >= 0 && i <= 9999);
}

static bool	validDay(std::string day){
	if (day.size() != 2)
		return (false);
	std::stringstream ss(day);
	int i;
	ss >> i;
	return (ss.fail() == false && ss.eof() == true &&
		i >= 1 && i <= 31);
}

static bool	validTimeStamp(std::string timestamp, eDate kind){
	if (kind == Year)
		return (validYear(timestamp));
	else if (kind == Month)
		return (validMonth(timestamp));
	else if (kind == Day)
		return (validDay(timestamp));
	return (false);
}

static bool	KeyHasValidDate(std::string date){
	eDate	itrDate = Year;
	size_t	i = 0;

	while (i < date.size())
	{
		if (date[i] == '-')
		{
			if (validTimeStamp(date.substr(0, i), itrDate) == false)
				return (false);
			date = date.substr(i + 1);
			i = 0;
			itrDate = (eDate)(itrDate + 1);
			continue ;
		}
		else if (!std::isdigit(date[i]))
			return (false);
		i++;
	}
	if (validTimeStamp(date, itrDate) == false)
		return (false);
	return (true);
}

static bool    isDouble(const std::string &str)
{
    std::stringstream ss(str);
    double d;
    ss >> d;
    return  (ss.fail() == false && ss.eof() == true);
}

static bool	lineToMap(const std::string &line, std::map<std::string, double> &data){
	if (invalidCsvLine(line))
	{
		std::cout << "Invalid csv line => " << line << std::endl;
		return (false);
	}
	std::string key = line.substr(0, line.find(CSV_DELIMITER));
	std::string value = line.substr(line.find(CSV_DELIMITER) + 1);
	if (KeyHasValidDate(key) == false || isDouble(value) == false ||
		data.find(key) != data.end())
	{
		std::cout << "Invalid csv line => " << line << std::endl;
		return (false);
	}
	std::stringstream ss(value);
	ss >> data[key];
	return (true);
}

static bool	getRateFromDB(std::map<std::string, double> &data){
	std::fstream file("data.csv");
	if (!file.is_open()){
		std::cout << "this program need data.csv DataBase" << std::endl;
		return (false);
	}
	std::string line;
	std::getline(file, line);
	if (invalidCsvLine(line))
		return (false);
	while (std::getline(file, line))
		if (lineToMap(line, data) == false)
			return (false);
	return (true);
}

static double	getNearestLowerValue(std::map<std::string, double> &data, std::string date){
	if (KeyHasValidDate(date) == false)
	{
		std::cout << "Invalid date" << std::endl;
		return (-1);
	}
	std::map<std::string, double>::iterator itr = data.lower_bound(date);
	if (itr->first == date)
		return (itr->second);
	else if (itr == data.begin())
		return (-1);
	else
	{
		itr--;
		return (itr->second);
	}
}

static bool	outputExchangeValue(std::map<std::string, double> &bitcoinRate, const std::string &fileName){
	std::ifstream file(fileName.c_str());
	if (!file.is_open()) {
		std::cout << "Error: cannot open file " << fileName << std::endl;
		return false;
	}

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream line_ss(line);
        std::string date, delimiter, value_str;
        line_ss >> date >> delimiter >> value_str;
        
        if (delimiter != "|") {
			std::cout << "bad input => " << line << std::endl;
            continue;
        }
        
        if (!KeyHasValidDate(date)) {
            std::cout << "Invalid date format: " << date << std::endl;
            continue;
        }
        float value;
        if (!isDouble(value_str)) {
            std::cout << "Invalid value: " << value_str << std::endl;
            continue;
        }
		std::stringstream ss(value_str);
		ss >> value;
		if (value < 0) {
			std::cout << "Error: not a positive number. => " << value_str << std::endl;
            continue;
		}
		if (value > 1000) {
			std::cout << "Error: too large a number => " << value_str << std::endl;
            continue;
		}

		double valueFromMap = getNearestLowerValue(bitcoinRate, date);
		if (valueFromMap < 0)
		{
			std::cout << "Error: Invalid date => " << date << std::endl;
            continue;
		}
		std::cout << date << " => " << value_str << " = " << valueFromMap * value << std::endl;
    }
	return true;
}

bool	BitcoinExchange::Exchange(const std::string &fileName){
	std::map<std::string, double> bitcoinRate;

	return (getRateFromDB(bitcoinRate) && 
		outputExchangeValue(bitcoinRate, fileName));
}
