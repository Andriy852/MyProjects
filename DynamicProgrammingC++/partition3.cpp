#include <iostream>
#include <vector>

using std::vector;
using namespace std;

/*
3-Partition Problem
Partition a set of integers into three subsets with equal sums.
Check whether it is pos- sible to partition them into three subsets with equal sums
*/
bool subsetsum(vector <int> const &numbers, int n, int a, int b, int c){
  if (a==0 && b==0 && c==0) return true;
  if (n<0) return false;
  bool A = false;
  if (a-numbers[n]>=0){
      A = subsetsum(numbers,n-1,a-numbers[n],b,c);
  }
  bool B = false;
  if (!A && (b-numbers[n]>=0)){
      B = subsetsum(numbers,n-1,a,b-numbers[n],c);
  }
  bool C = false;
  if ((!A && !B) && (c-numbers[n]>=0)){
      C = subsetsum(numbers,n-1,a,b,c-numbers[n]);
  }
  return A || B || C;
}

int partition3(vector<int> &A) {
  int sum = 0;
  for (int number: A) sum+=number;
  double mean = static_cast<double>(sum)/3;
  if (mean != static_cast<int>(mean)) return 0;
  return subsetsum(A,A.size()-1,mean,mean,mean);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
