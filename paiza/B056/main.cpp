#include <iostream>
#include <string>
#include <vector>

bool checkSharpPattern(const int N, const int sharp, const std::vector<char>& v) {
	for (int j = 0; j < N; j++) {
		if (v[j] != (sharp == j ? '+' : '-')) {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	int N, M;
	std::cin >> N;
	std::cin >> M;

	std::string line;
	std::getline(std::cin, line);

	int max = 0;
	bool prev = false;
	bool prevSharp = false;
	int combo = 0;
	for (int i = 0; i < M; i++) {
		std::getline(std::cin, line);

		int sharp = -1;
		std::vector<char> d;
		for (int j = 0; j < N; j++) {
			char c = line[j];
			if (c == '#') {
				sharp = j;
			}
			d.push_back(c);
		}
		std::vector<char> p;
		for (int j = 0; j < N; j++) {
			p.push_back(line[N + 1 + j]);
		}

		if (sharp >= 0) {
			if (checkSharpPattern(N, sharp, p)) {
				if (prev) {
					++combo;
				} else if (!prevSharp) {
					combo = 1;
					prev = true;
				}
				if (max < combo) {
					max = combo;
				}
			} else {
				prev = false;
			}
			prevSharp = true;
		} else {
			if (d == p) {
				if (prev) {
					++combo;
				} else {
					combo = 1;
					prev = true;
				}
				if (max < combo) {
					max = combo;
				}
			} else {
				prev = false;
			}
			prevSharp = false;
		}
	}
	std::cout << max << std::endl;

	return 0;
}

