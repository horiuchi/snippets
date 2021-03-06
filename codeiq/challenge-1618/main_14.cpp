#include <iostream>
#include <set>

int solve(int len, std::set<int>&& set) {
	int result = 0;
	for (auto it = set.crbegin(); it != set.crend(); ++it) {
		int a = *it;
		auto it2 = it;
		++it2;
		for (; it2 != set.crend(); ++it2) {
			int b = *it2;
			if (a + b >= len) continue;
			int c = len - (a + b);
			if (c >= b) continue;

			auto f = set.find(c);
			if (f != set.end()) {
				++result;
			}
		}
	}
	return result;
}

int main() {
	int L, N;
	std::cin >> L;
	std::cin >> N;

	std::set<int> set;
	for (int i = 0; i < N; ++i) {
		int x;
		std::cin >> x;
		set.insert(x);
	}

	std::cout << solve(L, std::move(set)) << std::endl;
	return 0;
}

