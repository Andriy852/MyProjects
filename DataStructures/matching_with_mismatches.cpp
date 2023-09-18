#include <iostream>
#include <vector>

/*

Task. For an integer parameter 𝑘 and two strings 𝑡 = t[0..m-1] and 𝑝 = 𝑝[0..n-1], 
we say that 𝑝 occurs in 𝑡 at position 𝑖 with at most 𝑘 mismatches if the strings 
𝑝 and t[i:i+p] = t[i..i+n-1] differ in at most 𝑘 positions.
Input Format. Every line of the input contains an integer 𝑘 and two strings 𝑡 and 
𝑝 consisting of lower case Latin letters.
Output Format. For each triple (𝑘,𝑡,𝑝), find all positions 0 ≤ i< |𝑡| 
where 𝑝 occurs in 𝑡 with at most 𝑘 mismatches. Output 𝑙 and all i.
*/

using namespace std;

class Solution{
	string t;
	string p;
	long long mod;
	int x;
	int k;
	vector <long long> x_pow;
	vector <long long> t_hashes;
	vector <long long> p_hashes;
public:
	Solution(string t, string p, int k, int x, long long mod):t{t}, p{p}, mod{mod}, x{x}, k{k}{
		x_pow.resize(p.size()+1);
		t_hashes.resize(t.size()+1);
		p_hashes.resize(p.size()+1);
		x_pow.at(0) = 1;
		for (int i = 1;i<=p.size();i++){
			x_pow.at(i) = (x_pow.at(i-1)*x)%mod;
		}
		t_hashes = precompute_hashes(t);
		p_hashes = precompute_hashes(p);
	}
	vector <long long> precompute_hashes(const string &str){
		vector <long long> hash_table(str.size()+1);
		for (int i = 1;i<hash_table.size();i++)
			hash_table.at(i) = (hash_table.at(i-1)*x + str.at(i-1))%mod;
		return hash_table;
	}
	long long compute_hash(const vector <long long> &str_hashes, int left, int right){
		return ((str_hashes.at(right+1) - x_pow.at(right-left+1)*str_hashes.at(left))%mod+mod)%mod;
	}
	int count_mismatches(int starting_index, int pattern_left, int pattern_right){
		int mid = (pattern_left+pattern_right)/2;
		int mismatches = 0;
		if (t.at(starting_index+mid)!=p.at(mid))
			mismatches++;
		if (mismatches>k)
			return mismatches;
		if (mid>pattern_left){
		if (compute_hash(t_hashes, starting_index+pattern_left, starting_index+mid-1)!=compute_hash(p_hashes, pattern_left, mid-1))
			mismatches += count_mismatches(starting_index, pattern_left, mid-1);
		}
		if (mismatches>k)
			return mismatches;
		if (mid<pattern_right){
		if (compute_hash(t_hashes,starting_index+mid+1, starting_index+pattern_right)!=compute_hash(p_hashes, mid+1, pattern_right))
			mismatches += count_mismatches(starting_index, mid+1, pattern_right);
		}
		return mismatches;
}

};


vector<int> solve(int k, const string &text, const string &pattern) {
	Solution solution(text, pattern, k, 31, 1000000007);
	vector<int> pos;
	for (int i = 0;i<=text.size()-pattern.size();i++){
		if (solution.count_mismatches(i, 0, pattern.size()-1)<=k)
			pos.push_back(i);
	}

	return pos;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
