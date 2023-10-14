#include <iostream>
#include <fstream>
#include <map>
#include <exception>
#include <sstream>

#define CSV_DELIMITER ','

bool	invalidCsvLine(const std::string &line){
	std::string::size_type pos = line.find(CSV_DELIMITER);

	return (pos == std::string::npos ||
		pos != line.rfind(CSV_DELIMITER) || 
		pos == 0 ||
		pos == line.size() - 1);
}

int	testinvalidCsvLine(){
	std::string line;
	bool	except;
	// valid
	except = false;
	if (invalidCsvLine(line = "11,11") != except)
		throw std::runtime_error(line);

	// invalid
	except = true;
	if (invalidCsvLine(line = "11,") != except)
		throw std::runtime_error(line);
	if (invalidCsvLine(line = "1,1,1") != except)
		throw std::runtime_error(line);
	if (invalidCsvLine(line = ",11") != except)
		throw std::runtime_error(line);
	return (0);
}

// ABC
// BA
// AB

// validDate is 
// YYYY-MM-DD
// == has three '-' with number

enum eDate{
	Year,
	Month,
	Day
};

#include <sstream>

bool	validMonth(std::string month){
	std::stringstream ss(month);
	int i;
	ss >> i;
	return (ss.fail() == false && ss.eof() == true &&
		i >= 1 && i <= 12);
}

bool	validYear(std::string year){
	std::stringstream ss(year);
	int i;
	ss >> i;
	return (ss.fail() == false && ss.eof() == true &&
		i >= 0 && i <= 9999);
}

bool	KeyHasValidDate(std::string date){
	size_t	countLengthDate[3] = {0};
	size_t	itrDate = 0;
	size_t	i = 0;

	while (i < date.size())
	{
		if (itrDate > 2)
			return (false);
		else if (date[i] == '-')
		{
			if ((itrDate == Month && validMonth(date.substr(0, i)) == false) ||
				(itrDate == Year && validYear(date.substr(0, i)) == false))
				return (false);
			std::cout << "date : " << date << std::endl;
			date = date.substr(i + 1);
			i = 0;
			itrDate++;
			continue ;
		}
		else if (std::isdigit(date[i]))
			countLengthDate[itrDate]++;
		else
			return (false);
		i++;
	}
	std::cout << "date Foo : " << date << std::endl;
	if (date.find_first_not_of('0') >= i)
		return (false);
	std::cout << countLengthDate[0] << " " << countLengthDate[1] << " " << countLengthDate[2] << std::endl;
	return (countLengthDate[0] == 4 && countLengthDate[1] == 2 && countLengthDate[2] == 2);
}

bool    isDouble(const std::string &str)
{
    // if (str == "nan" || str == "+inf" || str == "-inf")
    //     return (true);
    std::stringstream ss(str);
    double d;
    ss >> d;
    return  (ss.fail() == false && ss.eof() == true);
}

int	main(int argc, char **argv){
	if (argc != 2){
		std::cout << "Wrong number of arguments" << std::endl;
		return (1);
	}
	(void)argv;
	std::fstream file("data.csv");
	if (!file.is_open()){
		std::cout << "this program need data.csv DataBase" << std::endl;
		return (1);
	}
	std::string line;
	std::map<std::string, std::string> data;
	std::getline(file, line);
	while (std::getline(file, line)){
		if (invalidCsvLine(line))
		{
			std::cout << "Invalid csv line" << std::endl;
			return (1);
		}
		std::string key = line.substr(0, line.find(CSV_DELIMITER));
		if (KeyHasValidDate(key) == false)
		{
			std::cout << "Invalid csv line : [" << key << "]" << std::endl;
			return (1);
		}
		if (data.find(key) != data.end())
		{
			std::cout << "Duplicate key : [" << key << "]" << std::endl;
			return (1);
		}
		std::string value = line.substr(line.find(CSV_DELIMITER) + 1);
		if (isDouble(value) == false)
		{
			std::cout << "Invalid csv line : [" << value << "]" << std::endl;
			return (1);
		}
		data[key] = value;
	}
	// for_each(data.begin(), data.end(),
	// 	DateFormat(countLengthDate[0], countLengthDate[1], countLengthDate[2]));

	// std::map<std::string, std::string> formatedData = format(data);
	// if (countLengthDate[0] < YearLength(key))
	// 	countLengthDate[0] = YearLength(key);
	// if (countLengthDate[1] < MonthLength(key))
	// 	countLengthDate[1] = MonthLength(key);
	// if (countLengthDate[2] < DayLength(key))
	// 	countLengthDate[2] = DayLength(key);


	std::cout << "=============" << std::endl;
	return 0;
}