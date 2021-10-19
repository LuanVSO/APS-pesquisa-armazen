#pragma once
#include <ranges>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include <map>
#include <functional>
#include <compare>

namespace bubble {
	 uint64_t sort(std::ranges::random_access_range auto& in) {
		uint64_t num_comparacao{};
		size_t n{ in.size() };

		do {
			size_t novon = 0;
			for (size_t i{ 1 }; i <= n - 1; i++) {
				num_comparacao++;
				if (in[i - 1] > in[i]) {
					std::swap(in[i - 1], in[i]);
					novon = i;
				}
			}
			n = novon;
		} while (n >= 1);
		if (!std::ranges::is_sorted(in)) __debugbreak();
		return num_comparacao;
	}
}

namespace selection {
	 uint64_t sort(std::ranges::random_access_range auto& in) {
		uint64_t num_comparacao{};
		size_t size = in.size();

		for (size_t i = 0; i < size - 1; i++) {
			auto jmin = i;
			for (auto j = i + 1; j < size; j++) {
				num_comparacao++;
				if (in[j] < in[jmin])
					jmin = j;
			}
			if (jmin != i)
				std::swap(in[i], in[jmin]);
		}
		if (!std::ranges::is_sorted(in)) __debugbreak();
		return num_comparacao;
	}
}

namespace insertion {
	 uint64_t sort(std::ranges::bidirectional_range auto& in) {
		uint64_t num_comparacao{};

		for (auto i = std::next(in.begin()); i != in.end(); i++)
		{
			for (auto ant = i, p = std::prev(i);
				(num_comparacao++, (*p > *ant)); ant = p--) {
				std::swap(*p, *ant);
				if (p == in.begin()) break;
			}
		}

		if (!std::ranges::is_sorted(in)) __debugbreak();
		return num_comparacao;
	}
}

namespace heap {
	 uint64_t sort(std::ranges::random_access_range auto& in) {
		uint64_t num_comparacao{};
		const auto comp_contada =
			[&num_comparacao](const auto& i, const auto& b) {
			num_comparacao++;
			return i < b;
		};
		std::ranges::make_heap(in, comp_contada);
		for (auto end = std::prev(in.end()); end != in.begin(); end--) {
			std::swap(*end, *in.begin());
			std::make_heap(in.begin(), end, comp_contada);
		}

		if (!std::ranges::is_sorted(in)) __debugbreak();
		return num_comparacao;
	}
}

namespace merge {
	 template<typename Begin, typename End> requires std::contiguous_iterator<Begin>&& std::contiguous_iterator<End>
		uint64_t sort(Begin begin, End end) {
		uint64_t num_comparacao{};
		const auto comp_contada = [&num_comparacao](const auto& i, const auto& b) {
			num_comparacao++;
			return i < b;
		};

		const auto size = std::distance(begin, end);

		if (size > 1) {
			const auto pontomedio = std::next(begin, size >> 1);
			num_comparacao += merge::sort(begin, pontomedio);
			num_comparacao += merge::sort(pontomedio, end);
			std::inplace_merge(begin, pontomedio, end, comp_contada);
		}

		if (!std::is_sorted(begin, end)) __debugbreak();
		return num_comparacao;
	}
	 uint64_t sort(std::ranges::contiguous_range auto& in) {
		return merge::sort(in.begin(), in.end());
	}
}

namespace quick {
	template<typename T>
	constexpr inline T median(T t1, T t2, T t3) {
		if (t1 < t2) {
			if (t2 < t3)
				return t2;
			else if (t1 < t3)
				return t3;
			else
				return t1;
		}
		else {
			if (t1 < t3)
				return t1;
			else if (t2 < t3)
				return t3;
			else
				return t2;
		}
	}
	 uint64_t sort(std::random_access_iterator auto begin, std::random_access_iterator auto end) {
		uint64_t num_comparacao{};

		if (begin == end || begin + 1 == end)
			return num_comparacao;

		const auto size = std::distance(begin, end);
		const auto meio = std::next(begin, size >> 1);
		const auto pivot = median(*begin, *meio, *(end - 1));
		const auto comp_contada = [&pivot, &num_comparacao](const auto i) {num_comparacao++; return i < pivot; };
		auto comp_contada_menorigual = [&num_comparacao, &pivot](const auto& i) {
			num_comparacao++;
			return i <= pivot;
		};

		const auto parte1 = std::partition(begin, end, comp_contada);
		const auto parte2 = std::partition(parte1, end, comp_contada_menorigual);
		num_comparacao += quick::sort(begin, parte1);
		num_comparacao += quick::sort(parte2, end);

		return num_comparacao;
	}
	 uint64_t sort(std::ranges::random_access_range auto& in) {
		const auto r = quick::sort(in.begin(), in.end());
		if (!std::ranges::is_sorted(in)) __debugbreak();
		return r;
	}
}

namespace count {
	 template <std::ranges::random_access_range T>
		uint64_t sort(T& in) {
		uint64_t num_comp{};
		const auto comp_contada = [&num_comp](const auto& l, const auto& r) {num_comp++; return l < r; };
		(void)std::ranges::max_element(in, comp_contada);
		(void)std::ranges::min_element(in, comp_contada);



		return num_comp;
	}
}
