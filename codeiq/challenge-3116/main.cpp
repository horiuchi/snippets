#include <cstdlib>
#include <iostream>
#include <string>


std::string resolve(std::string const& input) {
	std::string result = input;
	for (int i = 0; i < result.length() - 1; ) {
		if (std::abs(result[i] - result[i+1]) == 1) {
			result.erase(i, 2);
			i -= 1;
			if (i < 0) i = 0;
		} else {
			i++;
		}
	}
	return result;
}

int main(int argc, char *argv[]) {
	std::string line;
	while (std::cin >> line) {
		std::cout << resolve(line) << std::endl;
	}
	return 0;
}

