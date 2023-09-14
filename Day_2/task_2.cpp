#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <assert.h>
#include <unordered_map>

enum Cyphre_Opponent
{
	o_ROCK	   = 'A',
	o_PAPER	   = 'B',
	o_SCISSORS = 'C',
};


enum Cyphre_You
{
	y_ROCK	   = 'X',
	y_PAPER	   = 'Y',
	y_SCISSORS = 'Z'
};


enum Outcome
{
	c_LOSS = 'X',
	c_DRAW = 'Y',
	c_WIN  = 'Z'
};


enum Points
{
	ROCK	 = 1,
	PAPER	 = 2,
	SCISSORS = 3,
	
	LOSS	 = 0,
	DRAW	 = 3,
	WIN		 = 6
};


std::unordered_map<Outcome, std::unordered_map<Cyphre_Opponent, Points>> map_to_points = { 
	{ c_LOSS, { {o_ROCK, SCISSORS},	{o_PAPER, ROCK},		{o_SCISSORS, PAPER}		} },
	{ c_DRAW, { {o_ROCK, ROCK},		{o_PAPER, PAPER},		{o_SCISSORS, SCISSORS}	} },
	{ c_WIN,  { {o_ROCK, PAPER},	{o_PAPER, SCISSORS},	{o_SCISSORS, ROCK}		} }
};


void read_contents(const std::string& filepath, std::vector<std::pair<char, char>>& out)
{
	std::ifstream file(filepath);

	char o, y;
	while (file >> o >> y)
		out.push_back(std::make_pair<>(o, y));

	file.close();
}


int calculate_score_part1(const std::pair<char, char>& game)
{
	int res = 0;

	switch (game.second)
	{
	case y_ROCK:		res += Points::ROCK;		break;
	case y_PAPER:		res += Points::PAPER;		break;
	case y_SCISSORS:	res += Points::SCISSORS;	break;
	default:			assert(false && "???");
	}

	res += Points::DRAW * (game.first == o_ROCK		and game.second == y_ROCK or 
						   game.first == o_PAPER	and game.second == y_PAPER or
						   game.first == o_SCISSORS and game.second == y_SCISSORS);

	res += Points::WIN	* (game.first == o_ROCK		and game.second == y_PAPER or
						   game.first == o_PAPER	and game.second == y_SCISSORS or
						   game.first == o_SCISSORS and game.second == y_ROCK);
	
	res += Points::LOSS * (game.first == o_ROCK		and game.second == y_SCISSORS or
						   game.first == o_PAPER	and game.second == y_ROCK or
						   game.first == o_SCISSORS and game.second == y_PAPER);

	return res;

}


int calculate_score_part2(const std::pair<char, char>& game) 
{
	int res = 0;

	res += map_to_points[(Outcome) game.second][(Cyphre_Opponent) game.first];

	switch (game.second)
	{
	case c_DRAW:	res += Points::DRAW;	break;
	case c_LOSS:	res += Points::LOSS;	break;
	case c_WIN:		res += Points::WIN;		break;
	default:		assert(false && "???");
	}

	return res;
}


int accumulate(const std::vector<std::pair<char, char>> games)
{
	int acc = 0;

	for (auto& game : games)
		acc += calculate_score_part2(game);

	return acc;
}


int main()
{
	std::vector<std::pair<char, char>> games;

	read_contents("Day_2\\Guide.txt", games);

	int score = accumulate(games);

	std::cout << "Overall score is: " << score << "." << std::endl;

	return 0;
}