#include <iostream>

int resolve(int const input) {
	if (input % 2 == 0) return 0;
	return ((1999999 / input) + 1) / 2;
}

int main(int argc, char *argv[]) {
	int line;
	while (std::cin >> line) {
		std::cout << resolve(line) << std::endl;
	}
	return 0;
}

