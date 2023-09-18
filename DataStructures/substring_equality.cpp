#include <iostream>
#include <vector>
#include <utility>
/*
Input Format. The first line contains a string 𝑠 consisting of small Latin letters. 
The second line contains the number of queries 𝑞. Each of the next 𝑞 lines specifies a 
query by three integers 𝑎, 𝑏, and 𝑙.
Output Format. For each query, output “Yes” if s[a..a+l-1]= s[b..b+l-1] are equal, 
and “No” otherwise.
*/


using namespace std;

class Solver {
	string s;
	long long m1;
	long long m2;
	vector <long long> hashes_1;
	vector <long long> hashes_2;
	vector <long long> power_x1;
	vector <long long> power_x2;	
	int x;
public:	
	Solver(string s) : s(s) {	
		x = 7;
		m1 = 1000000007;
		m2 = 1000000009;
		power_x1.resize(s.size());
		power_x2.resize(s.size());
		hashes_1.resize(s.size()+1);
		hashes_2.resize(s.size()+1);
		power_x1.at(0) = power_x2.at(0) = x;
		for (int i = 1;i < s.size();i++){
			power_x1.at(i) = (power_x1.at(i-1)*x)%m1;
			power_x2.at(i) = (power_x2.at(i-1)*x)%m2;
		}
		precompute_hashes();

	}
	bool ask(int a, int b, int l) {
		long long hash_a1 = ((hashes_1.at(a+l) - power_x1[l-1]*hashes_1.at(a))%m1+m1)%m1;
		long long hash_a2 = ((hashes_2.at(a+l) - power_x2[l-1]*hashes_2.at(a))%m2+m2)%m2;

		long long hash_b1 = ((hashes_1.at(b+l) - power_x1[l-1]*hashes_1.at(b))%m1+m1)%m1;
		long long hash_b2 = ((hashes_2.at(b+l) - power_x2[l-1]*hashes_2.at(b))%m2+m2)%m2;

		if (hash_a1==hash_b1 && hash_a2 == hash_b2)
			return true;
		return false;
	}


	void precompute_hashes(){
		for (int i = 1;i<hashes_1.size();i++){
			hashes_1.at(i) = (hashes_1.at(i-1)*x + s.at(i-1))%m1;
			hashes_2.at(i) = (hashes_2.at(i-1)*x + s.at(i-1))%m2;
		}
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
