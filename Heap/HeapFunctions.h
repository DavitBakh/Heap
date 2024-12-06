/*
Write functions makeHeap, popHeap and pushHeap for the tests to pass.
They must behave the same way the std::make_heap, std::pop_heap and std::push_heap behave.
*/
#pragma once
#include <functional>
#include <algorithm>

size_t left(size_t index)
{
	return 2 * index + 1;
}

size_t right(size_t index)
{
	return 2 * index + 2;
}

size_t parent(size_t index)
{
	return (index - 1) / 2;
}

template <typename ItType, typename Comparator = std::less<typename ItType::value_type>>
void siftUp(ItType begin, ItType end, size_t index, Comparator compare = std::less<typename ItType::value_type>{})
{
	const ItType::value_type& val = *(begin + index);
	while (index > 0)
	{
		int parent_index = parent(index);
		if (compare(*(begin + parent_index), *(begin + index)))
			*(begin + parent_index) = *(begin + index);
		else
			break;

		index = parent_index;
	}

	*(begin + index) = val;
}

template <typename ItType, typename Comparator = std::less<typename ItType::value_type>>
void siftDown(ItType begin, ItType end, size_t index, Comparator compare = std::less<typename ItType::value_type>{})
{
	size_t size = end - begin;
	size_t maxChildInd;
	const ItType::value_type& val = *(begin + index);

	while (true)
	{
		size_t leftInd = left(index), rightInd = right(index);

		if (leftInd >= size)
			break;

		if (rightInd >= size)
			maxChildInd = leftInd;
		else
			maxChildInd = compare(*(begin + rightInd), *(begin + leftInd)) ? leftInd : rightInd;

		if (compare(*(begin + index), *(begin + maxChildInd)))
			*(begin + index) = *(begin + maxChildInd);
		else
			break;

		index = maxChildInd;
	}
	*(begin + index) = val;
}

template <typename ItType, typename Comparator = std::less<typename ItType::value_type>>
void makeHeap(ItType begin, ItType end, Comparator compare = std::less<typename ItType::value_type>{})
{
	size_t size = end - begin;
	if (!size)
		return;

	size_t currInd = parent(size - 1);

	while (true)
	{
		siftDown(begin, end, currInd, compare);

		if (currInd == 0)
			break;

		currInd--;
	}
}


template <typename ItType, typename Comparator = std::less<typename ItType::value_type>>
void popHeap(ItType begin, ItType end, Comparator compare = std::less<typename ItType::value_type>{})
{
	std::swap(*begin, *(end - 1));
	siftDown(begin, end - 1, 0, compare);
}

template <typename ItType, typename Comparator = std::less<typename ItType::value_type>>
void pushHeap(ItType begin, ItType end, Comparator compare = std::less<typename ItType::value_type>{})
{
	siftUp(begin, end, (end - begin - 1), compare);
}

