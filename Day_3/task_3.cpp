#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>


const std::unordered_map<char, int> priority = { 
	{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}, {'f', 6}, {'g', 7}, {'h', 8}, {'i', 9}, {'j', 10},
	{'k', 11}, {'l', 12}, {'m', 13}, {'n', 14}, {'o', 15}, {'p', 16}, {'q', 17}, {'r', 18}, {'s', 19}, 
	{'t', 20}, {'u', 21}, {'v', 22}, {'w', 23}, {'x', 24}, {'y', 25}, {'z', 26}, {'A', 27}, {'B', 28}, 
	{'C', 29}, {'D', 30}, {'E', 31}, {'F', 32}, {'G', 33}, {'H', 34}, {'I', 35}, {'J', 36}, {'K', 37}, 
	{'L', 38}, {'M', 39}, {'N', 40}, {'O', 41}, {'P', 42}, {'Q', 43}, {'R', 44}, {'S', 45}, {'T', 46}, 
	{'U', 47}, {'V', 48}, {'W', 49}, {'X', 50}, {'Y', 51}, {'Z', 52} 
};


void read_contents(const std::string& filepath, std::vector<std::string>& out)
{
	std::ifstream file(filepath);
	std::string line;

	while (std::getline(file, line))
		out.push_back(line);

	file.close();
}


char find_same(const std::string& bag) 
{
	std::unordered_set<char> compartment;

	size_t half = (bag.length() / 2);
	std::string_view compartment_1(bag.c_str(), half);
	std::string_view compartment_2(&bag.c_str()[half], half);

	for (auto& c : compartment_1)
		compartment.insert(c);

	for (auto& c : compartment_2)
		if (compartment.contains(c)) 
			return c;
	
	return NULL;
}


char find_same_in_group(const std::string& bag_1, const std::string& bag_2, const std::string& bag_3)
{
	std::unordered_set<char> compartment;
	std::unordered_set<char> partially_filtered;

	for (auto& c : bag_1)
		compartment.insert(c);

	for (auto& c : bag_2)
		if (compartment.contains(c))
			partially_filtered.insert(c);

	for (auto& c : bag_3)
		if (partially_filtered.contains(c)) 
			return c;
	
	return NULL;
}


int accumulate_priority(const std::vector<std::string>& bags)
{
	int res = 0;
	for (auto& bag : bags)
		if (char same_item = find_same(bag))
			res += priority.at(same_item);

	return res;
}


int accumulate_group_priority(const std::vector<std::string>& bags)
{
	int res = 0;
	for (size_t i = 2; i <= bags.size(); i += 3)
		if (char same_item = find_same_in_group(bags[i - 2], bags[i - 1], bags[i]))
			res += priority.at(same_item);

	return res;
}


int main() 
{
	std::vector<std::string> bags;

	read_contents("Day_3\\input.txt", bags);

	int task_1 = accumulate_priority(bags);
	int task_2 = accumulate_group_priority(bags);

	std::cout << "Accumulated priority of items that appear in both compartments is: " << task_1 << "." << std::endl;
	std::cout << "Accumulated priority of items that appear in groups of 3 bags is: " << task_2 << "." << std::endl;

	return 0;
}