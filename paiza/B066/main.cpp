#include <iostream>
#include <vector>

using Piece = std::vector<std::vector<char>>;

struct Output {
	bool find;
	int y;
	int x;
	int r;

	Output(): find(false) {}
	Output(int _y, int _x, int _r): find(true), y(_y), x(_x), r(_r) {}
};
struct Result {
	std::vector<Output> outputs;
};

char get(const Piece& piece, const int r, const int i, const int j) {
	const size_t M = piece.size();
	switch (r) {
		case 0:
			return piece[i][j];
		case 1:
			return piece[M - j - 1][i];
		case 2:
			return piece[M - i - 1][M - j - 1];
		case 3:
			return piece[j][M - i - 1];
	}
	return -1;
}
bool isMatch(const Piece& board, const Piece& piece, const int y, const int x, const int r) {
	const size_t M = piece.size();
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (board[y + i][x + j] != get(piece, r, i, j)) {
				return false;
			}
		}
	}
	return true;
}
int match(const Piece& board, const Piece& piece, const int y, const int x) {
	for (int r = 0; r < 4; r++) {
		if (isMatch(board, piece, y, x, r)) {
			return r;
		}
	}
	return -1;
}
void find(Result& result, const Piece& board, const Piece& piece) {
	const size_t N = board.size();
	const size_t M = piece.size();
	for (int y = 0; y < N; y += M) {
		for (int x = 0; x < N; x += M) {
			const auto r = match(board, piece, y, x);
			if (r >= 0) {
				result.outputs.push_back(Output(y, x, r));
				return;
			}
		}
	}
	result.outputs.push_back(Output());
}

void debug(const Piece& cc) {
	std::cout << "DEBUG:" << std::endl;
	for (const auto row: cc) {
		for (const auto item: row) {
			std::cout << item;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	int X, N, M;
	std::cin >> X;
	std::cin >> N;
	std::cin >> M;

	Piece board;
	std::vector<Piece> pieces;

	for (int i = 0; i < N; i++) {
		board.push_back(std::vector<char>());
		for (int j = 0; j < N; j++) {
			char c;
			std::cin >> c;
			board[i].push_back(c);
		}
	}
	for (int i = 0; i < X; i++) {
		pieces.push_back(Piece());
		for (int j = 0; j < M; j++) {
			pieces[i].push_back(std::vector<char>());
			for (int k = 0; k < M; k++) {
				char c;
				std::cin >> c;
				pieces[i][j].push_back(c);
			}
		}
	}

	Result result;
	for (const auto p: pieces) {
		find(result, board, p);
	}
	for (const auto output: result.outputs) {
		if (output.find) {
			std::cout << (output.y + 1) << " " << (output.x + 1) << " " << output.r << std::endl;
		} else {
			std::cout << -1 << std::endl;
		}
	}

	return 0;
}

