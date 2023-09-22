#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <assert.h>
#include <unordered_set>

#define HEAD 0

enum Directions { Up = 0, Down, Left, Right };

struct hash_pair
{
	template<typename T, typename U>
	size_t operator()(const std::pair<T, U> tohash) const
	{
		auto hash_first = std::hash<T>{}(tohash.first);
		auto hash_second = std::hash<U>{}(tohash.second);
	
		if (hash_first != hash_second) 
			return hash_first ^ hash_second;
		return hash_first;
	}
};


void load_input(const std::string&& filepath, std::vector<std::pair<Directions, int>>& out)
{
	auto get_direction = [](const char dir)
	{
		switch (dir)
		{
		case 'U': return Up;
		case 'D': return Down;
		case 'L': return Left;
		case 'R': return Right;
		}
		assert(false && "???");
	};
	
	std::ifstream file(filepath);
	std::string line;

	while (std::getline(file, line))
		out.push_back(std::make_pair<>(get_direction(line[0]), std::stoi(&line.c_str()[2])));

	file.close();
}


size_t number_of_visited_positions_v1(const std::vector<std::pair<Directions, int>>& data)
{
	// x, y
	std::pair<int, int> head{0, 0};
	std::pair<int, int> tail{0, 0};
	std::unordered_set<std::pair<int, int>, hash_pair> visited({ tail });

	for (auto& [direction, moves] : data)
	{
		for (int i = 0; i < moves; i++)
		{
			head.second += 1 * (direction == Up)    - 1 * (direction == Down);
			head.first  += 1 * (direction == Right) - 1 * (direction == Left);

			if (std::max(std::abs(head.second - tail.second), std::abs(head.first - tail.first)) > 1)
			{
				tail.first =  head.first  + 1 * (direction == Left) - 1 * (direction == Right);
				tail.second = head.second + 1 * (direction == Down) - 1 * (direction == Up);
				visited.insert(tail);
			}
		}
	}
	return visited.size();
}


void debug_draw(const int width, const int height, const std::vector<std::pair<int, int>>& rope)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			char val = '.';
			for (int k = 0; k < rope.size(); k++)
				if (rope[k].first == j and rope[k].second == i) { val = (k == 0 ? 'K' : char(k + 48)); break; }
			std::cout << val << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n" << std::endl;
}


size_t number_of_visited_positions_v2(const std::vector<std::pair<Directions, int>>& data, int followed_knot)
{
	auto is_touching = [&](const std::vector<std::pair<int, int>>& rope, const size_t knot)
	{
		int max_distance = 1;
		return std::max(
			std::abs(rope[knot - 1].second - rope[knot].second), 
			std::abs(rope[knot - 1].first  - rope[knot].first)
		) <= max_distance;
	};

	// 20, 15 for debugging
	std::vector<std::pair<int, int>> rope = { {20, 15}, {20, 15}, {20, 15}, {20, 15}, {20, 15}, {20, 15}, {20, 15}, {20, 15}, {20, 15}, {20, 15} };
	if (followed_knot > rope.size() - 1) return 0;

	std::unordered_set<std::pair<int, int>, hash_pair> visited({ rope[followed_knot] });

	for (auto& [direction, moves] : data)
	{
		for (int i = 0; i < moves; i++)
		{
			rope[HEAD].first  += 1 * (direction == Right) - 1 * (direction == Left);
			rope[HEAD].second += 1 * (direction == Down)  - 1 * (direction == Up);

			for (size_t knot = 1; knot < rope.size(); knot++)
			{
				if (is_touching(rope, knot)) continue;
				
				if (rope[knot - 1].second != rope[knot].second and rope[knot - 1].first != rope[knot].first)
				{
					rope[knot].first  += -1 + 2 * (rope[knot - 1].first  > rope[knot].first);
					rope[knot].second += -1 + 2 * (rope[knot - 1].second > rope[knot].second);
				}
				while (!is_touching(rope, knot))
				{
					if (rope[knot - 1].second == rope[knot].second)
						rope[knot].first  += -1 + 2 * (rope[knot - 1].first  > rope[knot].first);
					if (rope[knot - 1].first == rope[knot].first)
						rope[knot].second += -1 + 2 * (rope[knot - 1].second > rope[knot].second);
				}
			}	
#ifdef DEBUG_DRAW
			debug_draw(40, 40, rope);
#endif // DEBUG_DRAW
			visited.insert(rope[followed_knot]);
		}
	}
	return visited.size();
}


int main()
{
	std::vector<std::pair<Directions, int>> data;
	load_input("Day_9\\input.txt", data);
	
#ifdef DEBUG_DRAW

	std::vector<std::pair<Directions, int>> testing_data = {
		{Right, 5}, {Up, 8}, {Left, 8}, { Down, 3 }, { Right, 17 }, { Down, 10 }, { Left, 25 }, { Up, 20 } };
	const size_t count = number_of_visited_positions_v2(testing_data, 9);
#else
	const size_t count = number_of_visited_positions_v2(data, 9);

#endif // DEBUG_DRAW

	std::cout << "Number of all visited positions is: " << count << ".\n";

	return 0;
}