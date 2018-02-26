#include <iostream>

int main(int argc, char *argv[]) {
	int N;
	std::cin >> N;

	int x = 1;
	int result = 0;
	for (int i = 0; i < N; i++) {
		int f;
		std::cin >> f;
		int count = f - x;
		if (count < 0) {
			count *= -1;
		}
		result += count;
		x = f;
	}
	std::cout << result << std::endl;
	return 0;
}

