#include <iostream>
#include <string>
#include <vector>

struct V {
    constexpr V(int _x, int _y): x(_x), y(_y) {}
    int x;
    int y;
};

double f(V a, V b) {
    return (a.x*b.x + a.y*b.y) * 1.0 / (a.x*a.x + a.y*a.y) * 1.0;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<V> vec;
    vec.reserve(n);
	for (int i = 0; i < n; ++i) {
        int x, y;
		std::cin >> x;
		std::cin >> y;
		vec.emplace_back(x, y);
	}

    int acute = 0;
    int right = 0;
    int obtuse = 0;
    for (int i = 0; i < n - 2; ++i) {
        V A = vec[i];
        for (int j = i + 1; j < n - 1; ++j) {
            V B = vec[j];
            for (int k = j + 1; k < n; ++k) {
                V P = vec[k];
                
                V a(B.x - A.x, B.y - A.y);
                V b(P.x - A.x, P.y - A.y);
                V c(B.x - P.x, B.y - P.y);
	            double r = f(a, b);
                if (r == 0 || r == 1) {
                    ++right;
                } else if (0 < r && r < 1) {
                    double p = f(c, a);
                    if (p == 0 || p == 1) {
                        ++right;
                    } else if (0 < p && p < 1){
                        ++acute;
                    } else {
                        ++obtuse;
                    }
                } else {
                    ++obtuse;
                }
            }
        }
    }
    std::cout << acute << " " << right << " " << obtuse << std::endl;
	return 0;
}

