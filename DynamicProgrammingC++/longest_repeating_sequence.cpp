#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
A longest repeating sub- sequence of this string. 
Two sub-sequences of a string form a re- peating subsequence 
if they spell the same string but do not share positions in the string.
*/
string longest_repeating_subsequence(string str){
    if (str.size()<=1) return "";
    char letter = str[0];
    string new_str;
    bool there{false};
    for (int i = 1;i<str.size();i++){
        if(letter==str[i]){
            there = true;
            continue;
        }
        new_str+=str[i];
    }
    if (there) return str[0]+longest_repeating_subsequence(new_str);
    else return longest_repeating_subsequence(new_str);
} 


int main(){
    cout<<longest_repeating_subsequence("ababcad")<<endl;
}