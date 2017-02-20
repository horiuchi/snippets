#ifndef _EVALUATE_BOARD_H_
#define _EVALUATE_BOARD_H_

#include <assert.h>

#include <set>
#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/optional.hpp>

namespace puzzle {

	enum FixedStatus { 
		NG, FIXED, HOLD,
	};

	typedef boost::optional<int> Coord;

	class EvaluateBoard {
	public:
		std::set<int> get_fixed_indexes(int const w, int const h, std::string const& board, std::string const& goal) {
			std::vector<FixedStatus> statuses;
			for (int index = 0; index < static_cast<int>(board.length()); ++index) {
				if (board[index] == goal[index]) {
					statuses.push_back(FIXED);
				} else {
					statuses.push_back(NG);
				}
			}

			for (std::size_t index = 0; index < statuses.size(); ++index) {
				if (statuses[index] != NG) continue;
				{
					Coord left = get_left_index(board, w, index);
 					Coord right = get_right_index(board, w, index);
					if (!(left && statuses[*left] == NG) && !(right && statuses[*right] == NG)) {
						if (left && right) {
							statuses[*left] = statuses[*right] = HOLD;
						} else if (left) {
							statuses[*left] = NG;
						} else if (right) {
							statuses[*right] = NG;
						}
					}
				}
                {
					Coord up = get_up_index(board, w, h, index);
					Coord down = get_down_index(board, w, h, index);
                    if (!(up && statuses[*up] == NG) && !(down && statuses[*down] == NG)) {
                        if (up && down) {
                            statuses[*up] = statuses[*down] = HOLD;
                        } else if (up) {
                            statuses[*up] = NG;
                        } else if (down) {
                            statuses[*down] = NG;
                        }
                    }
				}
            }

            bool is_hold_changed = false;
            do {
            	is_hold_changed = false;
                for (std::size_t index = 0; index < statuses.size(); ++index) {
                    if (statuses[index] == HOLD) {
						int fixed_count = 0;
						if (is_fixed_index(statuses, get_left_index(board, w, index))) fixed_count++;
 						if (is_fixed_index(statuses, get_right_index(board, w, index))) fixed_count++;
						if (is_fixed_index(statuses, get_up_index(board, w, h, index))) fixed_count++;
						if (is_fixed_index(statuses, get_down_index(board, w, h, index))) fixed_count++;

						if (fixed_count >= 3) {
							statuses[index] = FIXED;
							is_hold_changed = true;
						}
                    }
                }
            } while (is_hold_changed);

            std::set<int> result;
            for (std::size_t index = 0; index < statuses.size(); ++index) {
                if (statuses[index] == FIXED) {
                    result.insert(index);
                }
            }
            return result;
        }

		Coord get_left_index(std::string const& board, int const width, int const index) {
			int const x = index % width;
			return x > 0 && board[index - 1] != '=' ? Coord(index - 1) : Coord();
		}
		Coord get_right_index(std::string const& board, int const width, int const index) {
			int const x = index % width;
			return x < width - 1 && board[index + 1] != '=' ? Coord(index + 1) : Coord();
		}
		Coord get_up_index(std::string const& board, int const width, int const height, int const index) {
			int y = index / width;
			return y > 0 && board[index - width] != '=' ? Coord(index - width) : Coord();
		}
		Coord get_down_index(std::string const& board, int const width, int const height, int const index) {
			int y = index / width;
			return y < height - 1 && board[index + width] != '=' ? Coord(index + width) : Coord();
		}

		bool is_fixed_index(std::vector<FixedStatus> const& statuses, Coord const& coord) {
			if (!coord) return true;
			return statuses[*coord] == FIXED;
		}

	};

}

#endif

