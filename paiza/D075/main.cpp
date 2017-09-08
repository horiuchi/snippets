#include <iostream>
#include <set>

void removeNumber(std::set<int>& set, int number) {
	set.erase(number);
}

int main(int argc, char *argv[]) {
	std::set<int> set;
	for (int i = 1; i <= 5; ++i) {
		set.insert(i);
	}

	int n;
	for (int i = 0; i < 4; ++i) {
		std::cin >> n;
		removeNumber(set, n);
	}
	std::cout << *set.begin() << std::endl;
	return 0;
}

