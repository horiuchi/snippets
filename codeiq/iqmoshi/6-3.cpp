#include <algorithm>
#include <array>
#include <iostream>

typedef std::array<int, 10> Pins;

bool checkSums(const Pins& data) {
	int a = data[0] + data[1] + data[3] + data[6];
	int b = data[0] + data[2] + data[5] + data[9];
	int c = data[6] + data[7] + data[8] + data[9];
	return a == b && b == c;
}

int main() {
	Pins data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	int count = 0;
	do {
		if (checkSums(data)) {
			count++;
		}
	} while (std::next_permutation(data.begin(), data.end()));
	std::cout << "count=" << count << std::endl;

	return 0;
}

