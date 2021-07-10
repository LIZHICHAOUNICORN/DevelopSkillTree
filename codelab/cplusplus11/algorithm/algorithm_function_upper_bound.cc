// Author: zhichaoli
// Time: 2021-07-10

#include <algorithm>

#ifdef USE_GLOG

#include "glog/logging.h"
#include "gflags/gflags.h"

#else

#include <iostream>

#endif
#include <algorithm>
#include <iostream>
#include <vector>

/*
// implements: binary search

template<class ForwardIt, class T, class Compare>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
{
    ForwardIt it;
    typename std::iterator_traits<ForwardIt>::difference_type count, step;
    count = std::distance(first, last);
 
    while (count > 0) {
        it = first; 
        step = count / 2;
        std::advance(it, step);
        if (!comp(value, *it)) {
            first = ++it;
            count -= step + 1;
        } 
        else
            count = step;
    }
    return first;
}
*/


 
struct PriceInfo { double price; };
 
int main()
{
    const std::vector<int> data = { 1, 2, 4, 5, 5, 6 };
    for (int i = 0; i < 7; ++i) {
        // Search first element that is greater than i
        auto upper = std::upper_bound(data.begin(), data.end(), i);
 
        std::cout << i << " < ";
        upper != data.end()
            ? std::cout << *upper << " at index " << std::distance(data.begin(), upper)
            : std::cout << "not found";
        std::cout << '\n';
    }
 
    std::vector<PriceInfo> prices = { {100.0}, {101.5}, {102.5}, {102.5}, {107.3} };
    for(double to_find: {102.5, 110.2}) {
      auto prc_info = std::upper_bound(prices.begin(), prices.end(), to_find,
          [](double value, const PriceInfo& info){
              return value < info.price;
          });
 
      prc_info != prices.end()
          ? std::cout << prc_info->price << " at index " << prc_info - prices.begin()
          : std::cout << to_find << " not found";
      std::cout << '\n';
    }
}
