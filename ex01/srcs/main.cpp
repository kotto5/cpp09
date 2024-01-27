#include "RPN.hpp"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

int	putResult(bool success, Result<int> result) {
	if (success)
	{
		std::cerr << GREEN;
		std::cout << "OK : ";
		result.isOk() ? std::cerr << result.getResult() : std::cerr << "ERROR";
		std::cerr << RESET << std::endl;
		return 0;
	}
	else
	{
		std::cerr << RED;
		std::cerr << "ERROR: getResult() returned: ";
		result.isOk() ? std::cerr << result.getResult() : std::cerr << "ERROR";
		std::cerr << RESET << std::endl;
		return 0;
	}
}



int	tester(std::string str, bool success, int expect = 0) {
	std::cerr << GREEN << "Testing \"" << str << "\" Expect: ";
	success ? std::cerr << expect : std::cerr << "ERROR";
	std::cerr << RESET << std::endl;

	Result<int> result = RPN::evaluate(str);
	if (result.isOk() != success || (success == true && result.getResult() != expect))
		putResult(false, result);
	else
		putResult(true, result);
	std::cout << "========================================" << std::endl;
	return 0;
}


int	main(int argc, char **argv) {
	tester("1 2 +", true, 3);
	tester("2 2 +", true, 4);
	tester("+ +", false);
	tester("1 + +", false);
	tester("0 1 /", true, 0);
	tester("1 0 /", false, 0);
	tester("1 1 1 - /", false);
	tester("1 1 1 - *", true, 0);
	tester("10 1 1 - *", false, 0);
	tester("5 6 - 1 3 * 2 + 5 2 - * - 4 5 * * 8 /", true, 0);
	tester("3 4 2 * 1 5 - / +", true, 1);
	tester("1 5 -", true, -4);
	tester("9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *", false);
	if (argc == 1)
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}
	else
	{
		Result<int> result = RPN::evaluate(argv[1]);
		if (!result.isOk())
		{
			std::cout << "TOTAL ERROR" << std::endl;
			return 1;
		}
		else
		{
			std::cout << result.getResult() << std::endl;
			return 0;
		}
	}
}