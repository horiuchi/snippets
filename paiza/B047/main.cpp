#include <iostream>
#include <map>
#include <string>

struct Point {
	int x;
	int y;

	Point(): x(0), y(0) {}
	Point(int _x, int _y): x(_x), y(_y) {}
};
std::ostream& operator<<(std::ostream& os, const Point& p) {
	return os << "(x, y)=(" << p.x << ", " << p.y << ")";
}

typedef std::map<char, Point> PointMap;

std::string table[] = {
	"qwertyuiop",
	"asdfghjkl",
	"zxcvbnm",
};

void initMap(PointMap& map) {
	for (int y = 0; y <=2; y++) {
		const auto line = table[y];
		for (int x = 0, len = line.length(); x < len; x++) {
			char c = line[x];
			map[c] = Point(x, y);
		}
	}
}


bool isMissType(Point now, Point prev) {
	return prev.y == now.y && ((prev.x == 4 && now.x == 5) || (now.x == 4 && prev.x == 5));
}
bool isNeighbor(Point now, Point prev) {
	return (now.y == prev.y && (prev.x - 1 <= now.x && now.x <= prev.x + 1))
		|| (now.x == prev.x && (prev.y - 1 <= now.y && now.y <= prev.y + 1));
}

int solve(std::string input, PointMap map) {
	int count = 0;
	bool mode = false;
	Point prev = Point(-1, -1);
	for (auto c: input) {
		auto p = map[c];
		if (mode) {
			if (isNeighbor(p, prev)) {
				count++;
			} else {
				mode = false;
			}
		} else {
			if (isMissType(p, prev)) {
				count++;
				mode = true;
			}
		}
		prev = p;
	}
	return count;
}

int main(int argc, char *argv[]) {
	std::string s;
	std::cin >> s;

	PointMap map;
	initMap(map);

	std::cout << solve(s, map) << std::endl;

	return 0;
}

