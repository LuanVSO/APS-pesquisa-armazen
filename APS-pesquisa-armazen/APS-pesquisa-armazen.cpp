#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>
#include <string_view>
#include <cstdlib>
#include <cstdint>
#include <ranges>
#include <cassert>
#include <chrono>
#include "sortAlgos.h"

int main()
{
	static constexpr size_t tamanhos[]{ 5,10,50,100,1'000,10'000 };

	auto run = [](auto& sort_func, size_t t_vetor) {
		std::vector<int> vetor(t_vetor);
		uint64_t accum{};

		for (size_t i = 0; i != 50; i++) {
			std::ranges::generate(vetor, rand);
			accum += sort_func(vetor);
		}

		const auto media = accum / 50;

		return media;
	};

	using namespace std::string_view_literals;

	const auto sort_functions = {
		//std::pair{bubble   ::sort<std::vector<int>>,   "bubble"sv},
		//std::pair{selection::sort<std::vector<int>>,"selection"sv},
		//std::pair{insertion::sort<std::vector<int>>,"insertion"sv},
		//std::pair{heap     ::sort<std::vector<int>>,     "heap"sv},
		//std::pair{merge    ::sort<std::vector<int>>,    "merge"sv},
		std::pair{quick    ::sort<std::vector<int>>,    "quick"sv},
		std::pair{count    ::sort<std::vector<int>>,    "count"sv},
		//std::pair{bucket   ::sort<std::vector<int>>,   "bucket"sv},
		std::pair{radix    ::sort<std::vector<int>>,    "radix"sv}
	};

	for (auto& [sort_func, name] : sort_functions) {
		std::cout << name << ":\n";
		for (const auto& size : tamanhos) {
			std::cout << size << ": " << run(sort_func, size) << '\n';
		}
		std::cout << "========================\n";
	}
	return EXIT_SUCCESS;
}
