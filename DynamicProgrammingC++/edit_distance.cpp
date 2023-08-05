#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using std::string;

/*
Edit Distance Problem
Compute the edit distance between two strings.
The minimum number of single-symbol insertions, 
deletions, and substitutions to transform one string into the other one.
*/
int edit_distance(const string &str1, const string &str2) {
  vector <vector <int>> editing_matrix(str1.size()+1,vector <int>(str2.size()+1, 0));
  for (size_t i = 0;i<str2.size()+1;++i){
      editing_matrix[0][i] = i;
  }
  for (size_t j = 0;j<str1.size()+1;++j){
      editing_matrix[j][0] = j;
  }
  for (size_t i = 1;i<str1.size()+1;++i){
      for (size_t j = 1;j<str2.size()+1;++j){
        int difference = 1;
          if (str1[i-1]==str2[j-1]){
              difference = 0;
          }
          editing_matrix[i][j] = min(editing_matrix[i-1][j]+1,  
                                    min(editing_matrix[i][j-1]+1, editing_matrix[i-1][j-1]+difference));
     }
  }
  return editing_matrix[str1.size()][str2.size()];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
