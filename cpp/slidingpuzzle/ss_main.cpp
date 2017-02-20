#include <boost/foreach.hpp>

#include "Define.h"
#include "SlidingSolver.h"

using namespace puzzle;

int main(int argc, char const* argv[]) {
	BoardInfoPtr board = boost::make_shared<BoardInfo>();
	// board->width = 3;
	// board->height = 3;
	// board->board = "168452=30";
	// board->width = 3;
	// board->height = 4;
	// board->board = "1327A40=5B96";
	// board->width = 4;
	// board->height = 4;
	// board->board = "32465871FAC0=9BE";
	board->width = 3;
	board->height = 6;
	board->board = "17=42=580HFEABD9GC";

	SlidingSolver solver;
	MoveInfos result = solver.solve(board);
	std::cout << "result count=" << result.size() << std::endl;
	BOOST_FOREACH(MoveInfoPtr const& ptr, result) {
		std::cout << ptr->moved << std::endl;
	}
	return 0;
}

