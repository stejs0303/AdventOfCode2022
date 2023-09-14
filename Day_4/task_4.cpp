#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>


void read_contents(const std::string& filepath, std::vector<std::string>& out)
{
	std::ifstream file(filepath);
	std::string line;

	while (std::getline(file, line))
		out.push_back(line);

	file.close();
}


std::tuple<std::pair<int, int>, std::pair<int, int>> 
get_ranges(const std::string_view& assignments_1, const std::string_view& assignments_2)
{
	size_t pos_1 = assignments_1.find('-');
	size_t pos_2 = assignments_2.find('-');

	return std::make_tuple<>(
		std::make_pair<>(
			std::atoi(std::string_view(assignments_1.data(), pos_1).data()),
			std::atoi(std::string_view(&assignments_1.data()[pos_1 + 1]).data())
		),
		std::make_pair<>(
			std::atoi(std::string_view(assignments_2.data(), pos_2).data()),
			std::atoi(std::string_view(&assignments_2.data()[pos_2 + 1]).data())
		)
	);
}


bool is_sub_range(const std::string_view& assignments_1, const std::string_view& assignments_2)
{
	auto [range_1, range_2] = get_ranges(assignments_1, assignments_2);

	if (range_1.first <= range_2.first and range_1.second >= range_2.second or 
		range_2.first <= range_1.first and range_2.second >= range_1.second) return true;

	return false;
}


bool is_overlapping(const std::string_view& assignments_1, const std::string_view& assignments_2)
{
	auto [range_1, range_2] = get_ranges(assignments_1, assignments_2);

	if (range_1.second < range_2.first and range_2.second > range_1.first or 
		range_2.second < range_1.first and range_1.second > range_2.first) return false;

	return true;
}


std::tuple<int, int> 
number_of_subranges(const std::vector<std::string> pairs)
{
	size_t splitter = 0; 
	int part_1 = 0, part_2 = 0;

	for (const auto& pair : pairs)
	{
		splitter = pair.find(',');
		std::string_view job_list_1(pair.c_str(), splitter), job_list_2(&pair.c_str()[splitter + 1]);
		
		part_1 += is_sub_range(job_list_1, job_list_2);
		part_2 += is_overlapping(job_list_1, job_list_2);
	}

	return std::make_tuple<>(part_1, part_2);
}


int main()
{
	std::vector<std::string> pairs;

	read_contents("Day_4\\input.txt", pairs);

	auto [part_1, part_2] = number_of_subranges(pairs);

	std::cout << "Number of pairs that have completely overlapping jobs is: " << part_1 << "." << std::endl;
	std::cout << "Number of pairs that have partially overlapping jobs is: " << part_2 << "." << std::endl;

	return 0;
}