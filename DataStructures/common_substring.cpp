#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <unordered_map>
/*
Input Format. Every line of the input contains two strings 𝑠 and 𝑡 
consisting of lower case Latin letters.
For each pair of strings 𝑠 and 𝑡, find its longest common substring and specify 
it by outputting three integers: its starting position in 𝑠, its starting position 
in 𝑡 (both 0-based), and its length.
*/

struct Answer {
	int i, j, len;
};


long long poly_hash(int p, long long mod, int left, int right, const string &s){
	long long hash = 0;
	for (int i = right;i>=left;i--){
		hash = (hash*p + s.at(i))%mod;
	}
	return hash;
}

unordered_map <long long, int> compute_hashes(int length, const string &s, long long mod, int p, long long p_pow){
	unordered_map <long long, int> hashes(s.size()-length+1);
	long long res = poly_hash(p, mod, s.size()-length, s.size()-1, s);
	hashes[res] = s.size()-length;
	for (int i = s.size()-length-1;i>=0;i--){
		long long term1 = (p * res) % mod;
        long long term2 = (p_pow * s.at(i + length)) % mod;
        res = ((term1 + s.at(i) - term2) + mod) % mod;
		hashes[res] = i;
	}
	return hashes;

}

Answer find_match(const string &larger, const string &smaller, int length){
	long long m1 = 1000000009;
	long long m2 = 1000000007;
	int p1 = 37;
	int p2 = 37;
	long long p_pow1 = 1;
	long long p_pow2 = 1;
	for (int i = 0;i<length;i++){
		p_pow1 = (p_pow1*p1)%m1;
		p_pow2 = (p_pow2*p2)%m2;
	}
	unordered_map <long long, int> hash1 = compute_hashes(length, smaller, m1, p1, p_pow1);
	unordered_map <long long, int> hash2 = compute_hashes(length, smaller, m2, p2, p_pow2);
	long long hashed_1 = poly_hash(p1, m1, larger.size()-length,larger.size()-1, larger);
	long long hashed_2 = poly_hash(p2, m2, larger.size()-length,larger.size()-1, larger);
	for (int i = larger.size()-2;i>=length-2;i--){
		if (hash1.find(hashed_1)!=hash1.end() && hash2.find(hashed_2)!=hash2.end()){
			Answer ans = {hash1.find(hashed_1)->second, i-length+2, length};
			return ans;
		}
		if (i!=length-2){
			long long term1_1 = (p1 * hashed_1) % m1;
			long long term2_1 = (p_pow1 * larger.at(i + 1)) % m1;
			hashed_1 = ((term1_1 + larger.at(i-length+1) - term2_1) + m1) % m1;

			long long term1_2 = (p2 * hashed_2) % m2;
			long long term2_2 = (p_pow2 * larger.at(i + 1)) % m2;
			hashed_2 = ((term1_2 + larger.at(i-length+1) - term2_2) + m2) % m2;
		}
	}
	Answer ans = {0,0,0};
	return ans;
}

Answer solve(const string &s, const string &t) {
	Answer ans = {0,0,0};
	int left = 0;
	int right = min(t.size(), s.size());
	int mid = 0;
	while (left<=right){
		mid = ((left + right) / 2);
		Answer found;
		if (s.size()>t.size()){
			found = find_match(s, t, mid);
			swap(found.i, found.j);
		}
		else{
			found = find_match(t, s, mid);
		}
		if (found.len>ans.len){
			ans = found;
			left = mid+1;
		}
		else
			right = mid-1;
	}
	return ans;
}


int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
