#include <algorithm>
#include <iostream>
#include <vector>

enum class Direction : int {
	N, E, S, W,
};
struct Position {
	int y;
	int x;
	Direction d;
	Position(int _y, int _x): y(_y), x(_x), d(Direction::N) {}

	void changeDirection(bool isPoor) {
		int next = (static_cast<int>(this->d) + (isPoor ? 1 : -1));
		if (next < 0) next += 4;
		if (next >= 4) next -= 4;
		this->d = static_cast<Direction>(next);
	}
	void doMove() {
		switch (this->d) {
			case Direction::N: --this->y; break;
			case Direction::E: ++this->x; break;
			case Direction::S: ++this->y; break;
			case Direction::W: --this->x; break;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const Position& p);
};
typedef std::vector<std::string> Scheme;

std::ostream& operator<<(std::ostream& os, const Position& p) {
	return os << "d=" << static_cast<int>(p.d) << " (x, y)=(" << p.x << ", " << p.y << ")";
}

bool checkRange(const Position& p, int H, int W) {
	return (0 <= p.y && p.y < H) && (0 <= p.x && p.x < W);
}

bool isPoor(char c) {
	return c == '.';
}
bool flipValue(Scheme& s, const Position& p) {
	bool b = isPoor(s[p.y][p.x]);
	s[p.y][p.x] = b ? '*' : '.';
	return b;
}
void move(Scheme& s, Position& p) {
	bool b = flipValue(s, p);
	p.changeDirection(b);
	p.doMove();
}

int main(int argc, char *argv[]) {
	int H, W;
	int y, x;

	std::cin >> H;
	std::cin >> W;
	std::cin >> y;
	std::cin >> x;
	Position p(y - 1, x - 1);
	Direction d = Direction::N;

	Scheme s;
	for (int i = 0; i < H; ++i) {
		std::string str;
		std::cin >> str;
		s.push_back(str);
	}

	while (checkRange(p, H, W)) {
		move(s, p);
	}

	for (auto it = s.cbegin(); it != s.cend(); ++it) {
		std::cout << *it << std::endl;
	}
	return 0;
}

