#include <vector>
#include <iostream>
#include "PmergeMe.hpp"


void    putVector2(std::vector<t_ui> v, std::string msg) {
    std::cout << msg << std::endl;
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;    
}

bool    isSorted(std::vector<t_ui> v) {
    for (t_ui i = 0; i < v.size() - 1; i++)
    {
        if (v[i] > v[i + 1])
            return false;
    }
    return true;
}

// int testGetInsertItr() {
//     t_ui max = 100;
//     std::vector<std::pair<t_ui, t_ui> > v;
//     for (t_ui i = 0; i < max; i += 8)
//         v.push_back(std::make_pair(i, 0U));
//     for (t_ui i = 1; i < max - 8; i += 4)
//     {
//         std::vector<std::pair<t_ui, t_ui> >::iterator itr;
//         itr = PmergeMe::getInsertItrRec(i, v.begin(), v.end());
//         std::cout << "itr: " << (*itr).first << "insert: " << i << "  ";
//         if ((*itr).first == i + 1)
//         {
//             std::cout << GREEN << "OK!" << RESET << std::endl;
//         }
//         else
//         {
//             std::cout << RED << "NO!" << RESET << std::endl;
//             // std::cout << "KO itr: " << (*(itr - 1)).first << std::endl;
//         }
//         v.insert(itr, std::make_pair(i, 0));
//         // if ((*itr).first = i + 1 && *itr).first = i + 1)
//     }

//     std::vector<t_ui> ret;
//     for (std::vector<std::pair<t_ui, t_ui> >::iterator itr = v.begin(); itr != v.end(); itr++)
//         ret.push_back((*itr).first);
//     if (isSorted(ret))
//         std::cout << "SUCESS!!" << std::endl;
//     else
//         std::cout << "KO!!" << std::endl;

//     putVector2(ret, "FINISH ! ");
//     return 0;
// }

// int main() {
//     std::vector<int> v;
//     v.push_back(1);
//     v.push_back(2);
//     std::vector<int>::iterator itr = v.begin();
//     std::cout << "*itr: " << *itr << std::endl;
//     putVector(v, "before: ");
//     v.insert(itr, 0);

//     std::cout << "*itr: " << *itr << std::endl;
//     putVector(v, "after: ");
//     return 0;   
// }

