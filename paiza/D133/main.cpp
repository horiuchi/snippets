#include <iostream>

int main(void){
    int X, A, B;
    std::cin >> X;
    std::cin >> A;
    std::cin >> B;

	int count = X / A;
	std::cout << (B - A) * count << std::endl;
    return 0;
}

