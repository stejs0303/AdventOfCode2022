#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>
#include <iomanip>

struct Tree
{
	std::string_view name;
	std::string_view type;
	int disk_usage;

	Tree* parent;
	std::unordered_map<std::string, Tree> branches;

	Tree() : disk_usage(0), parent(nullptr) {}

	Tree(std::string_view& _name, std::string_view& _type, int _disk_usage)
		: name(_name), type(_type), disk_usage(_disk_usage), parent(nullptr) {}

	Tree(std::string_view&& _name, std::string_view&& _type, int _disk_usage)
		: name(_name), type(_type), disk_usage(_disk_usage), parent(nullptr) {}
};


void load_input(const std::string&& filepath, std::vector<std::string>& out)
{
	std::ifstream file(filepath);
	std::string line;

	while (std::getline(file, line))
		out.push_back(line);

	file.close();
}


std::tuple<std::string_view, std::string_view, int> parse_instruction(const std::string& instruction)
{
	std::string_view type;
	std::string_view name;
	int size = 0;
	
	if (instruction[0] == '$')
	{
		type = std::string_view(&instruction.c_str()[2], 2);
		name = instruction.length() > 3 ? std::string_view(&instruction.c_str()[5]) : "";
	}
	else if ((type = std::string_view(instruction.c_str(), 3)) == "dir")
	{
		name = std::string_view(&instruction.c_str()[4]);
	}
	else
	{
		type = "file";

		size_t space = instruction.find_first_of(' ');
		name = std::string_view(&instruction.c_str()[space + 1]);
		size = std::atoi(std::string_view(instruction.c_str(), space - 1).data());
	}
	
	return std::tuple(type, name, size);
}


int update_dir_sizes(Tree& root)
{
	for (auto& [key, branch] : root.branches)
		root.disk_usage += update_dir_sizes(branch);
	
	return root.disk_usage;
}


int construct_dir_tree(const std::vector<std::string>& instructions, Tree& root)
{
	bool ls = false;
	
	Tree* current = &root;

	for (auto& instruction : instructions)
	{
		auto [type, name, size] = parse_instruction(instruction);

		if (type == "cd") 
		{
			ls = false;

			if (name == "..")
				current = current->parent;
			else if (name == "/")
				current = &root;
			else
				current = &current->branches.at(name.data());
		}
		else if (type == "ls")
		{
			ls = true;
		}
		else if (ls)
		{
			current->branches[name.data()] = Tree(name, type, size);
			current->branches[name.data()].parent = current;
		}
	}

	return update_dir_sizes(root);
}


int sum_smaller_than(Tree& root, const int limit)
{
	int sum = 0;
	for (auto& [key, branch] : root.branches)
		sum += sum_smaller_than(branch, limit);

	if (root.type == "dir" && root.disk_usage < limit)
		return sum + root.disk_usage;
	
	return sum;
}


Tree* get_size_of_smallest_possible(Tree& root, const int size_to_delete) 
{
	Tree* smallest = &root;

	for (auto& [key, branch] : root.branches)
	{
		Tree* tmp = get_size_of_smallest_possible(branch, size_to_delete);
		if (tmp->disk_usage < smallest->disk_usage && tmp->disk_usage > size_to_delete)
			smallest = tmp;
	}

	return smallest;
}


void print_dir_tree(const Tree& root, const size_t max_depth, const size_t indent = 0)
{
	if (indent > max_depth && max_depth != 0) return;

	for (size_t i = 0; i < indent; i++) 
		std::cout << "-";

	int align = 26;
	if (indent) { std::cout << " "; align--; }
	std::cout << root.name << std::setw(align - root.name.length() - indent) << " (" << root.type << ", " << root.disk_usage << ")\n";
	
	for (auto& [key, branch] : root.branches)
		print_dir_tree(branch, max_depth, indent + 1);

	if (!indent) std::cout << std::endl;
}


int main()
{
	std::vector<std::string> data;
	load_input("Day_7\\terminal_output.txt", data);
	
	Tree root("/", "dir", 0);
	int overall_size = construct_dir_tree(data, root);
	
	//print_dir_tree(root, 3);

	int size = sum_smaller_than(root, 100'000);

	std::cout << "The sum of all folders that take up less than 100'000 of storage is: " << size << std::endl;

	int need_to_free_up = 30000000 - (70000000 - overall_size);
	Tree* smallest = get_size_of_smallest_possible(root, need_to_free_up);

	std::cout << "The smallest directory that needs to be deleted to free up " << 
		need_to_free_up << " memory for update is: " << smallest->name << " (size = " << smallest->disk_usage << ")" << std::endl;

	return 0;
}