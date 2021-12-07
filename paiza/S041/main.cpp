#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
	int to;
	int cost;
};
using vEdge = std::vector<Edge>;
using Graph = std::vector<vEdge>;

bool addAllEdge(Graph& g, int start, int n, int value) {
	if (start == n) {
		return true;
	}
	auto es = g[n];
	for (auto it = es.cbegin(); it != es.cend(); ++it) {
		result[it->to] += value;
		if (addAllEdge(g, start, it->to, value)) {
			return true;
		}
	}
	return false;
}

std::vector<int> resolve(Graph& g) {
	std::vector<int> result(g.size(), 1);

	for (int i = 1; i < g.size(); ++i) {
		auto es = g[i];
		for (auto it = es.cbegin(); it != es.cend(); ++it) {
			int from = result[i];
			int to = result[it->to];
			int a = it->cost;
			if (to - from < a) {
				int value = from + a;
				result[it->to] = value;
				// addAllEdge(g, i, it->to, value);
			}
		}
	}
	for (int i = 1; i < g.size(); ++i) {
		auto es = g[i];
		for (auto it = es.cbegin(); it != es.cend(); ++it) {
			int from = result[i];
			int to = result[it->to];
			int a = it->cost;
			if (to - from < a) {
				return std::vector<int>{ 0, -1 };
			}
		}
	}

	return result;
}

int main(int argc, char *argv[]) {
	int N, M;
	std::cin >> N;
	std::cin >> M;

	Graph g(M + 1);
	for (int i = 0; i < M; i++) {
		int x, y, a;
		std::cin >> x;
		std::cin >> y;
		std::cin >> a;
		g[y].push_back({x, a});
	}

//	for (int i = 1; i < g.size(); ++i) {
//		auto es = g[i];
//		for (auto it = es.cbegin(); it != es.cend(); ++it) {
//			std::cout << i << ", " << it->to << ": " << it->cost << std::endl;
//		}
//	}

	auto result = resolve(g);
	bool isFirst = true;
	for (auto it = result.cbegin(); it != result.cend(); ++it) {
		if (isFirst) {
			isFirst = false;
			continue;
		}
		std::cout << *it << std::endl;
	}

	return 0;
}

