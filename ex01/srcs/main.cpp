#include <iostream>
#include <fstream>
#include <map>
#include <exception>
#include <sstream>
#include <stack>

int	stod(std::string s) {
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

int	main(int argc, char **argv) {
	std::stack<int> stack;
	int				front;
	int				back;

	for (int i = 0; i < argc; i++) {
		if (std::isdigit(argv[i][0]))
			stack.push(stod(argv[i]));
		else if (isoperator(argv[i][0]))
		{
			back = stack.top();
			stack.pop();
			front = stack.top();
			stack.pop();
			stack.push(calculate(front, back, argv[i][0]));
		}
	}
	std::cout << stack.top() << std::endl;
}