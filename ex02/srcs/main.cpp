#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <array>
#include <vector>
#include "PmergeMe.hpp"

bool is_number(std::string str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

int stoi(std::string str) {
    int result;
    std::stringstream(str) >> result;
    return result;
}

Result<std::vector<int> > validateArgs(char **argv) {
    std::vector<int> v;
    for (int i = 0; argv[i]; i++) {
        if (is_number(argv[i]) == false)
            return Result<std::vector<int> >(false);
        else {
            const int num = stoi(argv[i]);
            if (num <= 0)
                return Result<std::vector<int> >(false);
            else
                v.push_back(num);
        }
    }
    return Result<std::vector<int> >(true, v);
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        return 1;
    }
    Result<std::vector<int> > result = validateArgs(argv + 1);
    if (result.isOk() == false) {
        return 2;
    }
    std::vector<int> v = result.getResult();
    std::cout << "min: " << *std::min_element(v.begin(), v.end()) << std::endl;
    return 0;
}