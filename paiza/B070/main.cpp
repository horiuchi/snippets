#include <iostream>
#include <vector>

template <typename Tlist, typename Tfunc>
void __combination(Tlist const& list, typename Tlist::size_type const n, Tfunc const& func,
		Tlist& tmp, typename Tlist::size_type const i, typename Tlist::size_type const j) {
    if (i == n) {
        func(tmp);
        return;
    }

    for (typename Tlist::size_type k = j; k != list.size() + (1 + i- n); ++k) {
        tmp[i] = list[k];
        __combination(list, n, func, tmp, i + 1, k + 1);
    }
}

template <typename Tlist, typename Tfunc>
void combination(Tlist const& list, typename Tlist::size_type const n, Tfunc const& func) {
    Tlist tmp(n);
    __combination(list, n, func, tmp, 0, 0);
}


int separate(int max, std::vector<int> const& list, int index, int left, int right) {
	if (index == list.size()) {
		if (left == right && left + right <= max) {
			return left + right;
		} else {
			return 0;
		}
	}
	int x = list[index];
	int l = separate(max, list, index + 1, left + x, right);
	int r = separate(max, list, index + 1, left, right + x);
	return l > r ? l : r;
}


int resolve(int max, std::vector<int> weights) {
	int result = 0;

	for (size_t n = 2; n <= weights.size(); n++) {
		combination(weights, n, [max, &result](std::vector<int> const& a) {
			//  for (auto it(a.cbegin()); it != a.cend(); ++it) {
			//  	std::cout << (*it) << ",";
			//  }
			//  std::cout << std::endl;
			int x = separate(max, a, 1, a[0], 0);
			if (result < x) {
				result = x;
			}
		});
	}

	return result;
}

int main(int argc, char *argv[]) {
	int N, M;
	std::cin >> N;
	std::cin >> M;

	std::vector<int> weights;
	for (int i = 0; i < N; i++) {
		int x;
		std::cin >> x;
		weights.push_back(x);
	}

	int result = resolve(M, std::move(weights));
	std::cout << result << std::endl;

	return 0;
}

