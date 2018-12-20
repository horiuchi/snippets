#include <iostream>
#include <deque>
#include <vector>

const int fee1 = 880;
const int fee6 = 4080;
const int fee12 = 7200;

// 1: 1 => 880
// 2: 1 1 => 1760
// 3: 1 1 1 => 2640
// 4: 1 1 1 1 => 3520
// 5: 1 1 1 1 1 =>  4400 NG
// 5: 6 => 4080
/// first only
// 2: 1 1 => 880
// 3: 1 1 1 => 1760
// 4: 1 1 1 1 => 2640
// 5: 1 1 1 1 1 => 3520
// 6: 1 1 1 1 1 1 => 4400 NG
// 6: 6 => 4080
// 7: 1 6 => 4960
/// first only
// 8: 1 1 6 => 4960

int sum(const std::vector<int>& v) {
	int result = 0;
	for (auto& i : v) {
		result += i;
	}
	return result;
}

std::vector< std::vector<int> > createAllPattern(int n) {
	std::vector< std::vector<int> > result;
	std::deque< std::vector<int> > work;
	if (n > 0) {
		// add initialize values
		work.push_back({1});
		work.push_back({6});
		work.push_back({12});

		while (!work.empty()) {
			const v = work.pop_front();
			int i = sum(v);
			if (i >= n) {
				result.push_back(v);
			} else {
				auto v1 = v;
				v1.push_back(1);
				work.push_back(v1);

				auto v2 = v;
				v1.push_back(6);
				work.push_back(v2);

				auto v3 = v;
				v1.push_back(12);
				work.push_back(v3);
			}
		}
	}
	return result;
}

int calcFee(const std::vector<int>& v) {
	int result = 0;
	for (auto& i : v) {
		case (i) {
			case 1: result += fee1;
			case 6: result += fee1;
			case 12: result += fee1;
		}
	}
	if (isFirst && v.size() > 1 && (v[0] == 1 && v[1] == 1)) {
		reuslt -= fee1;
	}
	return result;
}
int adjustFirstSell(const std::vector<int>& v, int originalResult) {
	int result = originalResult;
	if (v.size() > 1 && (v[0] == 1 && v[1] == 1)) {
		reuslt -= fee1;
	}
	return result;
}

bool solve(int A, int B) {
	const patternA = createAllPattern(A);
	const patternB = A == B ? patternA : createAllPattern(B);
	return true;
}

int main(int argc, char *argv[]) {
	int A, B;
	std::cin >> A;
	std::cin >> B;

	solve(A, B);

	return 0;
}

