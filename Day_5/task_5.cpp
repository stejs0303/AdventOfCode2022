#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <assert.h>
#include <sstream>


void load_table(const std::string&& filepath, std::unordered_map<size_t, std::stack<char>>& out)
{
	std::ifstream file(filepath);
	std::vector<std::string> temp_buffer;
	std::string line;

	while (std::getline(file, line))
		temp_buffer.push_back(line);
	
	std::string& first_row = temp_buffer.back();

	for (size_t i = 1; i < first_row.length(); i += 4)
		out[std::atoi(&first_row.c_str()[i])] = std::stack<char>();

	for (auto it = temp_buffer.rbegin() + 1; it != temp_buffer.rend(); it++)
		for (size_t i = 1; i < (*it).length(); i += 4)
			if ((*it)[i] != ' ')
				out[1 + i / 4].push((*it)[i]);
	
	file.close();
}


void load_instructions(const std::string&& filepath, std::vector<std::string>& out)
{
	std::ifstream file(filepath);
	std::string line;

	while (std::getline(file, line))
		out.push_back(line);

	file.close();
}


void reorder_9000(const std::vector<std::string>& moves, std::unordered_map<size_t, std::stack<char>>& boxes)
{
	for (auto& operation : moves)
	{
		//offset to first number of operation
		size_t move = operation.find("move") + 5;
		size_t from = operation.find("from") + 5;
		size_t to	= operation.find("to") + 3;

		//actual value
		move = operation.at(move + 1) != ' ' ? 
			(size_t) std::atoi(std::string_view(&operation.c_str()[move], 2).data()) : 
			(size_t) std::atoi(&operation.c_str()[move]);
		from = (size_t) std::atoi(&operation.c_str()[from]);
		to	 = (size_t) std::atoi(&operation.c_str()[to]);

		for (size_t i = 0; i < move; i++)
		{
			boxes.at(to).push(boxes.at(from).top());
			boxes.at(from).pop();
		}
	}
}


void reorder_9001(const std::vector<std::string>& moves, std::unordered_map<size_t, std::stack<char>>& boxes)
{
	std::stack<char> buffer;

	for (auto& operation : moves)
	{
		//offset to first number of operation
		size_t move = operation.find("move") + 5;
		size_t from = operation.find("from") + 5;
		size_t to = operation.find("to") + 3;

		//actual value
		move = operation.at(move + 1) != ' ' ?
			(size_t)std::atoi(std::string_view(&operation.c_str()[move], 2).data()) :
			(size_t)std::atoi(&operation.c_str()[move]);
		from = (size_t)std::atoi(&operation.c_str()[from]);
		to = (size_t)std::atoi(&operation.c_str()[to]);

		for (size_t i = 0; i < move; i++)
		{
			buffer.push(boxes.at(from).top());
			boxes.at(from).pop();
		}

		for (size_t i = 0; i < move; i++)
		{
			boxes.at(to).push(buffer.top());
			buffer.pop();
		}

		if (!buffer.empty()) assert(false && "???");
	}
}


std::string get_tops(const std::unordered_map<size_t, std::stack<char>> boxes)
{
	std::stringbuf tops;
	for (auto& [key, stack] : boxes)
		tops.sputc(stack.top());
	
	return tops.str();
}


int main()
{
	// I could use an array instead of a map, but having to subtract 1 when indexing into it would be too much hassle to debug. This solves the problem.
	std::unordered_map<size_t, std::stack<char>> boxes;
	std::vector<std::string> instructions;

	load_table("Day_5\\table.txt", boxes);
	load_instructions("Day_5\\instruction.txt", instructions);

	reorder_9001(instructions, boxes);

	std::cout << "Boxes on top are: " << get_tops(boxes) << "." << std::endl;
	
	return 0;
}