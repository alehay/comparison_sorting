#ifndef __EDU_HEAP_SORT_HPP__
#define __EDU_HEAP_SORT_HPP__

#include <functional>
#include <iterator>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace edu {

template <class RandomIt, class Compare>
inline void heapify(RandomIt first, RandomIt last, RandomIt i, Compare cmp) {
  auto size = std::distance(first, last);
  
  auto double_dist = 2 * std::distance(first, i); 
  auto largest = i;
  auto l = first + double_dist + 1;
  auto r = first + double_dist + 2;

  if (l < last && !cmp(*l, *largest))
    largest = l;

  if (r < last && !cmp(*r, *largest))
    largest = r;

  if (largest != i) {
    std::iter_swap(i, largest);
    heapify(first, last, first + std::distance(first, largest), cmp);
  }
}


template <class RandomIt, class Compare>
inline void heap_sort(RandomIt first, RandomIt last, Compare cmp ) {
  auto size = std::distance(first, last);

  for (auto i = size / 2 - 1; i >= 0; --i)
    heapify(first, last, first + i, cmp);

  for (auto i = size - 1; i > 0; --i) {
    std::iter_swap(first, first + i);
    heapify(first, first + i, first, cmp);
  }
}

template <class RandomIt>
inline void heap_sort(RandomIt first, RandomIt last) {
  heap_sort(first, last, std::less<>{});
}


} // namespace edu

#endif