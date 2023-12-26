// #include <vector>
// #include <iostream>

// void    putVector(std::vector<int> v, std::string msg) {
//     std::cout << msg << std::endl;
//     for (size_t i = 0; i < v.size(); i++) {
//         std::cout << v[i] << " ";
//     }
//     std::cout << std::endl;    
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