#ifndef __EDU_BUBBLE_SORT_HPP__
#define __EDU_BUBBLE_SORT_HPP__

#include <utility>

#include <functional>
#include <iterator>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

// educational
namespace edu {

template <typename RandomAccessIterator_, typename Cmp>
inline void bubble_sort(RandomAccessIterator_ first, RandomAccessIterator_ last,
                        Cmp cmp) {

  while (first < last - 1) {
    bool swapped = false;
    for (auto it = first; it < last - 1; ++it) {
      if (!cmp(*it, *(it + 1))) {
        std::swap(*it, *(it + 1));
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
    --last;
  }
  return;
}

template <typename RandomAccessIterator_>
inline void bubble_sort(RandomAccessIterator_ first,
                        RandomAccessIterator_ last) {

  bubble_sort(first, last, std::less<>{});
}

} // namespace edu
#endif