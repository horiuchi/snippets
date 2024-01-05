#include <iostream>
#include <string>
#include <vector>

template<typename T>
using BOARD = std::vector<std::vector<T>>;

int main(void) {
	int H, W;
	std::cin >> H;
	std::cin >> W;

	BOARD<bool> s = std::vector<std::vector<bool>>(H);

	std::string line;
	std::getline(std::cin, line);
	for (int i = 0; i < H; i++) {
		auto& row = s[i];
		row = std::vector<bool>(W);

		std::getline(std::cin, line);
		for (int j = 0; j < W; j++) {
			row[j] = (line[j] == 'o');
		}
	}

	int p;
	int sum = 0;
	for (int i = 0; i < H; i++) {
		auto& row = s[i];
		for (int j = 0; j < W; j++) {
			std::cin >> p;
			if (row[j]) {
				sum += p;
			}
		}
	}
	std::cout << sum << std::endl;

	return 0;
}

