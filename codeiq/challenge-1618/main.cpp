#include <iostream>
#include <set>

typedef std::set<int>::const_iterator Iterator;
typedef std::set<int>::reverse_iterator RIterator;

int solve(int len, const std::set<int>& set) {
	int result = 0;
	for (RIterator it = set.rbegin(); it != set.rend(); ++it) {
		int a = *it;
		RIterator it2 = it;
		++it2;
		for (; it2 != set.rend(); ++it2) {
			int b = *it2;
			if (a + b >= len) continue;
			int c = len - (a + b);
			if (c >= b) continue;

			Iterator f = set.find(c);
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

	std::cout << solve(L, set) << std::endl;
	return 0;
}

