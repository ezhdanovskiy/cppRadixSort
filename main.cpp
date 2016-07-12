#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <ctime>
#include <sys/time.h>
#include <iomanip>

#define LOG(chain) std::cout << chain << std::endl;
#define LOG1(el) std::cout << #el << "=" << el << std::endl;

long long mtime() {
	struct timeval t;
	gettimeofday(&t, NULL);
	long long mt = (long long)t.tv_sec * 1000 + t.tv_usec / 1000;
	return mt;
}

typedef uint8_t TDigit;
typedef std::vector<TDigit> TDigits;

std::ostream& operator<<(std::ostream &o, const TDigits &v) {
	o << "(" << v.size() << ")={ ";
	for (auto &el : v) {
		o << (int)el << ", ";
	}
	return o << "}";
}

void bubbleSort(TDigits &v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i + 1; j < v.size(); ++j) {
			if (v[i] > v[j]) {
				std::swap(v[i], v[j]);
			}
		}
	}
}

void radixSort(TDigits &v) {
	const int typeBitsCnt = 8;
	const int bitStep = 4;
	const int bitStepMaxValue = 16;
	for (int r = 0; r < typeBitsCnt; r += bitStep) {
		TDigits v2[bitStepMaxValue];
		for (int i = 0; i < v.size(); ++i) {
			v2[v[i]>>r & 0xf].push_back(v[i]);
		}
		v.clear();
		for (int i = 0; i < bitStepMaxValue; ++i) {
			for (const auto &el : v2[i]) {
				v.push_back(el);
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
	TDigits v0(size);
	for (int i = 0; i < size; i++) {
		v0[i] = rand() % std::numeric_limits<TDigit>::max();
	}
	TDigits v4 = v0;

	TDigits v1 = v0;
	{
		auto t = mtime();
		std::sort(begin(v1), end(v1));
		LOG("std::sort        " << std::setw(10) << mtime() - t << " ms");
	}

	{
		TDigits v = v0;
		auto t = mtime();
		std::stable_sort(begin(v), end(v));
		LOG("std::stable_sort " << std::setw(10) << mtime() - t << " ms");
		assert(v1 == v);
	}

	{
		TDigits v = v0;
		auto t = mtime();
		radixSort(v);
		LOG("radixSort        " << std::setw(10) << mtime() - t << " ms");
		assert(v1 == v);
	}

	if (size <= 100000)
	{
		TDigits v = v0;
		auto t = mtime();
		bubbleSort(v);
		LOG("bubbleSort       " << std::setw(10) << mtime() - t << " ms");
		assert(v1 == v);
	}

	return 0;
}
