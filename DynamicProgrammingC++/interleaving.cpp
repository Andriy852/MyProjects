#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
// Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
bool isinterleave(string s1, string s2, string s3){
    vector<vector<bool>> dp(s1.size()+1, vector<bool>(s2.size()+1, true));
    if (s1.size()+s2.size()!=s3.size()) return false;
    for (int i = 0;i<=s1.size();i++){
        for(int j = 0;j<=s2.size();j++){
            if (i==0 && j!=0){
                if (s2[j-1]==s3[j-1]) dp[i][j] = dp[i][j-1];
                else dp[i][j] = false;
            }
        else if (j==0 && i!=0){
            if (s1[i-1]==s3[i-1]) dp[i][j] = dp[i-1][j];
            else dp[i][j] = false;
        }
        else if (j!=0 && i!=0){
            bool res1{false};
            bool res2{false};
            if (s1[i-1]==s3[i+j-1]){
                res1 = dp[i-1][j];
            }
            if (s2[j-1]==s3[i+j-1]){
                res2 = dp[i][j-1];
            }
            if (res1||res2) dp[i][j] = true;
            else dp[i][j] = false;
        }
        }
    }
    return dp[s1.size()][s2.size()];
    }


int main(){
    cout<<boolalpha<<isinterleave("aabc", "abad", "aabadabc")<<endl;
    return 0;
}