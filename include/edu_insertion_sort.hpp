#ifndef __EDU_INSERTION_SORT_HPP__
#define __EDU_INSERTION_SORT_HPP__

#include <iostream>
#include <iterator>
#include <functional>

namespace edu {

template <typename T, typename Iterator_, typename Compare_>
inline Iterator_ binary_Search(T item, Iterator_ first, Iterator_ last,
                               Compare_ comp) {

  while (first < last) {
    Iterator_ mid = first + (std::distance(first, last) / 2);

    if (!comp(item, *mid) && !comp(*mid, item)) {
      return mid;
    }

    if (comp(item, *mid)) {
      last = mid;
    }

    if (comp(*mid, item)) {
      first = mid + 1;
    }
  }

  if (comp(first, last)) {
    return first;
  }

  return last;
}

template <typename RandomAccessIterator_, typename Cmp>
inline void insertion_sort(RandomAccessIterator_ first,
                           RandomAccessIterator_ last, Cmp cmp) {
  for (auto it = first + 1; it < last; ++it) {
    auto jt = it - 1;
    auto selected = *it;
    // fin insert position
    auto loc = binary_Search(selected, first, jt + 1, cmp);
    while (jt >= loc) {
      *(jt + 1) = *jt;
      --jt;
    }
    *loc = selected;
  }
}

template <typename RandomAccessIterator_>
inline void insertion_sort(RandomAccessIterator_ first,
                           RandomAccessIterator_ last) {
  insertion_sort(first, last, std::less<>{});
}

} // namespace edu

#endif