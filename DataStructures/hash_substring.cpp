#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
typedef unsigned long long ull;


/*Input Format. There are two strings in the input: the pattern 𝑃 and the text 𝑇 .
Output Format. Print all the positions of the occurrences of 𝑃 in 𝑇 in the ascending order. 
Use 0-based indexing of positions in the the text 𝑇.
*/

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

ull polyhash(int x, ull p, string s, int left, int right){ // hash the string and get the number between 1 and  p-1
    ull hash = 0;
    for (int i = left;i<=right;++i)
        hash = (hash*x+s[i])%p;
    return hash;
}

bool areequal(const string &pattern, const string &text, size_t start){
    for (size_t i = 0;i<pattern.size();i++){
        if (pattern.at(i)!=text.at(i+start))
            return false;
    }
    return true;
}

vector <ull> computehashes(int pattern_size, const string &text, ull p, ull x){
    vector <ull> hashes(text.size()-pattern_size+1);
    // hash of the last substring
    hashes.at(text.size()-pattern_size) = polyhash(x, p, text, text.size()-pattern_size, text.size()-1);
    ull y = 1;
    for (int i = 1;i<=pattern_size;i++)
        y = (y*x)%p;
    
    for (int i=text.size()-pattern_size-1;i>=0;i--)
        hashes.at(i) = ((x*hashes.at(i+1)+text.at(i)-y*text.at(i+pattern_size))%p+p)%p;
    
    return hashes;
}

vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    ull p = 10000007;
    ull x = 1;
    ull hashed_string = polyhash(x, p, s, 0, s.size()-1);
    vector <ull> hashes = computehashes(s.size(), t, p, x);
    for (size_t i = 0; i + s.size() <= t.size(); ++i){
        if (hashes.at(i)!=hashed_string)
            continue;
        if (areequal(s, t, i))
            ans.push_back(i);       
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
