#include <cassert>
#include <iostream>
#include <string>
#include <vector>

const int WWIDTH = 10;
const int WHEIGHT = 10;
const int MY_WIDTH = 5;
const int MY_HEIGHT = 5;


struct Result {
	int x;
	int y;
	int g;
};
std::ostream& operator<<(std::ostream& os, const Result& r) {
	os << "{\"x\":" << r.x << ",\"y\":" << r.y << ",\"g\":" << r.g << "}";
	return os;
}

class World {
public:
	World(std::vector<std::string> const& input): _value() {
		assert(input.size() == WHEIGHT);
		for (auto line: input) {
			assert(line.size() == WWIDTH);
			this->appendLine(line);
		}
	}

	Result count(int startX, int startY, int width, int height) {
		int g = 0;
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				if (this->get(x + startX, y + startY)) {
					++g;
				}
			}
		}
		return {startX, startY, g};
	}
	bool get(int x, int y) {
		return this->_value[y * WWIDTH + x];
	}

private:
	void appendLine(std::string const& line) {
		for (auto c: line) {
			_value.push_back(c == 'G');
		}
	}

	std::vector<bool> _value;
};

int main(int argc, char *argv[]) {
	std::vector<std::string> field;
	std::string line;
	while (getline(std::cin, line)) {
		field.emplace_back(line);
	}

	World w(field);

	Result r{0, 0, 0};
	for (int y = 0; y < WHEIGHT - MY_HEIGHT + 1; ++y) {
		for (int x = 0; x < WWIDTH - MY_WIDTH + 1; ++x) {
			auto work = w.count(x, y, MY_WIDTH, MY_HEIGHT);
			if (work.g > r.g) {
				r = work;
			}
		}
	}
	std::cout << r << std::endl;
}

