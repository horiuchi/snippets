#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using Field = std::vector< std::vector<int> >;
typedef unsigned long ulong;

struct Space {
	int x;
	int y;
	int h;
};

class G {
private:
	ulong _a, _b, _c, _d, _t;

public:
	G(ulong a, ulong b, ulong c, ulong d): _a(a), _b(b), _c(c), _d(d), _t(0) {}

	Space gen(const int W, const int H) {
		int x = (r() % W) + 1;
		int y = (r() % H) + 1;
		int h = (r() % _d) + 1;
		return Space{x, y, h};
	}

	ulong r() {
		_t = (_t * _a + _b) % _c;
		return _t;
	}
};

bool setHeight(Field& f, int x, int y, int value) {
	if (y < 1 || f.size() < y) return true;
	auto& v = f[y - 1];
	if (x < 1 || v.size() < x) return true;
	v[x - 1] = std::max(v[x - 1], value);
	return false;
}
void addTower(Field& f, const Space& s) {
	setHeight(f, s.x, s.y, s.h);
	for (int i = 1; i < s.h; ++i) {
		bool b1 = setHeight(f, s.x + i, s.y, s.h - i);
		bool b2 = setHeight(f, s.x - i, s.y, s.h - i);
		bool b3 = setHeight(f, s.x, s.y + i, s.h - i);
		bool b4 = setHeight(f, s.x, s.y - i, s.h - i);
		if(b1 && b2 && b3 && b4) {
			break;
		}
	}
}

void display(const Field& f) {
	for (auto it = f.begin(); it != f.end(); ++it) {
		auto v = *it;
		for (auto i = v.begin(); i != v.end(); ++i) {
			std::cout << *i << " ";
		}
		std::cout << std::endl;
	}
}

void countValue(std::map<int, int>& map, const Field& f) {
	for (auto it = f.begin(); it != f.end(); ++it) {
		auto v = *it;
		for (auto i = v.begin(); i != v.end(); ++i) {
			int x = *i;
			map[x]++;
		}
	}
}

std::map<int, int> resolve(G& g, const int W, const int H, const int N) {
	std::map<int, int> map;
	Field f(H);
	for (auto it = f.begin(); it != f.end(); ++it) {
		*it = std::vector<int>(W);
	}

	for (int i = 0; i < N; i++) {
		Space s = g.gen(W, H);
		// std::cout << i << ": (" << s.x << ", " << s.y << ", " << s.h << ")" << std::endl;
		addTower(f, s);
	}
	display(f);
	countValue(map, f);
	return map;
}

int main(int argc, char *argv[]) {
	int W, H, N;
	std::cin >> W;
	std::cin >> H;
	std::cin >> N;
	unsigned long a, b, c, d;
	std::cin >> a;
	std::cin >> b;
	std::cin >> c;
	std::cin >> d;

	G g(a, b, c, d);
	std::map<int, int> map = resolve(g, W, H, N);

	int Q;
	std::cin >> Q;
	for (int i = 0; i < Q; i++) {
		int x;
		std::cin >> x;

		const auto it = map.find(x);
		if (it == map.end()) {
			std::cout << 0 << std::endl;
		} else {
			std::cout << it->second << std::endl;
		}
	}
	return 0;
}

