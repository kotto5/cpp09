#include "BitcoinExchange.hpp"
#include <iostream>

int	main(int argc, char **argv){
	(void)argc;
	return (!BitcoinExchange::Exchange(argv[1]));
}
