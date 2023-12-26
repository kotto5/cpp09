#include "PmergeMe.hpp"

int PmergeMe::pow(int x, unsigned int a) {
    if (a == 0)
        return 1;
    else if (a == 1)
        return x;
    else
    {
        int base = x;
        while (a-- > 1) 
            x *= base;
        return x;
    }
}

unsigned int PmergeMe::jacobsthal(unsigned int t)
{
    return (pow(2, t + 1) + pow(-1, t)) / 3;
}

// 入れるところの前のitrを返す
std::vector<std::pair<unsigned int, unsigned int> >::iterator PmergeMe::getInsertItr(std::vector<std::pair<unsigned int, unsigned int> > &pairs, unsigned int insert, unsigned int end)
{
    (void)pairs;
    (void)insert;
    (void)end;
    return pairs.begin();
}

std::vector<unsigned int> PmergeMe::pMerge1(std::vector<unsigned int> v) {
    if (v.size() == 2)
    {
        if (v[0] > v[1])
        {
            unsigned int tmp = v[0];
            v[0] = v[1];
            v[1] = tmp;
        }
        return v;
    }
    else if (v.size() == 1)
        return v;
    // make pair
    std::vector<std::pair<unsigned int, unsigned int> > pairs;
    for (size_t i = 0; i < v.size(); i += 2) {
        pairs.push_back(std::make_pair(v[i], v[i + 1]));
    }
    unsigned int let = 0;
    if (v.size() % 2 == 1) {
        let = v[v.size() - 1];
    }

    // pair sort, first is bigger
    for (size_t i = 0; i < pairs.size(); i++) {
        if (pairs[i].first < pairs[i].second) {
            unsigned int tmp = pairs[i].first;
            pairs[i].first = pairs[i].second;
            pairs[i].second = tmp;
        }
    }

    // make main chain's vector
    std::vector<unsigned int> mainChain;
    for (size_t i = 0; i < pairs.size(); i++) {
        mainChain.push_back(pairs[i].first);
    }

    // main chain sort
    std::vector<unsigned int> sortedMainChain = pMerge1(mainChain);

    // 主鎖を元にpairs をソート
    std::vector<std::pair<unsigned int, unsigned int> > sortedPairs;
    for (size_t i = 0; i < sortedMainChain.size(); i++) {
        const unsigned int findFirst = sortedMainChain[i];
        for (size_t j = 0; j < pairs.size(); j++) {
            if (findFirst == pairs[j].first) {
                sortedPairs.push_back(std::make_pair(findFirst, pairs[j].second));
            }
        }
    }
    // 最小ペアのsecond は主鎖の仲間入り
    sortedMainChain.insert(sortedMainChain.begin(), sortedPairs[0].second);

    // insertion sort
    for (unsigned int i = 1 ;; i++)
    {
        const unsigned int t = jacobsthal(i);
        std::cout << "t: " << t << std::endl;
        // TODO あまりのやつ size より大きい時かな?
        (void)let;
        const unsigned int start = t > sortedPairs.size() ? sortedPairs.size() : t;
        const unsigned int end = jacobsthal(i - 1);
        for (unsigned int j = start; j > end; j--)
        {
            const unsigned int   insert = sortedPairs[j].second;
            std::vector<std::pair<unsigned int, unsigned int> >::iterator   insertItr = getInsertItr(sortedPairs, insert, start);
            sortedPairs.insert(insertItr, std::make_pair(insert, 0));
        }
        if (t > sortedPairs.size())
            break;
    }
    return v;
}

std::vector<unsigned int> PmergeMe::pMerge2(std::vector<unsigned int> v) {
    return v;
}
