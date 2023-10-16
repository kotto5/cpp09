#include "BitcoinExchange.hpp"
#include <iostream>

int	main(int argc, char **argv){
	(void)argc;
	return (!BitcoinExchange::Exchange(argv[1]));
}

// 
// struct Entry {
//     std::string date;
//     float value;
// };

// bool isValidDate(const std::string& date) {
//     std::istringstream ss(date);
//     struct tm tm;
//     char buf[255];

//     ss >> std::get_time(&tm, "%Y-%m-%d");
//     if (ss.fail()) {
//         return false;
//     }
//     std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
//     return date == buf;
// }