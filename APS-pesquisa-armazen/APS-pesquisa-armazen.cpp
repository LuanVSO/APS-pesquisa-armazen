#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cstdlib>
#include <cstdint>
#include <ranges>
#include <cassert>
#include <chrono>


import sortAlgos;

int main()
{
	std::vector<std::array<int,5>> vetores(50);

	uint64_t accum{};
	std::chrono::high_resolution_clock::time_point clock;
	std::chrono::nanoseconds ns_accum{};
	for (auto&& array : vetores) {
		std::ranges::generate(array, rand);
		clock = std::chrono::high_resolution_clock::now();
		accum += count::sort(array);
		ns_accum += std::chrono::high_resolution_clock::now() - clock;
	}
	const auto media = double(accum) / vetores.size();
	const auto t_medio = ns_accum / vetores.size();

	std::cout 
		<< media << '\n' 
		<< t_medio << '\n';
}
