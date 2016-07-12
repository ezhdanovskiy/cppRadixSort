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

template <typename TDigit>
std::ostream& operator<<(std::ostream &o, const std::vector<TDigit> &v) {
	o << "(" << v.size() << ")={ ";
	for (auto &el : v) {
		o << (uint64_t)el << ", ";
	}
	return o << "}";
}

template <typename TDigit>
void bubbleSort(std::vector<TDigit> &v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i + 1; j < v.size(); ++j) {
			if (v[i] > v[j]) {
				std::swap(v[i], v[j]);
			}
		}
	}
}

template <typename TDigit>
void radixSort(std::vector<TDigit> &v) {
	const int typeBitsCnt = sizeof(TDigit) * 8;
	const int bitStep = 4;
	const int bitStepMaxValue = 16;
	for (int r = 0; r < typeBitsCnt; r += bitStep) {
		std::vector<TDigit> v2[bitStepMaxValue];
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

template <typename TDigit>
void test(int size) {
	const int typeBitsCnt = sizeof(TDigit) * 8;
	LOG1(typeBitsCnt);
	std::vector<TDigit> v0(size);
	for (int i = 0; i < size; i++) {
		v0[i] = rand() % std::numeric_limits<TDigit>::max();
	}

	std::vector<TDigit> v1 = v0;
	{
		auto t = mtime();
		std::sort(begin(v1), end(v1));
		LOG("std::sort        " << std::setw(10) << mtime() - t << " ms");
	}

	{
		std::vector<TDigit> v = v0;
		auto t = mtime();
		std::stable_sort(begin(v), end(v));
		LOG("std::stable_sort " << std::setw(10) << mtime() - t << " ms");
		assert(v1 == v);
	}

	{
		std::vector<TDigit> v = v0;
		auto t = mtime();
		radixSort(v);
		LOG("radixSort        " << std::setw(10) << mtime() - t << " ms");
		assert(v1 == v);
	}

	if (size <= 100000)
	{
		std::vector<TDigit> v = v0;
		auto t = mtime();
		bubbleSort(v);
		LOG("bubbleSort       " << std::setw(10) << mtime() - t << " ms");
		assert(v1 == v);
	}
}

int main(int argc, char **argv) {
	srand(time(NULL));

	int size = 10;
	if (argc > 1) {
		size = atol(argv[1]);
	}
	LOG1(size);
	test<uint8_t>(size);
	test<uint16_t>(size);
	test<uint32_t>(size);
	test<uint64_t>(size);

	return 0;
}
