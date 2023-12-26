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

std::vector<std::pair<unsigned int, unsigned int> >::iterator	PmergeMe::getInsertItrRec
	(
		unsigned int insert,
		std::vector<std::pair<unsigned int, unsigned int> >::iterator begin,
		std::vector<std::pair<unsigned int, unsigned int> >::iterator end)
{
	const unsigned int middleIndex = (end - begin) / 2;
	if (middleIndex == 0)
	{
		return (*begin).first > insert
			? begin
			: end;
	}
	std::vector<std::pair<unsigned int, unsigned int> >::iterator	middle = begin + middleIndex;
	if ((*middle).first > insert)
		return getInsertItrRec(insert, begin, middle);
	else
		return getInsertItrRec(insert, middle, end);
}

// 入れるところの前のitrを返す
std::vector<std::pair<unsigned int, unsigned int> >::iterator	PmergeMe::getInsertItr
	(std::vector<std::pair<unsigned int, unsigned int> >	&pairs, unsigned int insert, unsigned int end)
{
	std::vector<std::pair<unsigned int, unsigned int> >::iterator	beginItr = pairs.begin();
	const unsigned int middle = end / 2;
	std::vector<std::pair<unsigned int, unsigned int> >::iterator	middleItr = beginItr + middle;
	if ((*middleItr).first > insert)
	{
		return getInsertItrRec(insert, beginItr, middleItr);
	}
	else
	{
		return getInsertItrRec(insert, beginItr, beginItr + end);
	}
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
    // sortedMainChain.insert(sortedMainChain.begin(), sortedPairs[0].second);
	sortedPairs.insert(sortedPairs.begin(), std::make_pair(sortedPairs[0].second, 0U));

    // insertion sort
    for (unsigned int k = 1 ;; k++)
    {
        const unsigned int t = jacobsthal(k);
        std::cout << "t: " << t << std::endl;
        // TODO あまりのやつ size より大きい時かな?
        (void)let;
        unsigned int start = t > sortedPairs.size() ? sortedPairs.size() : t;
        unsigned int end = jacobsthal(k - 1);
		// 今まで足した分のindex がずれてるのでずらす
		start += end;
        if (k > 1)
		    end += end;
		// value で itr は取れないみたいなので一旦index
        for (unsigned int i = start; i > end; i--)
        {
            const unsigned int						insert = sortedPairs[i].second;
			if (insert == 0)
				continue;
			std::vector<std::pair<unsigned int, unsigned int> >::iterator	insertItr
			 = getInsertItr(sortedPairs, insert, start);
            // mainChain.insert(insertItr, insert);
			sortedPairs.insert(insertItr, std::make_pair(insert, 0U));
			if (end > insertItr - sortedPairs.begin())
				end++;
        }
        if (sortedPairs.size() == v.size())
            break;
    }

    // pair のvec を first だけ抽出して返す
    std::vector<unsigned int> ret;
    for (std::vector<std::pair<unsigned int, unsigned int> >::iterator itr = sortedPairs.begin(); itr != sortedPairs.end(); itr++)
        ret.push_back((*itr).first);
    return ret;
}

std::vector<unsigned int> PmergeMe::pMerge2(std::vector<unsigned int> v) {
    return v;
}
