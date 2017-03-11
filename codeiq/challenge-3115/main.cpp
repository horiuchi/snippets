#include <algorithm>
#include <array>
#include <iostream>

typedef std::array<int, 4> Array;

template <class T, std::size_t N>
std::ostream& operator<<(std::ostream& o, const std::array<T, N>& arr)
{
	std::copy(arr.cbegin(), arr.cend(), std::ostream_iterator<T>(o, " "));
    return o;
}

Array convertInput(int input) {
	Array result;
	for (int i = 3; i >= 0; --i) {
		result[i] = input % 10;
		input /= 10;
	}
	return result;
}

int resolve(Array const& input) {
	Array x = input;
	std::sort(std::begin(x), std::end(x));
	if (x[0] == 0) {
		return x[1];
	} else {
		return x[3];
	}
}

int main(int argc, char *argv[]) {
	int line;
	while (std::cin >> line) {
		Array a = convertInput(line);
		std::cout << resolve(a) << std::endl;
	}
	return 0;
}

