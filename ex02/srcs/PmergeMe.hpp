#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <sys/time.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

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
	static std::vector<t_ui> pMerge1(std::vector<t_ui> v);
	static std::vector<t_ui> pMerge2(std::vector<t_ui> v);
	static t_ui jacobsthal(t_ui t);
	static int pow(int x, t_ui a);
	// static std::vector<t_ui>::iterator getInsertItr(std::vector<t_ui>&mainChain, t_ui insert, t_ui end);
	static std::vector<std::pair<t_ui, t_ui> >::iterator	getInsertItr(std::vector<std::pair<t_ui, t_ui> >	&pairs, t_ui insert, t_ui end);
	static std::vector<std::pair<t_ui, t_ui> >::iterator			getInsertItrRec
	(
		t_ui insert,
		std::vector<std::pair<t_ui, t_ui> >::iterator begin,
		std::vector<std::pair<t_ui, t_ui> >::iterator end);
};

#endif