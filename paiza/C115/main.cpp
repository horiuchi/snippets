#include <iostream>
#include <vector>

int main(void) {
	int N, M;
	std::cin >> N;
	std::cin >> M;

	int sum = 0;
	for (int i = 1; i < N; ++i) {
		int n;
		std::cin >> n;

		if (n <= M) {
			sum += n;
		}
	}

	std::cout << sum << std::endl;
	return 0;
}

