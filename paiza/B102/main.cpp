#include <iostream>
#include <vector>

typedef std::vector<std::vector<bool>> Board;
typedef std::vector<bool> Ope;

void displayBoard(const Board& b) {
	for (auto it = b.begin(); it != b.end(); ++it) {
		auto line = *it;
		for (auto lit = line.begin(); lit != line.end(); ++lit) {
			std::cout << (*lit ? '#' : '.');
		}
		std::cout << std::endl;
	}
}

bool resolveMark(const Board& b, bool ope, int i, int j) {
	if (b[i][j] == ope) {
		return ope;
	}
	if (i > 0 && b[i - 1][j] == ope) {
		return ope;
	}
	if (i < b.size() - 1 && b[i + 1][j] == ope) {
		return ope;
	}
	if (j > 0 && b[i][j - 1] == ope) {
		return ope;
	}
	if (j < b[i].size() - 1 && b[i][j + 1] == ope) {
		return ope;
	}
	return !ope;
}

Board resolve(const Board& b, const Ope& ope) {
	Board prev = b;
	Board result = b;
	for (auto it = ope.begin(); it != ope.end(); ++it) {
		for (int i = 0; i < b.size(); i++) {
			const auto& line = b[i];
			for (int j = 0; j < line.size(); j++) {
				result[i][j] = resolveMark(prev, *it, i, j);
				// std::cout << *it << ": " << i << "," << j << "=" << result[i][j] << std::endl;
			}
		}
		prev = result;
	}
	return std::move(result);
}

int main(int argc, char *argv[]) {
	int H, W, N;
	std::cin >> H;
	std::cin >> W;
	std::cin >> N;

	Board b;
	for (int i = 0; i < H; i++) {
		std::vector<bool> line = std::vector<bool>();
		for (int j = 0; j < W; j++) {
			char c;
			std::cin >> c;
			line.push_back(c == '#');
		}
		b.push_back(line);
	}

	Ope ope;
	for (int i = 0; i < N; i++) {
		char c;
		std::cin >> c;
		ope.push_back(c == 'D');
	}

	// displayBoard(b);
	Board ans = resolve(b, ope);
	displayBoard(ans);

	return 0;
}

