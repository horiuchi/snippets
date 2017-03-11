#include <iostream>
#include <string>
#include <map>

int main() {
	int n;
	std::cin >> n;
	std::map<std::string, int> map;
	for (int i = 0; i < n; ++i) {
		std::string s;
		int p;
		std::cin >> s;
		std::cin >> p;
		map.emplace(s, p);
	}

	auto max = map.cend();
	int sum = 0;
	for (auto it = map.cbegin(), end = map.cend(); it != end; ++it) {
		int value = it->second;
		sum += value;
		if (max == map.end()) {
			max = it;
		} else if (max->second < value) {
			max = it;
		}
	}

	if (max->second > (sum / 2)) {
		std::cout << max->first << std::endl;
	} else {
		std::cout << "atcoder" << std::endl;
	}
	return 0;
}

