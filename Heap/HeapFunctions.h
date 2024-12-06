/*
Write functions makeHeap, popHeap and pushHeap for the tests to pass.
They must behave the same way the std::make_heap, std::pop_heap and std::push_heap behave.
*/
#pragma once
#include <cstddef>

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

template <typename it>
void siftUp(it begin, it end, size_t index)
{
	const it::value_type& val = *(begin + index);
	while (index > 0)
	{
		int parent_index = parent(index);
		if (*(begin + index) > *(begin + parent_index))
			*(begin + parent_index) = *(begin + index);
		else
			break;

		index = parent_index;
	}

	*(begin + index) = val;
}

template <typename it>
void siftDown(it begin, it end, size_t index)
{
	size_t size = end - begin;
	size_t maxChildInd;
	const it::value_type& val = *(begin + index);

	while (true)
	{
		size_t leftInd = left(index), rightInd = right(index);

		if (leftInd >= size)
			break;

		if (rightInd >= size)
			maxChildInd = leftInd;
		else
			maxChildInd = *(begin + leftInd) > *(begin + rightInd) ? leftInd : rightInd;

		if (*(begin + index) < *(begin + maxChildInd))
			*(begin + index) = *(begin + maxChildInd);
		else
			break;

		index = maxChildInd;
	}
	*(begin + index) = val;
}

template <typename it>
void makeHeap(it begin, it end)
{
	size_t size = end - begin;
	if (!size)
		return;

	size_t currInd = parent(size - 1);

	while (true)
	{
		siftDown(begin, end, currInd);

		if (currInd == 0)
			break;

		currInd--;
	}
}

template <typename it>
void popHeap(it begin, it end)
{
	std::swap(*begin, *(end - 1));
	siftDown(begin, end - 1, 0);
}

template<typename it>
void pushHeap(it begin, it end)
{
	siftUp(begin, end, (end - begin - 1));
}
