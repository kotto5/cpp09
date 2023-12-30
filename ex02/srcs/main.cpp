#include "PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

bool    isSorted2(std::vector<t_ui> v) {
    for (t_ui i = 0; i < v.size() - 1; i++)
    {
        if (v[i] > v[i + 1])
            return false;
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

void    putVector(std::vector<t_ui> v, std::string msg) {
    std::cout << GREEN;
    std::cout << msg << std::endl;
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

int execute(int argc, char **argv) {
    if (argc == 1) {
        return 1;
    }
    Result<std::vector<t_ui> > result = validateArgs(argv + 1);
    if (result.isOk() == false) {
        return 2;
    }
    std::vector<t_ui> v = result.getResult();
    putVector(v, "Before");

    const long              ta1 = getTimeInUsec();
    const std::vector<t_ui>  sorted1 = PmergeMe::pMerge1(v);
    const long              ta2 = getTimeInUsec();

    const long              tb1 = getTimeInUsec();
    const std::vector<t_ui>  sorted2 = PmergeMe::pMerge2(v);
    const long              tb2 = getTimeInUsec();

    if (sorted1 != sorted2) {
        std::cout << "Error: pMerge1 and pMerge2 return different results" << std::endl;
        std::cout << RED;
        putVector(sorted1, "pMerge1 After");
        putVector(sorted2, "pMerge2 After");
        std::cout << RESET;
    }
    else
        putVector(sorted1, "After");
    std::cout << GREEN << "pMerge1(vector): " << ta2 - ta1 << " u_sec" << RESET << std::endl;
    std::cout << GREEN << "pMerge2(list)  : " << tb2 - tb1 << " u_sec" << RESET << std::endl;
    return 0;
}

int runTest() {
    std::vector<t_ui> v;
    for (t_ui i = 1; i < 18; i++) {
        v.push_back(i);
        // if (i == 12 || i == 13)
        if (i == 12)
            continue;
        const std::vector<t_ui>  sorted1 = PmergeMe::pMerge1(v);
        if (isSorted2(sorted1) == false)
        {
            putVector(v, "ERROR! ");
        }
        else
            putVector(v, "SUCCESS! ");
    }
    return 0;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    std::string str = argv[1];
    if (str == "test")
        runTest();
    else
        execute(argc, argv);
}
