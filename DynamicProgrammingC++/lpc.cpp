#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>
/*
Longest Palindromic Subsequence Problem
Given a string, find a longest palindromic subsequence of this string,
 i.e., a subsequence that reads the same backward and forward.
 */

int lps(string s){
    vector <vector <int>> results(s.size(), vector <int>(s.size(),0));
    for (int i = 0;i<s.size();i++){
        results[i][i] = 1;
    }
    for (int k = 1;k<s.size();k++){
        for (int i = 0;i<s.size()-k;i++){
            int j = i+k;
            if (s[i]==s[j]){
                results[i][j] = results[i+1][j-1]+2;
            }
            else{
                results[i][j] = max(results[i+1][j],results[i][j-1]);
            }
        }
    }
   return results[0][s.size()-1];
}


int main(){
    string s;
    cin>>s;
    cout<<lps(s)<<endl;
}