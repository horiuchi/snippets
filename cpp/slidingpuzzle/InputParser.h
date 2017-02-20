#ifndef _INPUT_PARSER_
#define _INPUT_PARSER_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>

#include "Define.h"

namespace puzzle {

	class InputParser {
	public:
		InputParser() : useCount_(new UseCount()) {
		}

		bool parse(std::ifstream& ifs) {
			if (!parse_use_count(ifs))
				return false;
			int count = 0;
			if (!parse_board_count(ifs, count))
				return false;
			for (int index = 0; index < count; index++) {
				if (!parse_board_info(ifs)) {
					return false;
				}
			}
			return true;
		}


		UseCountPtr const& getUseCount() const { return useCount_; }
		BoardInfos const& getBoards() const { return boards_; }

	private:
		bool parse_use_count(std::ifstream& ifs) {
			std::string line;
			if (!std::getline(ifs, line)) return false;
			LOG("parse use_count: " << line);

			std::stringstream ss(line);
			useCount_->left = parse_int_value(ss);
			useCount_->right = parse_int_value(ss);
			useCount_->up = parse_int_value(ss);
			useCount_->down = parse_int_value(ss);
			return true;
		}

		bool parse_board_count(std::ifstream& ifs, int& count) {
			std::string line;
			if (!std::getline(ifs, line)) return false;
			LOG("parse board_count: " << line);

			count = boost::lexical_cast<int>(line);
			boards_.reserve(count);
			return true;
		}

		bool parse_board_info(std::ifstream& ifs) {
			std::string line;
			if (!std::getline(ifs, line)) return false;
			LOG("parse board_info: " << line);

			std::vector<std::string> vec;
			boost::algorithm::split(vec, line, boost::is_any_of(",\r\n"));
			if (vec.size() != 3) {
				LOG(" invalid format: (count error) " << line);
				return false;
			}

			BoardInfoPtr board = boost::make_shared<BoardInfo>();
			board->width = boost::lexical_cast<int>(vec[0]);
			board->height = boost::lexical_cast<int>(vec[1]);
			board->board = vec[2];
			boards_.push_back(board);
			return true;
		}

		int parse_int_value(std::stringstream& ss) {
			int value;
			ss >> value;
			return value;
		}

	private:
		UseCountPtr useCount_;
		BoardInfos boards_;
	};

}

#endif

