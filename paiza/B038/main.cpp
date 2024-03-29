#include <cmath>
#include <iostream>

void resolve(const int a, const int b, const int c, const int d, int& x, int& y) {
	if (c == d) {
		if (b == 2) {
			x = 1;
			y = 1;
		} else {
			x = 0;
			y = 0;
		}
	} else if (c < d) {
		int l = a - b * c;
		y = l / (d - c);
		x = b - y;
	} else {
		int l = a - b * d;
		x = l / (c - d);
		y = b - x;
	}
}

int main(int argc, char *argv[]) {
	int a, b, c, d;
	std::cin >> a;
	std::cin >> b;
	std::cin >> c;
	std::cin >> d;

	int x, y;
	resolve(a, b, c, d, x, y);

	if (x <= 0 || y <= 0) {
		std::cout << "miss" << std::endl;
	} else {
		std::cout << x << " " << y << std::endl;
	}
	return 0;
}

