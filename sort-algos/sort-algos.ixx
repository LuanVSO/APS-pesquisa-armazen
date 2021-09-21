module;
#include <ranges>
#include <cstdint>
#include <algorithm>
#include <iterator>
export module sortAlgos;

namespace bubble {
	export uint64_t sort(std::ranges::random_access_range auto& in) {
		uint64_t num_comparacao{};
		size_t n{ in.size()};

		do {
			size_t novon = 0;
			for (size_t i{1}; i <= n-1; i++) {
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
	export uint64_t sort(std::ranges::random_access_range auto& in) {
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
	export uint64_t sort(std::ranges::bidirectional_range auto& in) {
		uint64_t num_comparacao{};

		for (auto i = std::next(in.begin()); i!=in.end(); i++)
		{
			for (auto ant = i ,p = std::prev(i);
				(num_comparacao++, (*p > *ant)); ant=p--) {
				std::swap(*p, *ant);
				if (p == in.begin()) break;
			}
		}
	
		if (!std::ranges::is_sorted(in)) __debugbreak();
		return num_comparacao;
	}
}

namespace heap {
	export uint64_t sort(std::ranges::random_access_range auto& in) {
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
	export template<typename Begin,typename End> requires std::contiguous_iterator<Begin> && std::contiguous_iterator<End>
	uint64_t sort(Begin begin,End end) {
		uint64_t num_comparacao{};
		const auto comp_contada = [&num_comparacao](const auto& i, const auto& b) {
			num_comparacao++;
			return i < b;
		};
			
		const auto size = std::distance(begin, end);

		if (size>1) {
			const auto pontomedio = std::next(begin,size/2);
			num_comparacao += merge::sort(begin,pontomedio);
			num_comparacao += merge::sort(pontomedio,end);
			std::inplace_merge(begin, pontomedio, end,comp_contada);
		}
		if (!std::is_sorted(begin,end)) __debugbreak();
		return num_comparacao;
	}
	export uint64_t sort(std::ranges::contiguous_range auto& in) {
		return merge::sort(in.begin(), in.end());
	}
}
