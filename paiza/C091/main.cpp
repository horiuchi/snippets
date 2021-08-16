#include <iostream>

int check(int N, int n) {
	int res = 1;
	while (n >= N * res + N / 2) {
		res++;
	}
	return res;
}

int main(void){
	int N, M;
	std::cin >> N;
	std::cin >> M;

	for (int i = 0; i < M; ++i) {
		int n;
		std::cin >> n;
		int res = check(N, n);
		std::cout << N * res << std::endl;
	}

    return 0;
}

