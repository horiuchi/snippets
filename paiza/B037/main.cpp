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


Array convertInput(const int M, const int D) {
	Array input;
	input[0] = M / 10;
	input[1] = M % 10;
	input[2] = D / 10;
	input[3] = D % 10;
	std::sort(std::begin(input), std::end(input));
	return input;
}

bool checkNumbers(Array const& input, Array x) {
	for (int i = 0; i < 4; i++) {
		x[i] = x[i] % 10;
	}
	std::sort(std::begin(x), std::end(x));
	return std::equal(std::begin(input), std::end(input), std::begin(x));
}

Array calcNumbers(Array const& a, Array const& b, Array const& m, Array const& x) {
	Array output;
	for (int i = 0; i < 4; i++) {
		output[i] = (a[i] * x[i] + b[i]) % m[i];
	}
	return output;
}


int main(int argc, char *argv[]) {
	int M, D;
	Array a, b, m;

	std::cin >> M;
	std::cin >> D;
	for (int i = 0; i < 4; i++) {
		std::cin >> a[i];
	}
	for (int i = 0; i < 4; i++) {
		std::cin >> b[i];
	}
	for (int i = 0; i < 4; i++) {
		std::cin >> m[i];
	}

	Array input = convertInput(M, D);

	const int max = 10000;
	Array x{0, 0, 0, 0};
	for (int i = 1; i <= max; i++) {
		Array next = calcNumbers(a, b, m, x);
		if (checkNumbers(input, next)) {
			std::cout << i << std::endl;
			break;
		}
		x = next;
	}
	return 0;
}

