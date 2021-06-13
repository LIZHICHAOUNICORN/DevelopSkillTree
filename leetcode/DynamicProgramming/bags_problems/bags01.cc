#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;


int MaxValue1D(const vector<int>& weights, const vector<int>& values, const int bag_weight) {
  vector<int> dp(bag_weight+1, 0);
  for (int i = 0; i < weights.size(); ++i) {
    for (int j = bag_weight; j >= weights[i]; --j) {
      dp[j] = std::max(dp[j], dp[j - weights[i]] + values[i] );
    }
  }
  return dp[bag_weight];
}

int MaxValue2D(const vector<int>& weights, const vector<int>& values, const int bag_weight) {
  // dp array
  int m = weights.size();
  int n = bag_weight + 1;
  vector<vector<int>> dp(m, vector<int>(n, 0));
  // initial
  for (int j = bag_weight; j >= weights[0]; --j) {
    dp[0][j] = dp[0][j - weights[0]] + values[0];
  }

  // Number of weights;
  for (int i = 1; i < weights.size(); ++i) {
    for (int j = 0; j <= bag_weight; ++j) {
      if (j < weights[i]) {
        dp[i][j] = dp[i-1][j];
      } else {
        dp[i][j] = std::max(dp[i-1][j], dp[i - 1][j - weights[i]] + values[i]);
      }
    }
  } 
//  for (int i = 0; i < dp.size(); ++i) {
//    for (int j = 0; j < dp[i].size(); ++j) {
//      std::cout << dp[i][j] << ", ";
//    }
//    std::cout << " " << std::endl;
//  }
  return dp[m-1][n-1];

}

int main(int argc, char* argv[]) {
  vector<int> weights {1, 3, 4};
  vector<int> values {15, 20, 30};

  int bag_weight = 4;

  int max_value = MaxValue2D(weights, values, bag_weight);
  std::cout << "2D Max bag value is : " << max_value << std::endl;

  max_value = MaxValue1D(weights, values, bag_weight);
  std::cout << "1D Max bag value is : " << max_value << std::endl;
  return 0;
}

