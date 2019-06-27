#include <cmath>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
	int N;
	std::cin >> N;

	int min = 0;
	int max = 100;
	std::vector<int> divs;
	for (int i = 0; i < N; i++) {
		char c;
		int n;
		std::cin >> c;
		std::cin >> n;

		switch (c) {
			case '>':
				min = std::max(min, n);
				break;
			case '<':
				max = std::min(max, n);
				break;
			case '/':
				divs.push_back(n);
				break;
		}
	}

	for (int i = min + 1; i < max; i++) {
		bool check = true;
		for (const auto n : divs) {
			if (i % n != 0) {
				check = false;
			}
		}
		if (check) {
			std::cout << i << std::endl;
			return 0;
		}
	}
	return 0;
}

