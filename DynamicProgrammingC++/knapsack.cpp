#include <iostream>
#include <vector>
using namespace std;
using std::vector;
/*

Maximum Amount of Gold Problem
Given a set of gold bars of various weights and a backpack that 
can hold at most W pounds, place as much gold as possible into the backpack.
*/
int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  vector <vector <int>> max_weights(w.size()+1,vector<int>(W+1,0));
  for (size_t i = 1;i<=w.size();i++){
      for (size_t weight = 1;weight<=W;weight++){
          max_weights[i][weight] = max_weights[i-1][weight];
          if (w[i-1]<=weight){
              int val = max_weights[i-1][weight-w[i-1]] + w[i-1];
              if (val>max_weights[i][weight]) max_weights[i][weight] = val;
          }
      }
  }
  return max_weights[w.size()][W];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
