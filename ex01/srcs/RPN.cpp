#include "RPN.hpp"

int	atoi(const std::string &s) {
	std::stringstream ss(s);
	int	i = 0;
	ss >> i;
	return (i);
}

int	isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

Result<int>	calculate(int front, int back, char ope) {
	if (ope == '+')
		return (front + back);
	else if (ope == '-')
		return (front - back);
	else if (ope == '*')
		return (front * back);
	else if (ope == '/')
	{
		if (back == 0)
			return false;
		return (front / back);
	}
	return 0;
}

Result<std::queue<std::string> >	tokenize(const std::string& str) {
    std::queue<std::string> tokens;
    std::string			    token;
    std::istringstream	    tokenStream(str);
	int						numOfNumberStackContain = 0;

    while (std::getline(tokenStream, token, ' ')) {
		if (token.size() != 1)
			return false;
		else if (isOperator(token[0]))
		{
			if (numOfNumberStackContain < 2)
				return false;
			else
				numOfNumberStackContain--;
		}
		else if (std::isdigit(token[0]))
			numOfNumberStackContain++;
		else
			return Result<std::queue<std::string> >(false);
		tokens.push(token);
    }
	if (numOfNumberStackContain != 1)
		return Result<std::queue<std::string> >(false);
	return Result<std::queue<std::string> >(true, tokens);
}

Result<int> evaluateRPN(std::queue<std::string> tokens) {
	int				front;
	int				back;

    std::stack<int> stack;
	std::string token;
    while (tokens.size()) {
		token = tokens.front();
		if (std::isdigit(token[0]))
			stack.push(atoi(token));
		else if (isOperator(token[0]))
		{
			back = stack.top();
			stack.pop();
			front = stack.top();
			stack.pop();
			Result<int> result = calculate(front, back, token[0]);
			if (!result.isOk())
				return Result<int>(false, ERROR);
			stack.push(result.getResult());
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