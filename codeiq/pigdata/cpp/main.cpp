#include <iostream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/sha1.hpp>


void display(unsigned short* hash) {
	//std::cout << "SHA1: " << std::hex;
	std::cout << "SHA1: ";
	for (int i = 0; i < 10; i++) {
		std::cout << hash[i] << " ";
	}
	std::cout << std::endl;
}

void collect(std::vector<long>& v, unsigned short* hash) {
	for (int i = 0; i < 10; ++i) {
		++v[hash[i]];
	}
}
long counting(std::vector<long> const& v, int skips) {
	long sum = 0;
	int s = 0;
	for (int i = 0, size = v.size(); i < size; ++i) {
		if (v[i] == 0L) continue;
		if (v[i] <= s) {
			s -= v[i];
		} else {
			long count = v[i];
			while (count > s) {
				std::cout << i << std::endl;
				sum += i;
				count -= s;
				s = skips;
			}
			s -= count;
		}
	}
	return sum;
}
long getsign(long count, int skips) {
	std::vector<long> v(0x10000);
	boost::uuids::detail::sha1 s;

	for (long i = 0; i < count / 10; ++i) {
		std::string a = boost::lexical_cast<std::string>(i);
		s.process_bytes(a.c_str(), a.size());
		unsigned int digest[5];
		s.get_digest(digest);
		s.reset();

		collect(v, reinterpret_cast<unsigned short*>(digest));
	}
	std::cout << "collect complete." << std::endl;
	return counting(v, skips);
}

int main() {
	long count = 107374182400L;
	int skips = 16777216;

	std::cout << "result: " << getsign(count, skips) << std::endl;
}

