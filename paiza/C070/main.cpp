#include <iostream>
#include <map>
#include <string>

std::string judge(std::string input) {
	std::map<char, int> map;
	for (int j = 0; j < 4; j++) {
		map[input[j]]++;
	}

	int max = 0;
	for (auto it = map.cbegin(); it != map.cend(); ++it) {
		int value = it->second;
		if (max < value) {
			max = value;
		}
	}

	switch (max) {
		case 4:
			return "Four Card";
		case 3:
			return "Three Card";
		case 2:
			if (map.size() == 2) {
				return "Two Pair";
			} else {
				return "One Pair";
			}
		default:
			return "No Pair";
	}
}

int main(void){
    int N;
    std::cin >> N;

	std::string line;
	std::getline(std::cin, line);
	for (int i = 0; i < N; i++) {
		std::getline(std::cin, line);

		std::cout << judge(std::move(line)) << std::endl;
	}
    return 0;
}

