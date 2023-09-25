#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <assert.h>

#define ROUNDS 10000
#define COMMON_DIVISOR (3 * 13 * 2 * 11 * 5 * 17 * 19 * 7)

enum Monkeys { MONKEY0 = 0, MONKEY1, MONKEY2, MONKEY3, MONKEY4, MONKEY5, MONKEY6, MONKEY7, };

void operation(Monkeys id, int64_t& old)
{
	switch (id)
	{
	case MONKEY0:  old *= 7;   break;
	case MONKEY1:  old += 5;   break;
	case MONKEY2:  old *= old; break;
	case MONKEY3:  old += 6;   break;
	case MONKEY4:  old *= 11;  break;
	case MONKEY5:  old += 8;   break;
	case MONKEY6:  old += 1;   break;
	case MONKEY7:  old += 4;   break;
	default: assert(false && "operation???");
	}
}

std::tuple<int64_t, int64_t> test_part1(Monkeys id, int64_t old) 
{
	old /= 3;
	switch (id)
	{
	case MONKEY0:  return std::tuple<int64_t, int64_t>(old %  3 == 0 ? MONKEY4 : MONKEY1, old);
	case MONKEY1:  return std::tuple<int64_t, int64_t>(old % 13 == 0 ? MONKEY7 : MONKEY3, old);
	case MONKEY2:  return std::tuple<int64_t, int64_t>(old %  2 == 0 ? MONKEY6 : MONKEY5, old);
	case MONKEY3:  return std::tuple<int64_t, int64_t>(old % 11 == 0 ? MONKEY2 : MONKEY6, old);
	case MONKEY4:  return std::tuple<int64_t, int64_t>(old %  5 == 0 ? MONKEY1 : MONKEY7, old);
	case MONKEY5:  return std::tuple<int64_t, int64_t>(old % 17 == 0 ? MONKEY4 : MONKEY0, old);
	case MONKEY6:  return std::tuple<int64_t, int64_t>(old % 19 == 0 ? MONKEY0 : MONKEY5, old);
	case MONKEY7:  return std::tuple<int64_t, int64_t>(old %  7 == 0 ? MONKEY3 : MONKEY2, old);
	default: assert(false && "test???");
	}
}

std::tuple<int64_t, int64_t> test_part2(Monkeys id, int64_t old)
{
	old %= COMMON_DIVISOR;
	switch (id)
	{
	case MONKEY0:  return std::tuple<int64_t, int64_t>(old %  3 == 0 ? MONKEY4 : MONKEY1, old);
	case MONKEY1:  return std::tuple<int64_t, int64_t>(old % 13 == 0 ? MONKEY7 : MONKEY3, old);
	case MONKEY2:  return std::tuple<int64_t, int64_t>(old %  2 == 0 ? MONKEY6 : MONKEY5, old);
	case MONKEY3:  return std::tuple<int64_t, int64_t>(old % 11 == 0 ? MONKEY2 : MONKEY6, old);
	case MONKEY4:  return std::tuple<int64_t, int64_t>(old %  5 == 0 ? MONKEY1 : MONKEY7, old);
	case MONKEY5:  return std::tuple<int64_t, int64_t>(old % 17 == 0 ? MONKEY4 : MONKEY0, old);
	case MONKEY6:  return std::tuple<int64_t, int64_t>(old % 19 == 0 ? MONKEY0 : MONKEY5, old);
	case MONKEY7:  return std::tuple<int64_t, int64_t>(old %  7 == 0 ? MONKEY3 : MONKEY2, old);
	default: assert(false && "test???");
	}
}

void debug(size_t round, std::vector<std::queue<int64_t>>& monkeys, std::vector<int64_t> inspections)
{
	std::cout << "After round " << round << ", the monkeys are holding items with these worry levels : \n";
	for (size_t id = 0; id < monkeys.size(); id++)
	{
		std::cout << "Monkey " << id << " with " << inspections[id] << " inspections: ";
		size_t size = monkeys[id].size();
		for (size_t i = 0; i < size; i++)
		{
			std::cout << monkeys[id].front() << ", ";
			monkeys[id].push(monkeys[id].front());
			monkeys[id].pop();
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}


int64_t loop(std::vector<std::queue<int64_t>>& monkeys, std::vector<int64_t> inspections)
{
	for (size_t round = 0; round < ROUNDS; round++)
	{
		for (size_t id = 0; id < monkeys.size(); id++)
		{
			size_t size = monkeys[id].size();
			for (size_t i = 0; i < size; i++)
			{
				operation(static_cast<Monkeys>(id), monkeys[id].front());
				auto [receiver, value] = test_part2(static_cast<Monkeys>(id), monkeys[id].front());
				monkeys[id].pop();
				inspections[id]++;
				monkeys[receiver].push(value);
			}
		}
		//debug(round, monkeys, inspections);
	}

	std::pair<int64_t, int64_t> twohighest = { 0, 0 };
	for (auto& value : inspections)
	{
		if (value > twohighest.first)
		{
			twohighest.second = twohighest.first;
			twohighest.first = value;
		}
		else if (value > twohighest.second)
		{
			twohighest.second = value;
		}
	}

	return twohighest.first * twohighest.second;
}

int main()
{
	std::vector<std::queue<int64_t>> monkeys = {
		std::queue<int64_t>({64, 89, 65, 95}),
		std::queue<int64_t>({76, 66, 74, 87, 70, 56, 51, 66}),
		std::queue<int64_t>({91, 60, 63}),
		std::queue<int64_t>({92, 61, 79, 97, 79}),
		std::queue<int64_t>({93, 54}),
		std::queue<int64_t>({60, 79, 92, 69, 88, 82, 70}),
		std::queue<int64_t>({64, 57, 73, 89, 55, 53}),
		std::queue<int64_t>({62}),
	};
	std::vector<int64_t> inspections = { 
		0, 0, 0, 0, 0, 0, 0, 0, 
	};

	int64_t monkey_bussiness = loop(monkeys, inspections);

	std::cout << "The level of monkey bussiness after " << ROUNDS << " rounds is: " << monkey_bussiness << ".\n";

	return 0;
}