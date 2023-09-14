#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


bool sort_by_sec_desc(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
	return (a.second > b.second);
}


void read_contents(const std::string& filepath, std::vector<std::pair<int, int>>& out)
{
	std::string line;
	std::ifstream file(filepath);

	for (size_t i = 0; !file.eof(); i++)
	{
		std::pair<int, int> elf = std::make_pair<int, int>(i, 0);
		while (std::getline(file, line))
		{
			if (line == "") break;
			elf.second += std::stoi(line);
		}
		out.push_back(elf);
	}

	file.close();
}


int main()
{
	std::vector<std::pair<int, int>> calories;

	read_contents("Day_1\\Calories.txt", calories);

	std::sort(calories.begin(), calories.end(), sort_by_sec_desc);

	int res_calories = 0;
	for (size_t i = 0; i < 3; i++) 
		res_calories += calories.at(i).second;

	std::cout << "Elf: " << calories[0].first << " carries " << calories[0].second << " calories." << std::endl;
	std::cout << "First three elves have " << res_calories << " calories." << std::endl;

	return 0;
}
