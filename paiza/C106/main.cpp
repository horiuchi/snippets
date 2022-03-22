#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

using Data = std::pair<int, int>;
using V = std::vector<Data>;
using SS = std::vector<std::string>;

int main(void) {
	int N;
	std::cin >> N;

	V v;
	for (int i = 0; i < N; ++i) {
		int n;
		std::cin >> n;

		Data d = std::make_pair(i, n);
		v.push_back(d);
	}

	std::sort(v.begin(), v.end(), [](Data& a, Data& b) {
		return a.second > b.second;
	});

	SS ss(N);

	int rank = -1;
	int count = 0;
	int value = 0;
	for (auto& d : v) {
		if (value != d.second) {
			rank++;
			if (rank == 1) {
				if (count == 2) {
					rank = 2;
				} else if (count > 2) {
					rank = 3;
				}
			} else if (rank == 2) {
				if (count > 3) {
					rank = 3;
				}
			}
		}
		count++;
		value = d.second;

		switch (rank) {
			case 0:
				ss[d.first] = "G";
				break;
			case 1:
				ss[d.first] = "S";
				break;
			case 2:
				ss[d.first] = "B";
				break;
			default:
				ss[d.first] = "N";
				break;
		}
	}

	for (auto& s : ss) {
		std::cout << s << std::endl;
	}

	return 0;
}

