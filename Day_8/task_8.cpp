#include <iostream>
#include <string>
#include <vector>
#include <fstream>


#define LOG(x) \
	do { std::cout << (#x) << " =" << std::endl; print_grid(x); } while(false)

void print_grid(const std::vector<std::vector<int>>&data)
{
	for (auto& vec : data)
	{
		for (auto& val : vec)
			std::cout << val << " ";
		std::cout << "\n";
	}
	std::cout << std::endl;
}


struct Sides
{
	int left = -1;
	int top = -1;
	int right = -1;
	int bottom = -1;
};


void load_input(const std::string&& filepath, std::vector<std::vector<int>>& out)
{
	std::fstream file(filepath);
	std::string line;

	while (std::getline(file, line))
	{
		std::vector<int> row;
		for (auto& c : line)
			row.push_back((int)c - 48);
		out.push_back(row);
	}

	file.close();
}


void compare_data(const std::vector<std::vector<int>>& data, const std::vector<std::vector<int>>& visibility, int fraction)
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[0].size() / fraction; j++)
		{
			std::cout << "\033[1;37m" << data[i][j] << "\033[1;33m(" << visibility[i][j] << ") ";
		}
		std::cout << "\n";
	}
	std::cout << "\033[1;37m" << std::endl;
}


void calculate_visibility(const std::vector<std::vector<int>>& forest, std::vector<std::vector<int>>& visibility)
{
	auto update = [](const int tree, int& visible, int& highest)
	{
		if (tree > highest) // or tree == 0 and highest <= 0)
		{
			highest = tree;
			visible = true;
		}
	};
	
	std::vector<Sides> hvals(forest.size(), Sides());
	int height = forest.size(), width = forest[0].size();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			update(forest[i][j],              visibility[i][j],              hvals[i].left);
			update(forest[i][width - j - 1],  visibility[i][width - j - 1],  hvals[i].right);
			update(forest[i][j],              visibility[i][j],              hvals[j].top);
			update(forest[height - i - 1][j], visibility[height - i - 1][j], hvals[j].bottom);
		}
	}
}


int count_visible(const std::vector<std::vector<int>>& visibility)
{
	int count = 0;
	for (auto& row : visibility)
		for (auto& val : row)
			count += val;
	
	return count;
}


int find_highest_visibility_score(const std::vector<std::vector<int>>& data)
{
	auto compare = [&](const int& current, const int& origin, int& counter, int& keep_going) 
	{
		if (current >= origin) keep_going = false;
		counter++;
	};

	int best_score = 0;
	int height = data.size(), width = data[0].size();
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int left = 0, top = 0, right = 0, bottom = 0;

			for (int i = x - 1, go_on = true; i >= 0 && go_on; i--)
				compare(data[i][y], data[x][y], left, go_on);

			for (int i = y - 1, go_on = true; i >= 0 && go_on; i--)
				compare(data[x][i], data[x][y], top, go_on);

			for (int i = x + 1, go_on = true; i < width && go_on; i++)
				compare(data[i][y], data[x][y], right, go_on);

			for (int i = y + 1, go_on = true; i < height && go_on; i++)
				compare(data[x][i], data[x][y], bottom, go_on);

			int tmp = left * top * right * bottom;
			best_score = tmp > best_score ? tmp : best_score;
		}
	}

	return best_score;
}


int main()
{
	std::vector<std::vector<int>> data;
	load_input("Day_8\\forest.txt", data);
	
	std::vector<std::vector<int>> visibility(data.size(), std::vector<int>(data[0].size(), 0));
	calculate_visibility(data, visibility);

	int visible = count_visible(visibility);
	int highest_score = find_highest_visibility_score(data);

	std::cout << "Number of visible trees is: " << visible << ".\n";
	std::cout << "Highest possible tree score is: " << highest_score << ".\n";

	//LOG(data);
	//LOG(visibility);

	//compare_data(data, visibility, 4);

	return 0;
}