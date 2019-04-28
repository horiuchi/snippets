#include <iostream>
#include <vector>

const bool debug = false;

const int len = 8;
const char blank = '_';
const char white = 'W';
const char black = 'B';
using board = std::vector<char>;

int toIndex(int x, int y) {
	return (y - 1) * len + (x - 1);
}

board createBoard() {
	board b(len * len, blank);
	b[toIndex(4, 4)] = white;
	b[toIndex(5, 4)] = black;
	b[toIndex(4, 5)] = black;
	b[toIndex(5, 5)] = white;
	return b;
}

void flip(board& b, char t, int x, int y, int dx, int dy) {
	char opo = t == white ? black : white;
	int found = 0;
	for (int i = 1; i < 8; i++) {
		int xx = x + dx * i;
		if (xx < 1 || 8 < xx) {
			break;
		}
		int yy = y + dy * i;
		if (yy < 1 || 8 < yy) {
			break;
		}
		char c = b[toIndex(xx, yy)];
		if (c == opo) {
			continue;
		} else if (c == t) {
			found = i;
			break;
		} else {
			break;
		}
	}
	// if (found > 1) std::cout << t << ' ' << x << ' ' << y << ',' << found << std::endl;
	for (int i = 1; i < found; i++) {
		int xx = x + dx * i;
		int yy = y + dy * i;
		b[toIndex(xx, yy)] = t;
	}
}
void turn(board& b, char t, int x, int y) {
	int index = toIndex(x, y);
	b[index] = t;
	flip(b, t, x, y, 0, -1);
	flip(b, t, x, y, 1, -1);
	flip(b, t, x, y, 1, 0);
	flip(b, t, x, y, 1, 1);
	flip(b, t, x, y, 0, 1);
	flip(b, t, x, y, -1, 1);
	flip(b, t, x, y, -1, 0);
	flip(b, t, x, y, -1, -1);
}

int count(const board& b, char t) {
	int res = 0;
	for (const auto& c : b) {
		if (c == t) res++;
	}
	return res;
}

void print(const board& b) {
	if (!debug) {
		return;
	}
	int i = 0;
	for (const auto& c : b) {
		std::cout << c;
		if (++i >= len) {
			std::cout << std::endl;
			i = 0;
		}
	}
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	int N;
	std::cin >> N;
	board b = createBoard();

	print(b);
	for (int i = 0; i < N; i++) {
		char t;
		int x, y;
		std::cin >> t;
		std::cin >> x;
		std::cin >> y;
		turn(b, t, x, y);
		print(b);
	}
	print(b);

	int bc = count(b, black);
	int wc = count(b, white);
	printf("%02d-%02d ", bc, wc);
	if (bc == wc) {
		printf("Draw!\n");
	} else if (bc > wc) {
		printf("The black won!\n");
	} else {
		printf("The white won!\n");
	}

	return 0;
}

