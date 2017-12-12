#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
	std::string S, T;

	std::cin >> S;
	for (int i = 0; i < 10; i++) {
		std::cin >> T;
		if (S == T) {
			std::cout << "YES" << std::endl;
			return 0;
		}
	}
	std::cout << "NO" << std::endl;
	return 0;
}

