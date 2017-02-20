#include "Define.h"
#include "InputParser.h"


using namespace puzzle;

int main(int argc, char const* argv[]) {
	InputParser parser;
	std::ifstream ifs("input.txt");
	bool res = parser.parse(ifs);
	std::cout << "Parse result: " << std::boolalpha << res << std::endl;

	UseCountPtr const& countPtr = parser.getUseCount();
	std::cout << "L" << countPtr->left
			<< " R" << countPtr->right
			<< " U" << countPtr->up
			<< " D" << countPtr->down
			<< std::endl;

	BoardInfos const& boards = parser.getBoards();
	std::cout << "BoardCount:" << boards.size() << std::endl;
	return 0;
}

