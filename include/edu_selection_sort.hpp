#ifndef __EDU_SELECTION_SORT_HPP__
#define __EDU_SELECTION_SORT_HPP__
#include <iostream>
#include <utility>

#include <functional>
#include <iterator>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace edu {
template <typename RandomAccessIterator_, typename Cmp>
inline void selection_sort(RandomAccessIterator_ first,
                           RandomAccessIterator_ last, Cmp cmp) {

  auto test_f = first;
  auto test_l = last;

  while (first < last) {
    auto min = first;
    for (auto jt = first + 1; jt < last; ++jt) {
      if (cmp(*jt, *min)) {
        min = jt;
      }
    }
    std::swap(*first, *min);

    ++first;
  }
}

template <typename RandomAccessIterator_>
inline void selection_sort(RandomAccessIterator_ first,
                           RandomAccessIterator_ last) {
  selection_sort(first, last, std::less<>{});
}

} // namespace edu

#endif