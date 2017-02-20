// :let b:quickrun_config={'args':'input.txt'}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

typedef std::vector<std::vector<int> > INPUT_DATA;

static const bool IS_DEBUG = false;

void print_data(const std::vector<int>& data) {
	if (!IS_DEBUG) return;

	BOOST_FOREACH(int i, data) {
		std::cout << i << ",";
	}
	std::cout << std::endl;
}


struct DivisibleDeleter {
	bool operator()(int i) {
		return i % 5 == 0;
	}
};
bool remove_divisible_by_5(std::vector<int>& data) {
	std::vector<int>::iterator it = std::remove_if(data.begin(), data.end(), DivisibleDeleter());
	if (it == data.end()) {
		return false;
	}
	data.erase(it, data.end());
	return true;
}

void divide_by_2(std::vector<int>& data) {
	BOOST_FOREACH(int& i, data) {
		i = i / 2;
	}
}

int solve_count(const std::vector<int>& data) {
	if (IS_DEBUG) std::cout << "start solver." << std::endl;
	print_data(data);

	int round = 1;
	INPUT_DATA all_data;
	all_data.push_back(data);
	for (;;) {
		if (IS_DEBUG) std::cout << "-- ROUND " << round << " --" << std::endl;
		INPUT_DATA work;
		BOOST_FOREACH(const std::vector<int>& vec, all_data) {
			std::vector<int> copy = vec;
			if (remove_divisible_by_5(copy)) {
				print_data(copy);

				if (copy.empty()) {
					return round;
				}
				work.push_back(copy);
				copy = vec;
			}

			divide_by_2(copy);
			print_data(copy);

			work.push_back(copy);
		}
		std::swap(all_data, work);
		round++;
	}
}

bool solve(const INPUT_DATA& input, std::vector<int>& ans) {
	ans.reserve(input.size());
	for (INPUT_DATA::const_iterator it = input.begin();
			it != input.end(); ++it) {
		ans.push_back(solve_count(*it));
	}
	return true;
}


bool load_input_data(std::ifstream& ifs, INPUT_DATA& result) {
	std::string line;
	if (!std::getline(ifs, line)) {
		std::cerr << "Error: input data invalid." << std::endl;
		return false;
	}
	int count = boost::lexical_cast<int>(line);
	result.reserve(count);
	for (int index = 0; index < count && ifs; index++) {
		if (!std::getline(ifs, line)) {
			std::cerr << "Error: input data invalid." << std::endl;
			return false;
		}
		int c = boost::lexical_cast<int>(line);
		std::vector<int> vec(c);
		
		if (!std::getline(ifs, line)) {
			std::cerr << "Error: input data invalid." << std::endl;
			return false;
		}
		std::istringstream iss(line);
		for (int j = 0; j < c; j++) {
			iss >> vec[j];
		}

		result.push_back(vec);
	}
	return true;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "argument is nothing." << std::endl;
		return 1;
	}

	std::cout << "load: " << argv[1] << std::endl;
	std::ifstream ifs(argv[1]);
	INPUT_DATA data;
	if (!load_input_data(ifs, data)) {
		return 1;
	}

	std::cout << "data: size=" << data.size() << std::endl;
	std::vector<int> answer;
	solve(data, answer);

	std::ofstream ofs("output.txt");
	for (std::vector<int>::const_iterator it = answer.begin();
			it != answer.end(); ++it) {
		ofs << *it << std::endl;
		std::cout << *it << std::endl;
	}
}

