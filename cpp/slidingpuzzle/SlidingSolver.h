#ifndef _SLIDING_SOLVER_
#define _SLIDING_SOLVER_

#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <boost/optional.hpp>

#include "Define.h"
#include "EvaluateBoard.h"

namespace puzzle {

	struct MoveCell;
	typedef boost::shared_ptr<MoveCell> MoveCellPtr;
	typedef std::vector<MoveCellPtr> MoveCells;
	
	struct MoveCell {
		char move;
		MoveCells prevs;
		MoveCells nexts;
	};

	typedef std::map<std::string, MoveCells> MoveCellMap;
	typedef std::map<std::string, std::set<int> > FixedIndexMap;
	typedef boost::optional<std::string> OpString;

	class SlidingSolver {
	public:
		SlidingSolver() {}

		MoveInfos solve(BoardInfoPtr const& board) {
			MoveCells cells = solve_(board);

			MoveInfos result;
			std::back_insert_iterator<MoveInfos> result_it(result);
			BOOST_FOREACH(MoveCellPtr const& cell, cells) {
				MoveInfos moves = chase_move_path(cell);
				std::copy(moves.begin(), moves.end(), result_it);
				LOG(" " << moves.size());
			}
			return result;
		}

		MoveCells solve_(BoardInfoPtr const& board) {
			int const width = board->width;
			int const height = board->height;
			std::string const goal = get_goal(board->board);
			MoveCellMap allmap;
			{
				MoveCellPtr cell = boost::make_shared<MoveCell>();
				allmap[board->board].push_back(cell);
			}

			{
				fixedIndexMap.clear();
				fixedIndexMap[board->board] = evaluator.get_fixed_indexes(width, height, board->board, goal);
			}

			std::set<std::string> current;
			current.insert(board->board);

			typedef std::pair<std::string, MoveCells> PairType;
			std::string const moves = "LRUD";

			int round = 1;
			LOG("solve board=" << board->board);
			LOG("       goal=" << goal);
			while (!current.empty()) {
				std::set<std::string> next;
				
				LOG("-- ROUND " << round++ << ": " << current.size() << " --");
				BOOST_FOREACH(std::string const& board, current) {
					BOOST_FOREACH(char move, moves) {
						OpString op = check_move_board(width, height, board, move);
						if (op) {
							MoveCellMap::const_iterator it = allmap.find(board);
							if (it == allmap.end()) continue;

							std::set<int> set = fixedIndexMap[*op] = evaluator.get_fixed_indexes(width, height, *op, goal);
							// if (set.size() < fixedIndexMap[board].size()) continue;

							BOOST_FOREACH(MoveCellPtr const& cell, it->second) {
								if (move == reverse_move(cell->move)) continue;
								if (append_new_move(allmap, *op, move, cell)) {
									if (goal != *op) {
										next.insert(*op);
									} else {
										// TODO 
										return allmap[*op];
									}
								}
							}
						}
					}
				}

				current = next;
			}

			std::cout << "error, allmap = " << allmap.size() << std::endl;
			return MoveCells();
		}

	private:
		std::string get_goal(std::string const& board) {
			static std::string const BOARD = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0";
			std::string goal(board);
			for (std::size_t index = 0; index < board.length(); ++index) {
				char c = (index < board.length() - 1) ? BOARD[index] : '0';
				if (board[index] != '=') {
					goal[index] = c;
				}
			}
			return goal;
		}

		bool append_new_move(MoveCellMap& map, std::string const& board, char move, MoveCellPtr const& prev) {
			MoveCellMap::const_iterator it = map.find(board);
			if (it == map.end()) {
				MoveCellPtr current = boost::make_shared<MoveCell>();
				current->move = move;
				current->prevs.push_back(prev);
				prev->nexts.push_back(current);
				map[board].push_back(current);
				return true;
			} else {
				// TODO
				return false;
			}
		}

		char reverse_move(char c) {
			switch (c) {
				case 'L': return 'R';
				case 'R': return 'L';
				case 'U': return 'D';
				case 'D': return 'U';
				default: return ' ';
			}
		}

		boost::optional<std::string> check_move_board(int w, int h, std::string board, char move) {
			switch (move) {
				case 'L':
					return check_x_move_board(w, h, board, -1);
					break;
				case 'R':
					return check_x_move_board(w, h, board, +1);
					break;
				case 'U':
					return check_y_move_board(w, h, board, -1);
					break;
				case 'D':
					return check_y_move_board(w, h, board, +1);
					break;
			}
			return boost::optional<std::string>();
		}
		boost::optional<std::string> check_x_move_board(int w, int h, std::string board, int dx) {
			std::size_t index = board.find('0');
			int x = index % w;
			if ((dx < 0 && x <= 0) || (dx > 0 && x >= w - 1)) {
				return boost::optional<std::string>();
			}
			return check_xy_move_board(board, index, index + dx);
		}
		boost::optional<std::string> check_y_move_board(int w, int h, std::string board, int dy) {
			std::size_t index = board.find('0');
			int y = index / w;
			if ((dy < 0 && y <= 0) || (dy > 0 && y >= h - 1)) {
				return boost::optional<std::string>();
			}
			return check_xy_move_board(board, index, index + dy * w);
		}
		boost::optional<std::string> check_xy_move_board(std::string board, int from_index, int to_index) {
			FixedIndexMap::const_iterator fit = fixedIndexMap.find(board);
			if (fit != fixedIndexMap.end()) {
				std::set<int>::const_iterator index_it = fit->second.find(to_index);
				if (index_it != fit->second.end()) {
					return boost::optional<std::string>();
				}
			}
			char c = board[to_index];
			if (c == BLOCK) {
				return boost::optional<std::string>();
			}
			std::string next = board;
			next[from_index] = board[to_index];
			next[to_index] = '0';
			return boost::optional<std::string>(next);
		}

		MoveInfos chase_move_path(MoveCellPtr const& cell) {
			MoveInfos result;
			result.push_back(boost::make_shared<MoveInfo>());
			chase_move_path_r(cell, result);
			return result;
		}
		void chase_move_path_r(MoveCellPtr const& cell, MoveInfos& moves) {
			BOOST_FOREACH(MoveInfoPtr const& move, moves) {
				move->append(cell->move);
			}
			if (cell->prevs.empty()) return;
			if (cell->prevs.size() == 1) {
				chase_move_path_r(cell->prevs[0], moves);
			} else {
				MoveInfos copy = deep_copy(moves);
				moves.clear();
				moves.reserve(copy.size() * cell->prevs.size());
				std::back_insert_iterator<MoveInfos> moves_it(moves);
				BOOST_FOREACH(MoveCellPtr const& prev, cell->prevs) {
					MoveInfos work = deep_copy(copy);
					chase_move_path_r(prev, work);
					std::copy(work.begin(), work.end(), moves_it);
				}
			}
		}

		MoveInfos deep_copy(MoveInfos const& moves) {
			MoveInfos copy;
			copy.reserve(moves.size());
			BOOST_FOREACH(MoveInfoPtr const& move, moves) {
				copy.push_back(deep_copy(move));
			}
			return copy;
		}
		MoveInfoPtr deep_copy(MoveInfoPtr const& move) {
			MoveInfoPtr copy = boost::make_shared<MoveInfo>();
			copy->moved = move->moved;
			copy->used = move->used;
			return copy;
		}

	private:
		static const char BLOCK = '=';

		EvaluateBoard evaluator;
		FixedIndexMap fixedIndexMap;
	};

}

#endif

