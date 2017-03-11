#include <iostream>
#include <string>

int main() {
	std::string s;
	std::cin >> s;
	if (s[0] == s[1] && s[0] == s[2] && s[0] == s[3]) {
		std::cout << "SAME" << std::endl;
	} else {
		std::cout << "DIFFERENT" << std::endl;
	}
	return 0;
}

