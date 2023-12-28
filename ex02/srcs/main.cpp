#include "PmergeMe.hpp"
#include "Array.hpp"

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

int testGetInsertItr();

template < typename Container >
void print( Container const & c )
{
    for ( std::size_t i = 0 ; i != c.size() ; ++i )
    {
        std::cout << c[i] ;
    }
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    // execute(argc, argv);
    // testGetInsertItr();
    Array<int, 5> array;
    array[0] = 0;
    array[1] = 1;
    array[2] = 2;
    array[3] = 3;
    array[4] = 4;

    for (Array<int, 5>::iterator itr = array.begin(),
        end = array.end(); itr < end; itr++) {
        std::cout << itr[0] << std::endl;
    }

    std::vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    for (std::vector<int>::iterator itr = v.begin(),
    end = v.end(); itr < end; itr++) {
        std::cout << itr[0] << std::endl;
    }
}
