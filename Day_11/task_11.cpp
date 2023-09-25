#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <memory>

#define ROUNDS 10000
#define COMMON_DIVISOR (3 * 13 * 2 * 11 * 5 * 17 * 19 * 7)

enum Monkeys { MONKEY0 = 0, MONKEY1, MONKEY2, MONKEY3, MONKEY4, MONKEY5, MONKEY6, MONKEY7, };

class Monkey
{
public:
	Monkey(const std::vector<int64_t>& starting_items)
	{
		for (auto& item : starting_items)
			this->items.push(item);
	}
	~Monkey() {}
	virtual void operation() = 0;
	virtual std::tuple<Monkeys, int64_t> test_part1() = 0;
	virtual std::tuple<Monkeys, int64_t> test_part2() = 0;

public:
	std::queue<int64_t> items;
	int64_t inspected = 0;
};

class Monkey0 : public Monkey
{
public:
	Monkey0(const std::vector<int64_t>&& starting_items) : Monkey(starting_items) {}
	
	void operation()
	{
		this->items.front() *= 7;
		this->inspected++;
	}

	std::tuple<Monkeys, int64_t> test_part1()
	{
		int64_t item = this->items.front() / 3;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 3 == 0 ? MONKEY4 : MONKEY1, item);
	}

	std::tuple<Monkeys, int64_t> test_part2()
	{
		int64_t item = this->items.front() % COMMON_DIVISOR;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 3 == 0 ? MONKEY4 : MONKEY1, item);
	}
};

class Monkey1 : public Monkey
{
public:
	Monkey1(const std::vector<int64_t>&& starting_items) : Monkey(starting_items) {}

	void operation()
	{
		this->items.front() += 5;
		this->inspected++;
	}
	std::tuple<Monkeys, int64_t> test_part1()
	{
		int64_t item = this->items.front() / 3;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 13 == 0 ? MONKEY7 : MONKEY3, item);
	}

	std::tuple<Monkeys, int64_t> test_part2()
	{
		int64_t item = this->items.front() % COMMON_DIVISOR;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 13 == 0 ? MONKEY7 : MONKEY3, item);
	}
};

class Monkey2 : public Monkey
{
public:
	Monkey2(const std::vector<int64_t>&& starting_items) : Monkey(starting_items) {}

	void operation()
	{
		this->items.front() *= this->items.front();
		this->inspected++;
	}

	std::tuple<Monkeys, int64_t> test_part1()
	{
		int64_t item = this->items.front() / 3;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 2 == 0 ? MONKEY6 : MONKEY5, item);
	}

	std::tuple<Monkeys, int64_t> test_part2()
	{
		int64_t item = this->items.front() % COMMON_DIVISOR;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 2 == 0 ? MONKEY6 : MONKEY5, item);
	}
};

class Monkey3 : public Monkey
{
public:
	Monkey3(const std::vector<int64_t>&& starting_items) : Monkey(starting_items) {}

	void operation()
	{
		this->items.front() += 6;
		this->inspected++;
	}

	std::tuple<Monkeys, int64_t> test_part1()
	{
		int64_t item = this->items.front() / 3;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 11 == 0 ? MONKEY2 : MONKEY6, item);
	}

	std::tuple<Monkeys, int64_t> test_part2()
	{
		int64_t item = this->items.front() % COMMON_DIVISOR;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 11 == 0 ? MONKEY2 : MONKEY6, item);
	}
};

class Monkey4 : public Monkey
{
public:
	Monkey4(const std::vector<int64_t>&& starting_items) : Monkey(starting_items) {}

	void operation()
	{
		this->items.front() *= 11;
		this->inspected++;
	}

	std::tuple<Monkeys, int64_t> test_part1()
	{
		int64_t item = this->items.front() / 3;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 5 == 0 ? MONKEY1 : MONKEY7, item);
	}

	std::tuple<Monkeys, int64_t> test_part2()
	{
		int64_t item = this->items.front() % COMMON_DIVISOR;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 5 == 0 ? MONKEY1 : MONKEY7, item);
	}
};

class Monkey5 : public Monkey
{
public:
	Monkey5(const std::vector<int64_t>&& starting_items) : Monkey(starting_items) {}

	void operation()
	{
		this->items.front() += 8;
		this->inspected++;
	}

	std::tuple<Monkeys, int64_t> test_part1()
	{
		int64_t item = this->items.front() / 3;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 17 == 0 ? MONKEY4 : MONKEY0, item);
	}

	std::tuple<Monkeys, int64_t> test_part2()
	{
		int64_t item = this->items.front() % COMMON_DIVISOR;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 17 == 0 ? MONKEY4 : MONKEY0, item);
	}
};

class Monkey6 : public Monkey
{
public:
	Monkey6(const std::vector<int64_t>&& starting_items) : Monkey(starting_items) {}

	void operation()
	{
		this->items.front() += 1;
		this->inspected++;
	}

	std::tuple<Monkeys, int64_t> test_part1()
	{
		int64_t item = this->items.front() / 3;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 19 == 0 ? MONKEY0 : MONKEY5, item);
	}

	std::tuple<Monkeys, int64_t> test_part2()
	{
		int64_t item = this->items.front() % COMMON_DIVISOR;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 19 == 0 ? MONKEY0 : MONKEY5, item);
	}
};

class Monkey7 : public Monkey
{
public:
	Monkey7(const std::vector<int64_t>&& starting_items) : Monkey(starting_items) {}

	void operation()
	{
		this->items.front() += 4;
		this->inspected++;
	}

	std::tuple<Monkeys, int64_t> test_part1()
	{
		int64_t item = this->items.front() / 3;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 7 == 0 ? MONKEY3 : MONKEY2, item);
	}

	std::tuple<Monkeys, int64_t> test_part2()
	{
		int64_t item = this->items.front() % COMMON_DIVISOR;
		this->items.pop();
		return std::tuple<Monkeys, int64_t>(item % 7 == 0 ? MONKEY3 : MONKEY2, item);
	}
};

void debug(size_t round, std::vector<std::shared_ptr<Monkey>>& monkeys)
{
	std::cout << "After round " << round << ", the monkeys are holding items with these worry levels : \n";
	for (size_t id = 0; id < monkeys.size(); id++)
	{
		std::cout << "Monkey " << id << " with " << monkeys[id]->inspected << " inspections: ";
		size_t size = monkeys[id]->items.size();
		for (size_t i = 0; i < size; i++)
		{
			std::cout << monkeys[id]->items.front() << ", ";
			monkeys[id]->items.push(monkeys[id]->items.front());
			monkeys[id]->items.pop();
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

int64_t loop(std::vector<std::shared_ptr<Monkey>>& monkeys)
{
	for (size_t round = 0; round < ROUNDS; round++)
	{
		for (auto& monkey : monkeys)
		{
			size_t size = monkey->items.size();
			for (size_t i = 0; i < size; i++)
			{
				monkey->operation();
				auto [receiver, item] = monkey->test_part2();
				monkeys[receiver]->items.push(item);
			}
		}
		//debug(round, monkeys);
	}

	std::pair<int64_t, int64_t> twohighest = {0, 0};
	for (auto& monkey : monkeys)
	{
		if (monkey->inspected > twohighest.first)
		{
			twohighest.second = twohighest.first;
			twohighest.first = monkey->inspected;
		}
		else if (monkey->inspected > twohighest.second)
		{
			twohighest.second = monkey->inspected;
		}
	}

	return twohighest.first * twohighest.second;
}

int main()
{
	std::vector<std::shared_ptr<Monkey>> monkeys = {
		std::make_shared<Monkey0>(std::vector<int64_t>({64, 89, 65, 95})),
		std::make_shared<Monkey1>(std::vector<int64_t>({76, 66, 74, 87, 70, 56, 51, 66})),
		std::make_shared<Monkey2>(std::vector<int64_t>({91, 60, 63})),
		std::make_shared<Monkey3>(std::vector<int64_t>({92, 61, 79, 97, 79})),
		std::make_shared<Monkey4>(std::vector<int64_t>({93, 54})),
		std::make_shared<Monkey5>(std::vector<int64_t>({60, 79, 92, 69, 88, 82, 70})),
		std::make_shared<Monkey6>(std::vector<int64_t>({64, 57, 73, 89, 55, 53})),
		std::make_shared<Monkey7>(std::vector<int64_t>({62})),
	};

	int64_t monkey_bussiness = loop(monkeys);

	std::cout << "The level of monkey bussiness after " << ROUNDS << " rounds is: " << monkey_bussiness << ".\n";

	return 0;
}