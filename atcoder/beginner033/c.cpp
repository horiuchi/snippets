#include <iostream>
#include <string>

int main() {
	std::string s;
	std::cin >> s;
    int count = 0;
    bool zeroTerm = false;
	for (int i = 0, len = s.size(); i < len; ++i) {
        char c = s[i];
        switch (c) {
            case '+':
                if (!zeroTerm) ++count;
                zeroTerm = false;
                break;
            case '0':
                zeroTerm = true;
                break;
        }
	}
    if (!zeroTerm) ++count;

    std::cout << count << std::endl;
	return 0;
}

