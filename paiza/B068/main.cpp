#include <iostream>
#include <vector>

template<typename T>
using Board = std::vector<std::vector<T>>;

bool solve(const Board<int>& board, Board<char>& result) {
	for (const auto row: board) {
		int sum = 0;
		for (const auto item: row) {
			sum += item;
		}
		if (sum % 2 != 0) {
			return false;
		}

		sum /= 2;
		int sumA = 0;
		for (int i = 0; i < row.size(); i++) {
			sumA += row[i];
			if (sum == sumA) {
				std::vector<char> line;
				for (int j = 0; j < row.size(); j++) {
					line.push_back(j <= i ? 'A' : 'B');
				}
				result.push_back(line);
				break;
			} else if (sum < sumA) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
void output(const Board<T>& cc) {
	for (const auto row: cc) {
		for (const auto item: row) {
			std::cout << item;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	int H, W;
	std::cin >> H;
	std::cin >> W;

	Board<int> board;
	for (int i = 0; i < H; i++) {
		board.push_back(std::vector<int>());
		for (int j = 0; j < W; j++) {
			int n;
			std::cin >> n;
			board[i].push_back(n);
		}
	}
	// output(board);

	Board<char> result;
	bool b = solve(board, result);
	if (b) {
		std::cout << "Yes" << std::endl;
		output(result);
	} else {
		std::cout << "No" << std::endl;
	}

	return 0;
}

