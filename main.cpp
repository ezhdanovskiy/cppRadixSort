#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <ctime>

#include <stdio.h>
#include <sys/time.h>

#define LOG(chain) std::cout << chain << std::endl;
#define LOG1(el) std::cout << #el << "=" << el << std::endl;

long long mtime() {
	struct timeval t;
	gettimeofday(&t, NULL);
	long long mt = (long long)t.tv_sec * 1000 + t.tv_usec / 1000;
	return mt;
}

std::ostream& operator<<(std::ostream &o, const std::vector<int> &v) {
	o << "(" << v.size() << ")={ ";
	for (auto &el : v) {
		o << el << ", ";
	}
	return o << "}";
}

void bubbleSort(std::vector<int> &v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i + 1; j < v.size(); ++j) {
			if (v[i] > v[j]) {
				std::swap(v[i], v[j]);
			}
		}
	}
}

int main(int argc, char **argv) {
	srand(time(NULL));

	int size = 10;
	if (argc > 1) {
		size = atol(argv[1]);
	}
	LOG1(size);
	std::vector<int> v1(size);
	for (int i = 0; i < size; i++) {
		v1[i] = rand();
	}
	std::vector<int> v2 = v1;
//	LOG1(v1);

	auto t1 = mtime();
	std::sort(begin(v1), end(v1));
	LOG("std::sort take " << mtime() - t1 << " ms");
//	LOG1(v1);

	auto t2 = mtime();
	bubbleSort(v2);
	LOG("bubbleSort take " << mtime() - t2 << " ms");
//	LOG1(v2);

	assert(v1 == v2);
	return 0;
}
