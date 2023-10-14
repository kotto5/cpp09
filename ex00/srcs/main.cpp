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
	if (month.size() != 2)
		return (false);
	std::stringstream ss(month);
	int i;
	ss >> i;
	return (ss.fail() == false && ss.eof() == true &&
		i >= 1 && i <= 12);
}

bool	validYear(std::string year){
	if (year.size() != 4)
		return (false);
	std::stringstream ss(year);
	int i;
	ss >> i;
	return (ss.fail() == false && ss.eof() == true &&
		i >= 0 && i <= 9999);
}

bool	validDay(std::string day){
	if (day.size() != 2)
		return (false);
	std::stringstream ss(day);
	int i;
	ss >> i;
	return (ss.fail() == false && ss.eof() == true &&
		i >= 1 && i <= 31);
}

bool	validTimeStamp(std::string timestamp, eDate kind){
	if (kind == Year)
		return (validYear(timestamp));
	else if (kind == Month)
		return (validMonth(timestamp));
	else if (kind == Day)
		return (validDay(timestamp));
	return (false);
}

bool	KeyHasValidDate(std::string date){
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

bool    isDouble(const std::string &str)
{
    std::stringstream ss(str);
    double d;
    ss >> d;
    return  (ss.fail() == false && ss.eof() == true);
}

bool	lineToMap(const std::string &line, std::map<std::string, double> &data){
	if (invalidCsvLine(line))
	{
		std::cout << "Invalid csv line" << std::endl;
		return (false);
	}
	std::string key = line.substr(0, line.find(CSV_DELIMITER));
	std::string value = line.substr(line.find(CSV_DELIMITER) + 1);
	if (KeyHasValidDate(key) == false || isDouble(value) == false ||
		data.find(key) != data.end())
	{
		std::cout << "Invalid csv line" << std::endl;
		return (false);
	}
	std::stringstream ss(value);
	ss >> data[key];
	return (true);
}

bool	dataBaseToMap(std::map<std::string, double> &data){
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

int	main(int argc, char **argv){
	if (argc != 2){
		std::cout << "Wrong number of arguments" << std::endl;
		return (1);
	}
	(void)argv;
	std::map<std::string, double> data;
	if (dataBaseToMap(data) == false)
		return (1);
	return 0;
}