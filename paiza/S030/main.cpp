#include <iostream>
#include <vector>

using vi = std::vector<int>;

void searchPeek(const vi& input, int m, vi& index) {
	for (int i = 1, n = input.size() - 1; i < n; i++) {
		int v = input[i];
		if (v >= m && input[i - 1] < v && v > input[i + 1]) {
			index.push_back(i);
			// std::cout << i << ": " << v << std::endl;
		}
	}
}

bool checkProminence(const vi& input, int m, int index) {
	int v = input[index];
	int lift = v - m;

	for (int i = index - 1; i > 0; i--) {
		int a = input[i];
		if (a - lift <= 0) {
			break;
		}
		if (a >= v) {
			return false;
		}
	}
	for (int i = index + 1, n = input.size(); i < n; i++) {
		int a = input[i];
		if (a - lift <= 0) {
			break;
		}
		if (a >= v) {
			return false;
		}
	}
	return true;
}

int resolve(const vi& input, int m) {
	vi index;
	searchPeek(input, m, index);

	int result = 0;
	for (int i = 0, n = index.size(); i < n; i++) {
		if (checkProminence(input, m, index[i])) {
			result++;
		}
	}
	return result;
}

int main(int argc, char *argv[]) {
	int N, M;
	std::cin >> N;
	std::cin >> M;
	vi input(N);
	for (int i = 0; i < N; i++) {
		int x;
		std::cin >> x;
		input[i] = x;
	}

	int answer = resolve(input, M);
	std::cout << answer << std::endl;

	return 0;
}

