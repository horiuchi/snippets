#include <iostream>
#include <sstream>
#include <string>

int main(void) {
	std::string S;
	std::getline(std::cin, S);
	int N;
	std::cin >> N;

	std::string line;
	std::getline(std::cin, line);
	std::getline(std::cin, line);

	std::stringstream ss{line};
	std::string str;
	bool find = false;
	while (getline(ss, str, ' ')) {
		if (S == str) {
			find = true;
			break;
		}
	}

	if (find) {
		std::cout << "Yes" << std::endl;
	} else {
		std::cout << "No" << std::endl;
	}
	return 0;
}

