/*
Write functions makeHeap, popHeap and pushHeap for the tests to pass.
They must behave the same way the std::make_heap, std::pop_heap and std::push_heap behave.
*/
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
void makeHeap(it begin, it end)
{
	size_t size = end - begin;
	if (!size)
		return;

	size_t currInd = parent(size - 1);

	while (true)
	{
		size_t maxChildInd;
		size_t index = currInd;
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

		if (currInd == 0)
			break;

		currInd--;
	}
}
