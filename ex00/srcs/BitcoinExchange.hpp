#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <string>

#define VALUE_RANGE_MIN 0
#define VALUE_RANGE_MAX 1000.0f

class BitcoinExchange
{
private:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();
public:
	static bool Exchange(const char *filename);
};

#endif