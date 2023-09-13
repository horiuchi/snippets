#include <iostream>

int main(void) {
	int N;
	std::cin >> N;

	int x = 0;
	int dx = 0;
	int y = 0;
	int dy = 0;
	int prev;
	std::cin >> prev;
	for (int i = 1; i < N; ++i) {
		int n;
		std::cin >> n;

		if (prev > n) {
			if (dy > 0) {
				if (y < dy) {
					y = dy;
				}
				dy = 0;
			}
			dx++;
		}
		if (prev < n) {
			if (dx > 0) {
				if (x < dx) {
					x = dx;
				}
				dx = 0;
			}
			dy++;
		}
		prev = n;
	}
	if (dx > x) {
		x = dx;
	}
	if (dy > y) {
		y = dy;
	}

	std::cout << x << " " << y << std::endl;
	return 0;
}

