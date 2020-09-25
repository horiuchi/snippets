#include <iostream>

int main(void){
	std::string S;
	std::getline(std::cin, S);

	int n = S.size();
	for (int i = 0; i < n + 2; ++i) {
		std::cout << "+";
	}
	std::cout << std::endl;

	std::cout << "+" << S << "+" << std::endl;

	for (int i = 0; i < n + 2; ++i) {
		std::cout << "+";
	}
	std::cout << std::endl;

    return 0;
}

