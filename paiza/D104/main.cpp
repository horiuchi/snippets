#include <iostream>

int main(void){
    int N;
    std::cin >> N;
    if (N < 10) {
        std::cout << 1000 << std::endl;
    } else {
        std::cout << N * 150 << std::endl;
    }
    return 0;
}

