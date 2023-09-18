#include <iostream>
#include <fstream>
#include <string>
#include <chrono>


void load_input(const std::string&& filepath, std::string& out)
{
	std::ifstream file(filepath);
	std::getline(file, out);
	file.close();
}


int find_packet_marker(const std::string& seq)
{
	for (size_t i = 3; i < seq.length(); i++)
		if (seq[i - 3] != seq[i - 2] and seq[i - 3] != seq[i - 1] and seq[i - 3] != seq[i] and
			seq[i - 2] != seq[i - 1] and seq[i - 2] != seq[i] and
			seq[i - 1] != seq[i]) return i + 1;
	
	return NULL;
}


int find_message_marker(const std::string_view&& seq)
{
	auto check_subsequence = [&](size_t i) 
	{
		for (int j = 13; j >= 0; j--)
			for (int k = j - 1; k >= 0; k--)
				if (seq[i-j] == seq[i-k]) return false;
		return true;
	};
	
	for (size_t i = 13; i < seq.length(); i++)
		if (check_subsequence(i)) return i + 1;
	
	return NULL;
}


void test(const std::string& data)
{
	using std::chrono::high_resolution_clock;
	using std::chrono::duration;
	using std::chrono::microseconds;

	int itterations = 1000;

	auto ts_v1 = high_resolution_clock::now();
	for (size_t i = 0; i < itterations; i++)
		find_packet_marker(data);
	auto te_v1 = high_resolution_clock::now();

	duration<double, std::micro> v1 = te_v1 - ts_v1;
	std::cout << "find_first_marker1 = " << v1.count() / itterations << "us\n";
}


int main()
{
	std::string data;
	load_input("Day_6\\input.txt", data);

	int packet_marker = find_packet_marker(data);
	int message_marker = find_message_marker(
		std::string_view(&data.c_str()[packet_marker], data.length() - (packet_marker)));

	std::cout << "First packet marker after character: " << packet_marker - 1 << " - ";
	for (int i = 3; i >= 0; i--) std::cout << data[packet_marker - i - 1];
	std::cout << "\nFirst packet starts at position: " << packet_marker << "." << std::endl;
	
	std::cout << "First message marker after character: " << packet_marker + message_marker - 1 << " - ";
	for (int i = 13; i >= 0; i--) std::cout << data[packet_marker + message_marker - i - 1];
	std::cout << "\nFirst message start at position: " << packet_marker + message_marker << "." << std::endl;

	//test(data);

	return 0;
}