#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<char>> Board;
typedef std::vector<std::pair<int, int>> Result;

void displayBoard(const Board& b) {
	for (auto it = b.begin(); it != b.end(); ++it) {
		auto line = *it;
		for (auto lit = line.begin(); lit != line.end(); ++lit) {
			std::cout << *lit << ' ';
		}
		std::cout << std::endl;
	}
}

bool checkWord(const Board& b, const std::string& w, int y, int x) {
	for (int i = 0, max = w.length(); i < max; i++) {
		if (w[i] != b[y + i][x + i]) {
			return false;
		}
	}
	return true;
}
bool findWord(const Board& b, const std::string& w, std::pair<int, int>& output) {
	int wLength = w.length();
	for (int y = 0, yMax = b.size() - wLength + 1; y < yMax; y++) {
		auto line = b[y];
		for (int x = 0, xMax = line.size() - wLength + 1; x < xMax; x++) {
			if (checkWord(b, w, y, x)) {
				output = std::pair<int, int>(x, y);
				return true;
			}
		}
	}
	return false;
}

Result resolve(const Board& b, const std::vector<std::string>& w) {
	Result result;
	for (int i = 0; i < w.size(); i++) {
		auto s = w[i];
		std::pair<int, int> output;
		if (findWord(b, s, output)) {
			result.push_back(output);
		}
	}
	return result;
}

int main(int argc, char *argv[]) {
	int N, M;
	std::cin >> N;
	std::cin >> M;

	Board b;
	for (int i = 0; i < N; i++) {
		std::vector<char> line = std::vector<char>();
		for (int j = 0; j < N; j++) {
			char c;
			std::cin >> c;
			line.push_back(c);
		}
		b.push_back(line);
	}

	std::string dummy;
	std::getline(std::cin, dummy);

	std::vector<std::string> words;
	for (int i = 0; i < M; i++) {
		std::string w;
		std::getline(std::cin, w);
		words.push_back(w);
	}

	// displayBoard(b);
	Result result = resolve(b, words);
	for (auto it = result.begin(); it != result.end(); ++it) {
		std::cout << it->first + 1 << ' ' << it->second + 1 << std::endl;
	}

	return 0;
}

