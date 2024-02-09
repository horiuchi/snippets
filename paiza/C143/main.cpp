#include <iostream>
#include <string>

int main(void) {
	std::string S;
	std::getline(std::cin, S);

	bool prev = false;
	for (auto it = S.begin(); it != S.end(); ++it) {
		const auto c = *it;
		if (c == '-') {
			if (prev) {
				continue;
			}
			prev = true;
		} else {
			prev = false;
		}
		std::cout << c;
	}
	std::cout << std::endl;
	return 0;
}

