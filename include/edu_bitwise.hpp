#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// educational
namespace edu
{
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdint>
#include <limits>

template<typename RandomIt>
void radix_sort(RandomIt begin, RandomIt end) {
    using T = typename std::iterator_traits<RandomIt>::value_type;
    static_assert(std::is_integral<T>::value, "Radix sort requires integral type");

    const int BITS = sizeof(T) * 8;
    const int RADIX = 8;
    const int BUCKETS = 1 << RADIX;
    const int MASK = BUCKETS - 1;

    std::vector<T> temp(std::distance(begin, end));
    int counts[BUCKETS];

    for (int shift = 0; shift < BITS; shift += RADIX) {
        std::fill(counts, counts + BUCKETS, 0);

        for (RandomIt it = begin; it != end; ++it) {
            ++counts[(*it >> shift) & MASK];
        }

        for (int i = 1; i < BUCKETS; ++i) {
            counts[i] += counts[i - 1];
        }

        for (RandomIt it = std::prev(end); it >= begin; --it) {
            temp[--counts[(*it >> shift) & MASK]] = *it;
        }

        std::copy(temp.begin(), temp.end(), begin);
    }

    // Handle negative numbers
    if (std::is_signed<T>::value) {
        RandomIt middle = std::partition(begin, end, [](const T& x) { return x < 0; });
        std::reverse(begin, middle);
    }
}


}