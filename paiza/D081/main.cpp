#include <iostream>

int main(int argc, char *argv[]) {
	int N, H, W;

	std::cin >> N;
	std::cin >> H;
	std::cin >> W;
	std::cout << (H * W) % N << std::endl;
	return 0;
}

