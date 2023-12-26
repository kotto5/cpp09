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
	static std::vector<unsigned int> pMerge1(std::vector<unsigned int> v);
	static std::vector<unsigned int> pMerge2(std::vector<unsigned int> v);
	static unsigned int jacobsthal(unsigned int t);
	static int pow(int x, unsigned int a);
	static std::vector<std::pair<unsigned int, unsigned int> >::iterator getInsertItr(std::vector<std::pair<unsigned int, unsigned int> > &pairs, unsigned int insert, unsigned int end);
};

#endif