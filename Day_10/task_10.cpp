#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define WIDTH  40
#define HEIGHT 6


enum Instruction
{
	// 1 cycle
	NOOP = 1,
	// 2 cycles
	ADDX = 2
};


void load_readings(std::string&& filepath, std::vector<std::pair<Instruction, int>>& out)
{
	std::ifstream file(filepath);
	std::string line;

	while (std::getline(file, line))
	{
		if (line[0] == 'n')
			out.push_back(std::make_pair<>(NOOP, 0));
		else
			out.push_back(std::make_pair<>(ADDX, std::stoi(&line.c_str()[5])));
	}
	
	file.close();
}


int sum_of_signal_strengths(const std::vector<std::pair<Instruction, int>>& readings)
{
	int cycle = 0, regx = 1, sum_of_strengths = 0;

	for (auto& [instruction, reading] : readings)
	{
		for (int i = 0; i < instruction; i++)
			if ((++cycle) % 40 == 20) 
				sum_of_strengths += (regx * cycle);
		
		if (instruction == ADDX) regx += reading;
	}
	
	return sum_of_strengths;
}


void draw_image(const std::vector<std::pair<Instruction, int>>& readings)
{
	int cycle = 0, regx = 1;

	for (auto& [instruction, reading] : readings)
	{
		for (int i = 0; i < instruction; i++)
		{
			//char disp = '.';
			//if (std::abs(((cycle++) % WIDTH) - regx) <= 1) disp = '#';
			//std::cout << disp;
			std::cout << char('.' - 11 * (std::abs(((cycle++) % WIDTH) - regx) <= 1));
			if (cycle % (WIDTH) == 0) std::cout << "\n";
		}
		if (instruction == ADDX) regx += reading;
	}
}

int main()
{
	std::vector<std::pair<Instruction, int>> readings;
	load_readings("Day_10\\signal_readings.txt", readings);

	// part 1
	int sum = sum_of_signal_strengths(readings);
	std::cout << "The sum of signal strengths on 20th, 60th, 100th, 140th, 180th and 220th cycle is: " << sum << ".\n" << std::endl;

	// part 2
	draw_image(readings);

	return 0;
}