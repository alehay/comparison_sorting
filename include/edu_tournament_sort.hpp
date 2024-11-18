#ifndef __EDU_TOURNAMENT_SORT_HPP__
#define __EDU_TOURNAMENT_SORT_HPP__

#include <functional>
#include <iterator>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace edu {
/*
template <typename RandomAccessIterator_, typename Compare_>
inline void tournament_sort(RandomAccessIterator_ first,
                            RandomAccessIterator_ last, Compare_ comp) {

  std::vector<RandomAccessIterator_> bin_heap;
  bin_heap.reserve(std::distance(first, last) / 2 + 1);

  int iter{0};
  for (; first < last; ++first) {

    auto dist = std::distance(first, last);

    for (auto it = first; it < last - 1; it += 2) {
      if (comp(*it, *(it + 1))) {
        bin_heap.push_back(it);
        continue;
      }
      bin_heap.push_back((it + 1));
    }
    if (dist & 1) {
      bin_heap.push_back(last - 1);
    }

    while (bin_heap.size() > 1) {

      std::size_t jt = 0;

      bool odd = bin_heap.size() & 1;

      for (std::size_t i = 0; i < bin_heap.size() - 1; i += 2) {
        if (comp(*bin_heap[i], *bin_heap[i + 1])) {
          bin_heap[jt] = bin_heap[i];
        } else {
          bin_heap[jt] = bin_heap[i + 1];
        }
        ++jt;
      }
      if (odd) {
        bin_heap[jt] = bin_heap.back();
        ++jt;
      }

      bin_heap.resize(jt);

      jt = 0;
    }

    std::swap(*first, *(bin_heap[0]));
    bin_heap.clear();
  }
}*/

template <typename RandomAccessIterator, typename Compare>
inline void tournament_sort(RandomAccessIterator first,
                            RandomAccessIterator last, Compare comp) {
  std::vector<size_t> bin_heap;
  bin_heap.reserve(std::distance(first, last) / 2 + 1);

  for (; first < last; ++first) {
    size_t dist = std::distance(first, last);

    for (RandomAccessIterator it = first; it < last - 1; it += 2) {
      size_t winner = comp(*it, *(it + 1)) ? std::distance(first, it)
                                           : std::distance(first, it + 1);
      bin_heap.push_back(winner);
    }

    if (dist & 1) {
      bin_heap.push_back(std::distance(first, last - 1));
    }

    while (bin_heap.size() > 1) {
      size_t jt = 0;
      bool odd = bin_heap.size() & 1;

      for (size_t i = 0; i < bin_heap.size() - 1; i += 2) {
        size_t winner = comp(*(first + bin_heap[i]), *(first + bin_heap[i + 1]))
                            ? bin_heap[i]
                            : bin_heap[i + 1];
        bin_heap[jt++] = winner;
      }

      if (odd) {
        bin_heap[jt++] = bin_heap.back();
      }

      bin_heap.resize(jt);
    }

    std::iter_swap(first, first + bin_heap[0]);
    bin_heap.clear();
  }
}

template <typename RandomAccessIterator_>
inline void tournament_sort(RandomAccessIterator_ first,
                            RandomAccessIterator_ last) {
  tournament_sort(first, last, std::less<>{});
}

} // namespace edu

#endif