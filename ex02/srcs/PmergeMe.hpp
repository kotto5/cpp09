#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/time.h>
#include <deque>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

#define NONE 0

typedef unsigned int t_ui;

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

class PmergeMe
{
private:
	PmergeMe();
	PmergeMe &operator=(const PmergeMe &other);
	PmergeMe(const PmergeMe &other);
	const PmergeMe	&operator=(const PmergeMe& other) const;
public:
	static bool    isSorted(std::vector<t_ui> v);
	static bool    isSorted(std::deque<t_ui> deQue);
	static std::vector<t_ui> pMerge(std::vector<t_ui> v);
	static std::deque<t_ui> pMerge(std::deque<t_ui> deQue);
	static t_ui jacobsthal(t_ui t);
	static int pow(int x, t_ui a);
	static int debug(std::string msg);

	static std::vector<std::pair<t_ui, t_ui> >::iterator	getInsertItr
	(
		t_ui insert,
		std::vector<std::pair<t_ui, t_ui> >::iterator begin,
		std::vector<std::pair<t_ui, t_ui> >::iterator end);
	static std::deque<std::pair<t_ui, t_ui> >::iterator	getInsertItr
	(
		t_ui insert,
		std::deque<std::pair<t_ui, t_ui> >::iterator begin,
		std::deque<std::pair<t_ui, t_ui> >::iterator end);
};

#endif