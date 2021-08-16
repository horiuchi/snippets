#include <algorithm>
#include <iostream>
#include <vector>

int main(void){
	int N, K;
	std::cin >> N;
	std::cin >> K;

	int min = -1;
	std::vector<int> result;
	for (int i = 0; i < N; ++i) {
		int t;
		std::cin >> t;

		int n = t - K;
		if (n < 0) {
			n *= -1;
		}

		if (min < 0 || n < min) {
			min = n;
			result.clear();
			result.push_back(t);
		} else if (n == min) {
			result.push_back(t);
		}
	}

	std::sort(result.begin(), result.end());
	for (auto it = result.cbegin(); it != result.cend(); ++it) {
		std::cout << *it << std::endl;
	}

    return 0;
}

