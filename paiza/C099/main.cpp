#include <iostream>

int main(void) {
	int D, N;
	std::cin >> N;
	std::cin >> D;

	int len = D;
	for (int i = 1; i < N; ++i) {
		int d;
		std::cin >> d;

		len += D - d;
	}

	std::cout << D * len << std::endl;
	return 0;
}

