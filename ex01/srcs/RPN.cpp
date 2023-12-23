#include "RPN.hpp"

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
	{
		if (back == 0)
			throw std::exception();
		return (front / back);
	}
	return 0;
}

Result<std::queue<std::string> >	tokenize(const std::string& str) {
    std::queue<std::string> tokens;
    std::string			    token;
    std::istringstream	    tokenStream(str);
	int					    acceptableOperator = -1;

    while (std::getline(tokenStream, token, ' ')) {
		if (token.size() != 1)
			return false;
		else if (isoperator(token[0]))
		{
			if (acceptableOperator < 1)
				return false;
			acceptableOperator--;
			tokens.push(token);
		}
		else if (std::isdigit(token[0]))
		{
			acceptableOperator++;
			tokens.push(token);
		}
		else
			return Result<std::queue<std::string> >(false);
    }
	if (acceptableOperator != 0)
		return Result<std::queue<std::string> >(false);
	return Result<std::queue<std::string> >(true, tokens);
}

// int evaluateRPN(const std::queue<std::string>& tokens) {
Result<int> evaluateRPN(std::queue<std::string> tokens) {
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
    return Result<int>(true, stack.top());
}

Result<int> RPN::evaluate(std::string str) {
    Result<std::queue<std::string> > tokens = tokenize(str);
    if (!tokens.isOk())
    {
        std::cout << "TOKENIZE ERROR" << std::endl;
        // return Result(false, ERROR);
        return Result<int>(false, ERROR);
    }

    Result<int> result = evaluateRPN(tokens.getResult());
    if (!result.isOk())
    {
        std::cout << "EVALUATE ERROR" << std::endl;
        return Result<int>(false, ERROR);
    }
    else
    {
        std::cout << result.getResult() << std::endl;
        return Result<int>(true, result.getResult());
    }
}