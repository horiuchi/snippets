#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

struct Point {
	int x;
	int y;

	Point(int x1, int y1): x(x1), y(y1) {}
};

int calcMaxWidth(std::vector<Point> const& inputs) {
	int minX, maxX, minY, maxY;
	minX = maxX = inputs[0].x;
	minY = maxY = inputs[0].y;
	for (int i = 1, len = inputs.size(); i < len; ++i) {
		Point const& p = inputs[i];
		minX = std::min(p.x, minX);
		minY = std::min(p.y, minY);
		maxX = std::max(p.x, maxX);
		maxY = std::max(p.y, maxY);
	}
	return std::max(maxX - minX, maxY - minY);
}

int main(int argc, char *argv[]) {
	int x, y;
	std::vector<Point> inputs;
	while (std::scanf("%d,%d", &x, &y) > 0) {
		inputs.emplace_back(x, y);
	}
	int width = calcMaxWidth(inputs);
	std::cout << width * width << std::endl;
	return 0;
}

