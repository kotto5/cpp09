#ifndef PMERGEME_HPP
# define PMERGEME_HPP

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

#endif