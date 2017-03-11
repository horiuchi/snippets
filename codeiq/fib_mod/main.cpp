#include <iostream>
#include <vector>

typedef std::vector<int> cache_vector;
static cache_vector cache;

void initialize() {
	if (cache.empty()) {
		cache.push_back(0);
		cache.push_back(1);
		cache.push_back(1);
	}
}

int fib_mod(int n) {
	if (n < 0) {
		return 0;
	}
	if (n < cache.size()) {
		return cache[n];
	}
	for (int i = cache.size(); i <= n; ++i) {
		cache.push_back((cache[i - 2] + cache[i - 1]) % 1000);
	}
	return cache[n];
}


int main(int argc, char *argv[]) {
	int N;
	std::cin >> N;
	std::vector<int> input;
	for (int i = 0; i < N; ++i) {
		int n;
		std::cin >> n;
		input.push_back(n);
	}

	initialize();

	for (const int n : input) {
		std::cout << fib_mod(n % 1500) << std::endl;
	}
}

