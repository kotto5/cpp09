#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include <stack>
#include <fstream>
#include <exception>

#define ERROR 0

template <typename T>
class Result
{
private:
	bool        _ok;
	const T	    _result;

	Result();
    Result &operator=(const Result &other);
public:
	Result(bool ok, T result = T()) : _ok(ok), _result(result) {}
	Result(const Result &other) : _ok(other._ok), _result(other._result) {}
	~Result() {};
    bool    isOk() const { return _ok; }
    // must be called only if isOk() == true
    const T &getResult() { return _result; }
};

class RPN
{
private:
    RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();
	static int								atoi(const std::string &s);
	static int								isOperator(char c);
	static Result<int>						calculate(int front, int back, char ope);
	static Result<std::queue<std::string> >	tokenize(const std::string& str);
	static Result<int>						evaluateRPN(std::queue<std::string> tokens);
public:
    static Result<int>	evaluate(std::string str);
};

#endif