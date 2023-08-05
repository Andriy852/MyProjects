#include <iostream>
#include <cassert>
#include <cctype>
#include <string>
#include <vector>
#include <utility>
#include <climits>
using namespace std;
using std::vector;
using std::string;
using std::max;
using std::min;
/*
Maximum Value of an Arithmetic Expres- sion Problem
Parenthesize an arithmetic expression to maxi- mize its value.
*/
long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
}
}

pair <long long, long long> MinandMax(int i, int j, vector <char> &operations, vector <vector <long long>> &Max, vector <vector <long long>> &Min){
  long long min_n = INT_MAX;
  long long max_n = INT_MIN;
  for (int k = i;k<j;k++){
      long long a = eval(Max[i][k],Max[k+1][j],operations[k]);
      long long b = eval(Max[i][k],Min[k+1][j],operations[k]);
      long long c = eval(Min[i][k],Max[k+1][j],operations[k]);
      long long d = eval(Min[i][k],Min[k+1][j],operations[k]);
      min_n = min(min(min_n, a), min(min(b,c),d));
      max_n = max(max(max_n, a), max(max(b,c),d));
  }
  return make_pair(min_n,max_n);
}

long long get_maximum_value(const string &exp) {
  int n = exp.size()/2+1;
  vector <int> numbers;
  vector <char> operations;
  for (char ch: exp){
    if (isdigit(ch)){
       numbers.push_back(ch-'0');
    }
    else{
      operations.push_back(ch);
    }
  }
  vector <vector <long long>> Max(n, vector <long long>(n, 0));
  vector <vector <long long>> Min(n, vector <long long>(n, 0));
  for (int i = 0;i<n;i++){
    Max[i][i] = numbers[i];
    Min[i][i] = numbers[i];
  }
  for (int s = 1; s<=n-1;s++){
    for (int i = 0; i<n-s;i++){
        int j = i+s;
        pair<long long, long long> max_min = MinandMax(i, j, operations, Max, Min);
        Max[i][j] = max_min.second;
        Min[i][j] = max_min.first;
    }
  }
  return Max[0][n-1];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}

