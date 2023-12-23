#include "RPN.hpp"
// int	tester(std::string &str) {
// 	std::queue<std::string>	tokens;

// 	if (!tokenize(str, tokens))
// 	{
// 		std::cout << "ERROR" << std::endl;
// 		return 1;
// 	}
// 	try {
// 		std::cout << evaluateRPN(tokens) << std::endl;
// 	}
// 	catch (std::exception &e)
// 	{
// 		std::cout << "ERROR" << std::endl;
// 		return (1);
// 	}
// 	return 0;
// }


int	main(int argc, char **argv) {
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