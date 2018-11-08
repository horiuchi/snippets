#include <iostream>
#include <string>

bool check(const std::string& base, const std::string& s, int index) {
	for (int i = 1; i < index; i++) {
		if (base[base.size() - 1 - index + i] != s[i]) {
			return false;
		}
	}
	return true;
}

void append(std::string& base, const std::string& s) {
	for (int i = 0; i < s.size(); i++) {
		if (i >= base.size()) {
			break;
		}
		if (base[base.size() - 1 - i] == s[0]) {
			if (check(base, s, i)) {
				base += s.substr(i + 1);
				return;
			}
		}
	}
	base += s;
}

int main(int argc, char *argv[]) {
	int N;
	std::cin >> N;

	std::string line;
	std::getline(std::cin, line);

	std::string result;
	for (int i = 0; i < N; i++) {
		std::getline(std::cin, line);
		append(result, line);
	}
	std::cout << result << std::endl;

	return 0;
}

