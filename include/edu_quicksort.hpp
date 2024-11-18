#ifndef __EDU_QUICK_SORT_HPP__
#define __EDU_QUICK_SORT_HPP__

#include <functional>
#include <iterator>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace edu {

template <typename RandomIt, typename Cmp>
inline RandomIt partition(RandomIt first, RandomIt last, Cmp &cmp) {
  auto pivot = std::prev(last, 1);
  auto i = first;
  for (auto j = first; j != pivot; ++j) {
    if (cmp(*j, *pivot)) {
      std::iter_swap(i++, j);
    }
  }
  std::iter_swap(i, pivot);
  return i;
}

template <typename RandomIt, typename Cmp>
inline void quickSort(RandomIt first, RandomIt last, Cmp cmp) {
  if (std::distance(first, last) < 2) {
    return;
  }
  auto p = edu::partition(first, last, cmp);
  quickSort(first, p, cmp);
  quickSort(p + 1, last, cmp);
}

template <typename RandomIt>
inline void quickSort(RandomIt first, RandomIt last) {
  quickSort(first, last, std::less<>{});
}

} // namespace edu

#endif