#include <iostream>
#include <string>

bool check(std::string const& S, std::string const& T, size_t index) {
	int si = 1;
	int skip = 0;
	for (size_t i = index + 1; i < T.size(); i++) {
		if (S[si] == T[i]) {
			si++;
			if (si == S.size()) {
				return true;
			}
		} else {
			if (skip == 0) {
				skip++;
			} else {
				return false;
			}
		}
	}
	return false;
}
bool solve(std::string const& S, std::string const& T) {
	for (size_t i = 0; i < T.size(); i++) {
		if (T[i] == S[0]) {
			if (check(S, T, i)) {
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char *argv[]) {
	int N;
	std::cin >> N;

	std::string S;
	std::cin >> S;

	for (int i = 0; i < N; i++) {
		std::string T;
		std::cin >> T;
		const bool result = solve(S, T);
		if (result) {
			std::cout << "valid" << std::endl;
		} else {
			std::cout << "invalid" << std::endl;
		}
	}

	return 0;
}

