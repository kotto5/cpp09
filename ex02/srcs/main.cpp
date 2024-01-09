#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int	g_count_operator = 0;

bool    isSorted2(std::vector<t_ui> v) {
    for (t_ui i = 0; i < v.size() - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            std::cout << "i: " << i << ": " << v[i];
            std::cout << "i+1: " << i+1 << ": " << v[i+1] << std::endl;
            return false;
        }
    }
    return true;
}

bool is_number(std::string str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

t_ui stoui(std::string str) {
    t_ui result;
    std::stringstream(str) >> result;
    return result;
}

Result<std::vector<t_ui> > validateArgs(char **argv) {
    std::vector<t_ui> v;
    for (t_ui i = 0; argv[i]; i++) {
        if (is_number(argv[i]) == false)
            return Result<std::vector<t_ui> >(false);
        else {
            const t_ui num = stoui(argv[i]);
            if (num <= 0)
                return Result<std::vector<t_ui> >(false);
            else
                v.push_back(num);
        }
    }
    return Result<std::vector<t_ui> >(true, v);
}

void    putVector(std::vector<t_ui> v, std::string msg = "debug: ", std::string color = GREEN) {
    std::cout << color;
    std::cout << msg << " ";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << RESET << std::endl;
}

unsigned long getTimeInUsec() {
    struct timeval  tv;
    if (gettimeofday(&tv, NULL))
        return 0;
    long ret = tv.tv_usec;
    ret += (tv.tv_sec * 1000000);
    return ret;
}

void    putResult(std::string msg, long time, int count) {
    (void)count;
    std::cout << msg << " time: " << time << " u_sec ";
    #ifdef DEBUG
    std::cout << "compare : " << count << "times";
    #endif
    std::cout << std::endl;
}

int execute(int argc, char **argv) {
    if (argc == 1) {
        return 1;
    }
    Result<std::vector<t_ui> > result = validateArgs(argv + 1);
    if (result.isOk() == false) {
        return 2;
    }
    std::vector<t_ui> v = result.getResult();
    putVector(v, "Before:");

    const long              ta1 = getTimeInUsec();
    g_count_operator = 0;
    const std::vector<t_ui>  sorted1 = PmergeMe::pMerge(v);
    int taCount = g_count_operator;
    const long              ta2 = getTimeInUsec();

    const long              tb1 = getTimeInUsec();
    g_count_operator = 0;
    std::deque<t_ui>        deQue(v.begin(), v.end());
    const std::deque<t_ui>  sorted2que = PmergeMe::pMerge(deQue);
    int tbCount = g_count_operator;
    std::vector<t_ui>       sorted2(sorted2que.begin(), sorted2que.end());
    const long              tb2 = getTimeInUsec();

    if (isSorted2(sorted1) == false)
        throw std::runtime_error("sorted1 is not sorted");
    else if (isSorted2(sorted2) == false)
        throw std::runtime_error("sorted2 is not sorted");
    else
        putVector(sorted1, "After: ");
    putResult("vector", ta2 - ta1, taCount);
    putResult("deque", tb2 - tb1, tbCount);
    return 0;
}

int sortDebugger(std::vector<t_ui> v) {
    g_count_operator = 0;

    const long              ta1 = getTimeInUsec();
    const std::vector<t_ui>  sorted1 = PmergeMe::pMerge(v);
    const long              ta2 = getTimeInUsec();

    std::cout << "============================" << std::endl;
    std::cout << "size: " << v.size() << std::endl;
    if (isSorted2(sorted1) == false)
    {
        putVector(v, "ERROR: ", RED);
        std::exit(1);
    }
    else
    {
        std::cout << GREEN << "SUCCESS" << RESET << std::endl;
    }
    std::cout << GREEN << "pMerge1(vector) time : " << ta2 - ta1 << " u_sec" << std::endl;
    std::cout << GREEN << "g_count_operator : " << g_count_operator << " times" << RESET << std::endl;
    return 0;
}

int runTest() {
    std::vector<t_ui> v;
    for (t_ui i = 1; i < 3000; i++) {
        v.push_back(i);
        v.push_back(i);
        sortDebugger(v);
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 1)
        return 1;
    std::string str = argv[1];
    if (str == "test")
        runTest();
    else
        execute(argc, argv);
    return 0;
}
