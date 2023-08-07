#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

//converting array into a heap
class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }


  void sift_down(int index){
    int min_index = index;
    int left_child = 2*index+1;
    if (left_child<data_.size() && data_.at(left_child)<data_.at(min_index))
      min_index = left_child;
    int right_child = 2*index+2;
    if (right_child<data_.size() && data_.at(right_child)<data_.at(min_index))
      min_index = right_child;
    if (min_index!=index){
        swaps_.push_back(make_pair(index, min_index));
        swap(data_.at(min_index), data_.at(index));
        sift_down(min_index);
    }
  
  }

  void GenerateSwaps() {
    swaps_.clear();
    for (int i = data_.size()/2; i >= 0; --i){
        sift_down(i);
    }
    
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
