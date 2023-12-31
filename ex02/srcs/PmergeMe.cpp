#include "PmergeMe.hpp"

extern int g_count_operator;

int debug(std::string msg) {
    std::cout << msg << std::endl;
    return 0;
}

bool    isSorted3(std::vector<t_ui> v) {
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

int PmergeMe::pow(int x, t_ui a) {
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

t_ui PmergeMe::jacobsthal(t_ui t)
{
    if (t == 0)
        return 0;
    return (pow(2, t + 1) + pow(-1, t)) / 3;
}

std::vector<std::pair<t_ui, t_ui> >::iterator	getInsertItr
	(
		t_ui insert,
		std::vector<std::pair<t_ui, t_ui> >::iterator begin,
		std::vector<std::pair<t_ui, t_ui> >::iterator end)
{
	const t_ui middleIndex = (end - begin) / 2;
	if (middleIndex == 0)
	{
        if (insert <= (*begin).first)
        {
            g_count_operator++;
            return begin;
        }
        else if (insert <= (*end).first)
        {
            g_count_operator +=2;
            return end;
        }
        else
        {
            g_count_operator +=2;
            return end + 1;
        }
	}
	std::vector<std::pair<t_ui, t_ui> >::iterator	middle = begin + middleIndex;
	if ((*middle).first > insert)
	{
        g_count_operator++;
        return getInsertItr(insert, begin, middle);
    }
	else
	{
        g_count_operator++;
        return getInsertItr(insert, middle, end);
    }
}

t_ui    jacobsthal_index(t_ui k) {
    if (k == 0)
        return 0;
    else
        return PmergeMe::jacobsthal(k - 1) + PmergeMe::jacobsthal(k) - 1;
}

std::vector<t_ui> PmergeMe::pMerge1(std::vector<t_ui> vec) {
    const t_ui origin_size = vec.size();

    if (origin_size == 1)
        return vec;

    t_ui let = NONE;
    if (origin_size % 2 == 1) {
        let = vec[origin_size - 1];
        vec.pop_back();
    }

    // make pair
    // and make main chain
    std::vector<std::pair<t_ui, t_ui> > pairs;
    std::vector<t_ui> mainChain;
    for (t_ui i = 0, vec_size = vec.size(); i < vec_size; i += 2) {
        std::pair<t_ui, t_ui> pair = vec[i] > vec[i + 1]
        ? std::make_pair(vec[i], vec[i + 1])
        : std::make_pair(vec[i + 1], vec[i]);
        mainChain.push_back(pair.first);
        pairs.push_back(pair);
    }

    // main chain sort
    std::vector<t_ui> sortedMainChain = pMerge1(mainChain);
    if (isSorted3(sortedMainChain) == false)
        throw std::logic_error("sorterr");

    // 主鎖を元にpairs をソート
    for (t_ui i = 0, chainSize = sortedMainChain.size(); i < chainSize; i++) {
        const t_ui findFirst = sortedMainChain[i];
        t_ui    j = i;
        while (findFirst != pairs[j].first)
            ++j;
        std::swap(pairs[i], pairs[j]);
    }

    for (t_ui i = 0, chainSize = sortedMainChain.size(); i < chainSize; i++) {
        if (sortedMainChain[i] != pairs[i].first)
            throw std::logic_error("swap");
    }

    // 最小ペアのsecond は主鎖の仲間入り
	pairs.insert(pairs.begin(), std::make_pair(pairs[0].second, NONE));
    pairs[1].second = NONE;

    // insertion sort
    for (t_ui k = 2; pairs.size() < origin_size; k++)
    {
        t_ui start_index = jacobsthal_index(k) >= pairs.size() ?
            pairs.size() - 1: jacobsthal_index(k);
        t_ui end_index = jacobsthal_index(k - 1);

        if (end_index >= pairs.size())
            throw std::logic_error("end_index (jacobstal)");

        if (start_index == pairs.size() - 1 && let != NONE)
        {
            std::vector<std::pair<t_ui, t_ui> >::iterator begin_itr = pairs.begin();
            std::vector<std::pair<t_ui, t_ui> >::iterator	insertItr = getInsertItr(let, begin_itr, begin_itr + start_index);
			pairs.insert(insertItr, std::make_pair(let, NONE));
            start_index++;
        }
        for (t_ui i = start_index; i != end_index;)
        {
            std::vector<std::pair<t_ui, t_ui> >::iterator begin_itr = pairs.begin();
            const t_ui						insert = pairs[i].second;
			if (insert == 0) // 挿入されたものはスキップ
			{
                --i;
                continue;
            }
            std::vector<std::pair<t_ui, t_ui> >::iterator	insertItr;

            insertItr = getInsertItr(insert, begin_itr, begin_itr + i);
            if (insertItr == pairs.end())
                throw std::logic_error("ERROR: logic getInsertItr");

            pairs[i].second = NONE;
            if (end_index >= i) {
                end_index++;
            }
			pairs.insert(insertItr, std::make_pair(insert, NONE));
        }
    }
    // pair のvec を first だけ抽出して返す
    std::vector<t_ui> ret;
    for (std::vector<std::pair<t_ui, t_ui> >::iterator itr = pairs.begin(); itr != pairs.end(); itr++)
        ret.push_back((*itr).first);
    return ret;
}

std::vector<t_ui> PmergeMe::pMerge2(std::vector<t_ui> v) {
    return v;
}
