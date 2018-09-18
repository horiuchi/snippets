#include <iostream>

int main(int argc, char *argv[]) {
	int N, M;
	std::cin >> N;
	std::cin >> M;

	for (int i = 0; i < N; i++) {
		int a, b;
		std::cin >> a;
		std::cin >> b;

		a -= b * 5;
		if (a < 0) {
			a = 0;
		}
		if (a >= M) {
			std::cout << (i + 1) << std::endl;
		}
	}
	return 0;
}

