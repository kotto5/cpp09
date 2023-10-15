#include <iostream>
#include <fstream>
#include <map>
#include <exception>
#include <sstream>
#include <stack>
#include <queue>

int	stod_util(const std::string &s) {
	std::stringstream ss(s);
	int	i = 0;
	ss >> i;
	return (i);
}

int	isoperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int	calculate(int front, int back, char ope) {
	if (ope == '+')
		return (front + back);
	else if (ope == '-')
		return (front - back);
	else if (ope == '*')
		return (front * back);
	else if (ope == '/')
		return (front / back);
	return 0;
}

bool	tokenize(const std::string& str, std::queue<std::string> &tokens) {
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, ' ')) {
		if (token.size() != 1 || 
			(!isoperator(token[0])&& !std::isdigit(token[0])))
			return (false);
		else
			tokens.push(token);
    }
	return (true);
}

int evaluateRPN(std::queue<std::string>& tokens) {
	int				front;
	int				back;

    std::stack<int> stack;
	std::string token;
    while (tokens.size()) {
		token = tokens.front();
		if (std::isdigit(token[0]))
			stack.push(stod_util(token));
		else if (isoperator(token[0]))
		{
			back = stack.top();
			stack.pop();
			front = stack.top();
			stack.pop();
			stack.push(calculate(front, back, token[0]));
		}
		tokens.pop();
    }
    return stack.top();
}

int	main(int argc, char **argv) {
	std::queue<std::string>	tokens;

	if (argc != 2 || !tokenize(argv[1], tokens))
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}
	std::cout << evaluateRPN(tokens) << std::endl;
	return 0;
}