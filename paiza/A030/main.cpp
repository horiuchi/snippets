#include <iostream>
#include <vector>

using vi = std::vector<int>;

void resolve(const vi& input, vi& result) {
	for (int i = 1, n = input.size(); i < n; i++) {
		int a = input[i];
		int count = 1 + result[i];
		while (a != 1) {
			result[a - 1] += count;
			a = input[a - 1];
		}
	}
}

void print(const vi& v) {
	for (const auto& i : v) {
		std::cout << i << std::endl;
	}
}

int main(int argc, char *argv[]) {
	int N;
	std::cin >> N;
	vi answer(N, 0);
	answer[0] = N - 1;
	vi input(N);
	for (int i = 1; i < N; i++) {
		int x;
		std::cin >> x;
		input[i] = x;
	}

	resolve(input, answer);
	print(answer);

	return 0;
}

