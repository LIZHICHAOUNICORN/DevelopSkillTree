#ifndef STRING_ALGORITHMS_BOYER_MOORE_
#define STRING_ALGORITHMS_BOYER_MOORE_

#include <string>
#include <vector>

using namespace std;

namespace base {
class BM {
 private:
  void GetBadChar(const string& pattern, vector<int>& bad_char);
  void GetSuff(const string& pattern, vector<int>& suff);
  void GetGoodSuff(const string& pattern, vector<int>& good_suff);

 public:
  int Search(const std::string& src, const std::string& pattern);
};
}  // namespace base

#endif  // STRING_ALGORITHMS_BOYER_MOORE_
