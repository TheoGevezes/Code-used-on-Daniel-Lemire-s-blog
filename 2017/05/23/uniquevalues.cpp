
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include "benchmark.h"

size_t distinct_count_hash(const uint64_t * values, size_t howmany) {
  std::unordered_set<uint64_t> hash(values, values + howmany, howmany);
  return hash.size();
}

size_t distinct_count_sort(const uint64_t * values, size_t howmany) {
  std::vector<uint64_t> array(values, values + howmany);
  std::sort(array.begin(), array.end());
  return std::unique(array.begin(), array.end()) - array.begin();
}

void demo(size_t N) {
    std::cout << "N = " << N <<std::endl;
    uint64_t * values = new uint64_t[N];
    for(size_t i = 0; i < N; ++i) {
      values[i] = rand();
    }
    for(size_t i = rand() % N ; i < N; ++i) {
      values[i] = values[0]; 
    }
    size_t expected = distinct_count_hash(values,N);
    std::cout <<" expected = "<<expected << std::endl;
    const int repeat = 1;
    BEST_TIME(distinct_count_hash(values,N), expected, , repeat, N, true);
    BEST_TIME(distinct_count_sort(values,N), expected, , repeat, N, true);
    delete[] values;
}
int main() {
  for(size_t N = 100; N < 100000000; N*=10) demo(N);
}
