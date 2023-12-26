#include "PmergeMe.hpp"

bool is_number(std::string str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

unsigned int stoui(std::string str) {
    unsigned int result;
    std::stringstream(str) >> result;
    return result;
}

Result<std::vector<unsigned int> > validateArgs(char **argv) {
    std::vector<unsigned int> v;
    for (unsigned int i = 0; argv[i]; i++) {
        if (is_number(argv[i]) == false)
            return Result<std::vector<unsigned int> >(false);
        else {
            const unsigned int num = stoui(argv[i]);
            if (num <= 0)
                return Result<std::vector<unsigned int> >(false);
            else
                v.push_back(num);
        }
    }
    return Result<std::vector<unsigned int> >(true, v);
}

void    putVector(std::vector<unsigned int> v, std::string msg) {
    std::cout << msg << std::endl;
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;    
}

unsigned long getTimeInUsec() {
    struct timeval  tv;
    if (gettimeofday(&tv, NULL))
        return 0;
    long ret = tv.tv_usec;
    ret += (tv.tv_sec * 1000000);
    return ret;
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        return 1;
    }
    Result<std::vector<unsigned int> > result = validateArgs(argv + 1);
    if (result.isOk() == false) {
        return 2;
    }
    std::vector<unsigned int> v = result.getResult();
    putVector(v, "Before");

    const long              ta1 = getTimeInUsec();
    const std::vector<unsigned int>  sorted1 = PmergeMe::pMerge1(v);
    const long              ta2 = getTimeInUsec();

    const long              tb1 = getTimeInUsec();
    const std::vector<unsigned int>  sorted2 = PmergeMe::pMerge2(v);
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