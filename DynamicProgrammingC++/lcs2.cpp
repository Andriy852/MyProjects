#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Longest Common Subsequence of Two Se- quences Problem
Compute the maximum length of a common subsequence of two sequences.
*/
int lcs2(vector<int> &a, vector<int> &b) {
  int dp[a.size()+1][b.size()+1];
  for (size_t i = 0;i<=a.size();i++){
      for (size_t j = 0;j<=b.size();j++){
          if (i == 0 || j == 0 ){
              dp[i][j] = 0;
          }
          else if (a[i-1]==b[j-1]){
              dp[i][j] = dp[i-1][j-1]+1;
          }
          else{
              dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
          }
      }
  }
  return dp[a.size()][b.size()];
}


int main() {

  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }
  int res = lcs2(a, b);
  std::cout << res << std::endl;
}
