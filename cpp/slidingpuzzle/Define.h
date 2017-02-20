#ifndef _DEFINE_
#define _DEFINE_

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace puzzle {

	static const bool DEBUG = true;
	#define LOG(...) if (DEBUG) { std::cout << __VA_ARGS__ << std::endl; }

	struct UseCount {
		int left;
		int right;
		int up;
		int down;
	};
	typedef boost::shared_ptr<UseCount> UseCountPtr;

	struct BoardInfo {
		int width;
		int height;
		std::string board;
	};
	typedef boost::shared_ptr<BoardInfo> BoardInfoPtr;
	typedef std::vector<BoardInfoPtr> BoardInfos;

	struct MoveInfo {
		UseCount used;
		std::string moved;
	
		void append(char move) {
			switch(move) {
				case 'L':
					used.left++;
					break;
				case 'R':
					used.right++;
					break;
				case 'U':
					used.up++;
					break;
				case 'D':
					used.down++;
					break;
				default:
					return;
			}
			moved += move;
		}
	};
	typedef boost::shared_ptr<MoveInfo> MoveInfoPtr;
	typedef std::vector<MoveInfoPtr> MoveInfos;

}

#endif

