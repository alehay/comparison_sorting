#ifndef __EDU_SHELL_SORT_HPP__
#define __EDU_SHELL_SORT_HPP__
#include <functional>
#include <iterator>

namespace edu {

template <typename RandomAccessIterator_, typename Compare_>
inline void shell_sort(RandomAccessIterator_ first, RandomAccessIterator_ last,
                       Compare_ comp) {

  for (std::size_t interval = std::distance(first, last) / 2; interval > 0;
       interval /= 2) {
    for (RandomAccessIterator_ it = first + interval; it < last; ++it) {
      auto temp = *it;
      RandomAccessIterator_ jt = it;
      for (; jt >= interval + first && comp(temp, *(jt - interval));
           jt -= interval) {
        *jt = *(jt - interval);
      }
      *jt = temp;
    }
  }
}

template <typename RandomAccessIterator_>
inline void shell_sort(RandomAccessIterator_ first,
                       RandomAccessIterator_ last) {
  shell_sort(first, last, std::less<>{});
}
} // namespace edu
#endif