#include <cmath>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Board;
typedef std::vector<std::pair<int, int>> Route;

void displayBoard(const Board& b) {
	for (auto it = b.begin(); it != b.end(); ++it) {
		auto line = *it;
		for (auto lit = line.begin(); lit != line.end(); ++lit) {
			std::cout << *lit << ' ';
		}
		std::cout << std::endl;
	}
}

int resolve(const Board& b, const Route& r) {
	int index = 0;
	int result = 0;
	for (auto it = r.begin(); it != r.end(); ++it) {
		auto way = *it;
		int i = way.first;
		int j = way.second;
		if (index == j) {
			continue;
		}

		result += abs( b[i][j] - b[i][index] );
		index = j;
	}
	return result;
}

int main(int argc, char *argv[]) {
	int N, M;
	std::cin >> N;
	std::cin >> M;

	Board b;
	for (int i = 0; i < N; i++) {
		std::vector<int> line = std::vector<int>();
		for (int j = 0; j < M; j++) {
			int c;
			std::cin >> c;
			line.push_back(c);
		}
		b.push_back(line);
	}

	int X;
	std::cin >> X;

	Route r;
	for (int i = 0; i < X; i++) {
		int R, S;
		std::cin >> R;
		std::cin >> S;
		auto p = std::make_pair(R - 1, S - 1);
		r.push_back(p);
	}

	// displayBoard(b);
	int ans = resolve(b, r);
	std::cout << ans << std::endl;

	return 0;
}

