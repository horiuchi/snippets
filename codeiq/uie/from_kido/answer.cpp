#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

#include <boost/rational.hpp>

using rational = boost::rational<unsigned long long int>;

void answer1(const int n = 365) {
	using container = std::vector<std::tuple<int, rational>>;

	container cont = {std::make_tuple(1, rational(1, 1))};
	for (int i = 1; i < n * 3; ++i) {
		container next;
		rational result = 0;
		for (const auto v : cont) {
			auto m = std::get<0>(v);
			if (m >= n) {
				result += std::get<1>(v);
			} else {
				// pattern 1: found target.
				next.emplace_back(m + 1, std::get<1>(v) * rational(n - m, n));
			}
			// pattern 2: target not found.
			next.emplace_back(m, std::get<1>(v) * rational(m, n));
		}
		std::cout << i << ": " << result << std::endl;
		cont = next;
	}
}

rational calcBase(const int n) {
	rational result = rational(1, 1);
	for (int i = 1; i < n; ++i) {
		result *= rational(n - i, n);
	}
	return std::move(result);
}
rational power(const rational& base, const int exp) {
	rational res = 1;
	for (int i = 0; i < exp; ++i) {
		res *= base;
	}
	return res;
}
std::vector<rational> calcAdditional(const int n, const int m, const int k) {
	std::vector<rational> result;
	if (m == 1) {
		result.push_back(power(rational(1, n), k));
	} else {
		for (int i = 0; i <= k; ++i) {
			rational x = power(rational(m, n), i);
			int rest = k - i;
			std::vector<rational> add = calcAdditional(n, m - 1, rest);
			result.reserve(result.size() + add.size());
			for (auto y : add) {
				result.push_back(x * y);
			}
		}
	}
	return std::move(result);
}
void answer2(const int n = 365) {
	std::cout << "answer2 start." << std::endl;
	rational base = calcBase(n);

	for (int i = 0; true; ++i) {
		std::vector<rational> additional = calcAdditional(n, n, i);
		rational sum = 0;
		for (auto x : additional) {
			sum += x;
		}
		rational result = base * sum;

		std::cout << (n + i) << ": " << result << " (" << boost::rational_cast<double>(result) << ")" << std::endl;
		if (result >= rational(1, 2)) {
			std::cout << "answer2 end." << std::endl;
			break;
		}
	}
}

double calcBaseD(const int n) {
	double result = 1.0;
	for (int i = 1; i < n; ++i) {
		result *= double(n - i) / n;
	}
	return result;
}
std::vector<double> calcAdditionalD(const int n, const int m, const int k) {
	std::vector<double> result;
	if (m == 1) {
		result.push_back(std::pow(1.0 / n, k));
	} else {
		for (int i = 0; i <= k; ++i) {
			double x = std::pow(double(m) / n, i);
			int rest = k - i;
			std::vector<double> add = calcAdditionalD(n, m - 1, rest);
			result.reserve(result.size() + add.size());
			for (auto y : add) {
				result.push_back(x * y);
			}
		}
	}
	return std::move(result);
}
void answer3(const int n = 365) {
	std::cout << "answer3 start." << std::endl;
	double base = calcBaseD(n);

	for (int i = 0; true; ++i) {
		std::vector<double> additional = calcAdditionalD(n, n, i);
		double sum = 0;
		for (auto x : additional) {
			sum += x;
		}
		double result = base * sum;

		std::cout << (n + i) << ": " << result << std::endl;
		if (result >= 0.5) {
			std::cout << "answer3 end." << std::endl;
			break;
		}
	}
}


int main() {
	int n = 3;
	for (int i = 3; i <= 10; ++i) {
		std::cout << i << ":" << std::endl;
		answer1(i);
	}
	//answer2(n);
	//answer3(n);
}

