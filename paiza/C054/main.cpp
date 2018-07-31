#include <iostream>

int main(int argc, char *argv[]) {
	int N, V;
	std::cin >> N;
	std::cin >> V;

	int prev_t, prev_p;
	for (int i = 0; i < N; i++) {
		int t, p;
		std::cin >> t;
		std::cin >> p;

		if (i > 0) {
			int v = (p - prev_p) / (t - prev_t);
			if (v > V) {
				std::cout << "YES" << std::endl;
				return 0;
			}
		}

		prev_t = t;
		prev_p = p;
	}
	std::cout << "NO" << std::endl;
	return 0;
}

