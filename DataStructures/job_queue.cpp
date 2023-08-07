#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

/*
You have a program which is parallelized and uses 𝑛 independent threads to 
process the given list of 𝑚 jobs. Threads take jobs in the order they are given in 
the input. If there is a free thread, it immediately takes the next job from the list. 
If a thread has started processing a job, it doesn’t interrupt or stop until it finishes 
processing the job. If several threads try to take jobs from the list simultaneously, 
the thread with smaller index takes the job. For each job you know exactly 
how long will it take any thread to process this job, and this time is the same for 
all the threads. You need to determine for each job which thread will process it and 
when will it start processing
*/
struct node{
  long long finishing_time;
  int index;
};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void sift_down(int index_el, vector<node> &workers_heap){
    int min_index = index_el;
    int left_child = 2*index_el+1;
    if (left_child<workers_heap.size()){
      if (workers_heap.at(left_child).finishing_time<workers_heap.at(min_index).finishing_time)
          min_index = left_child;
      else if (workers_heap.at(left_child).finishing_time==workers_heap.at(min_index).finishing_time){
        if (workers_heap.at(left_child).index<workers_heap.at(min_index).index)
          min_index = left_child;
      }
    } 
    int right_child = 2*index_el + 2;
    if (right_child<workers_heap.size()){
      if (workers_heap.at(right_child).finishing_time<workers_heap.at(min_index).finishing_time)
          min_index = right_child;
      else if (workers_heap.at(right_child).finishing_time==workers_heap.at(min_index).finishing_time){
        if (workers_heap.at(right_child).index<workers_heap.at(min_index).index)
          min_index = right_child;
      }
    }
      
    if (right_child<workers_heap.size() && left_child<workers_heap.size()&&
          workers_heap.at(left_child).finishing_time==workers_heap.at(right_child).finishing_time){
            if (workers_heap.at(left_child).index<workers_heap.at(right_child).index)
              min_index = left_child;
            else  
              min_index = right_child;
          }
    if (min_index!=index_el){
      std::swap(workers_heap.at(index_el), workers_heap.at(min_index));
      sift_down(min_index, workers_heap);
    }
  }

  void change_finishtime(int index, vector<node> &workers_heap, long long value){
      workers_heap.at(index).finishing_time = value;
      sift_down(index, workers_heap);
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector <node> workers_heap(num_workers_);
    for (size_t i = 0;i<num_workers_;i++){
      workers_heap[i].index = i; // setting indeces for each node
    }
    for (size_t i = 0;i<jobs_.size();i++){
      assigned_workers_[i] = workers_heap.at(0).index;
      start_times_[i] = workers_heap.at(0).finishing_time;
      long long new_finishingtime = workers_heap.at(0).finishing_time + static_cast<long long>(jobs_[i]);
      change_finishtime(0, workers_heap, new_finishingtime);
    }
  }


 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
