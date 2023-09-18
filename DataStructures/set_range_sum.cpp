#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;

/*
Problem Introduction
In this problem, your goal is to implement a data structure to store a set of integers and quickly compute range sums.
Problem Description
Task. Implement a data structure that stores a set 𝑆 of integers with the following allowed operations:
∙ add(𝑖) — add integer 𝑖 into the set 𝑆 (if it was there already, the set doesn’t change).
∙ del(𝑖) — remove integer 𝑖 from the set 𝑆 (if there was no such element, nothing happens). ∙ find(𝑖) — check whether 𝑖 is in the set 𝑆 or not.
∙ sum(𝑙,𝑟)—outputthesumofallelements𝑣in𝑆suchthat𝑙≤𝑣≤𝑟.
Input Format. Initially the set 𝑆 is empty. The first line contains 𝑛 — the number of operations. 
The next 𝑛 lines contain operations. Each operation is one of the following:
∙ “+ i" — which means add some integer (not 𝑖, see below) to 𝑆,
∙ “- i" — which means del some integer (not 𝑖, see below)from 𝑆,
∙ “? i" — which means find some integer (not 𝑖, see below)in 𝑆,
∙ “s l r" — which means compute the sum of all elements of 𝑆 within some range of values (not from 𝑙 to 𝑟, see below).
However, to make sure that your solution can work in an online fashion, each request will 
actually depend on the result of the last sum request. Denote 𝑀 = 1 000 000 001. 
At any moment, let 𝑥 be the result of the last sum operation, or just 0 if there were no sum operations before. Then
∙ “+ i" means add((𝑖 + 𝑥) mod 𝑀),
∙ “- i" means del((𝑖 + 𝑥) mod 𝑀),
∙ “? i" means find((𝑖 + 𝑥) mod 𝑀),
∙ “slr"meanssum((𝑙+𝑥)mod𝑀,(𝑟+𝑥)mod𝑀).
*/

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
  int key;
  // Sum of all the keys in the subtree - remember to update
  // it after each operation that changes the tree.
  long long sum;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent) 
  : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
  if (v == NULL) return; // there is nothing to update if our vertex is null
  v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
  if (v->left != NULL) { // if we updated the vertex's left child, than make it parent
    v->left->parent = v;
  }
  if (v->right != NULL) { // the same with the right child
    v->right->parent = v;
  }
}

void small_rotation(Vertex* v) { // ZIG
  Vertex* parent = v->parent; // find parent
  if (parent == NULL) {
    return; // if parent equals to zero, return because there is nothing to rotate(we have to splay our vertex up)
  }
  Vertex* grandparent = v->parent->parent; // find grand-parent
  if (parent->left == v) { // if the vertex is on the left of its parent
    Vertex* m = v->right; // find vertex's right vertex
    v->right = parent; // splay our vertex up and make its parent the right child(because our vertex is less than its parent)
    parent->left = m; // make parent's left vertex vertex's right vertex(because it is bigger than our vertex but smaller than its parent)
  } else { // if the vertex is on the right of its parent
    Vertex* m = v->left; // find vertex's left vertex
    v->left = parent; // splay our vertex up and make its parent its right child (because it is bigger than its parent)
    parent->right = m; // make parent's right child vertex's left child(because it is bigger than parent but less then vertex)
  }
  update(parent); 
  update(v);
  v->parent = grandparent; // make parent of our vertex its grandparent
  if (grandparent != NULL) { // update grandparent right or left child 
    if (grandparent->left == parent) {
      grandparent->left = v;
    } else {
      grandparent->right = v;
    }
  }
}

void big_rotation(Vertex* v) {
  // IF EVERYTHING IS ON ONE SIDE
  if (v->parent->left == v && v->parent->parent->left == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else { // IF THE PARENT AND GRAND PARENT ARE ON DIFFERENT SIDES
    // Zig-zag
    small_rotation(v);
    small_rotation(v);
  }  
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
  if (v == NULL) return;
  while (v->parent != NULL) {
    if (v->parent->parent == NULL) {
      small_rotation(v);
      break;
    }
    big_rotation(v);
  }
  root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree, 
// returns NULL.
Vertex* find(Vertex*& root, int key) {
  Vertex* v = root;
  Vertex* last = root;
  Vertex* next = NULL;
  while (v != NULL) { // WHILE WE STILL HAVE KEYS TO LOOK FOR
    if (v->key >= key && (next == NULL || v->key < next->key)) {//????????
      next = v;
    } // next helps us to find element that is next biggest after the one we are looking for
    // so, we check whether key of our current vertex is >= to our key
    // and also, check whether our current vertex is on the left or right of the next key
    // v->key<next->key is for us to check whether the element that is bigger than the key, is next biggest
    last = v;
    if (v->key == key) {
      break;      
    }
    if (v->key < key) {
      v = v->right;
    } else {
      v = v->left;
    }
  }
  splay(root, last);
  return next;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
  right = find(root, key);
  splay(root, right);
  if (right == NULL) {
    left = root;
    return;
  }
  left = right->left;
  right->left = NULL;
  if (left != NULL) {
    left->parent = NULL;
  }
  update(left);
  update(right);
} // HAVE TO CHECK ON PRACTICE

Vertex* merge(Vertex* left, Vertex* right) {
  if (left == NULL) return right;
  if (right == NULL) return left;
  Vertex* min_right = right;
  while (min_right->left != NULL) {
    min_right = min_right->left;
  }
  splay(right, min_right);
  right->left = left;
  update(right);
  return right;
}

// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert(int x) {
  Vertex* left = NULL;
  Vertex* right = NULL;
  Vertex* new_vertex = NULL;  
  split(root, x, left, right);
  if (right == NULL || right->key != x) {
    new_vertex = new Vertex(x, x, NULL, NULL, NULL);
  }
  root = merge(merge(left, new_vertex), right);
}

void erase(int x) {                   
    Vertex *found_element = find(root, x);
    if (found_element==NULL || found_element->key!=x)
      return;
    splay(root, found_element);
    Vertex *left = found_element->left;
    Vertex *right = found_element->right;
    if (right!=NULL)
      right->parent = NULL;
    if (left!=NULL)
      left->parent = NULL;
    root = merge(left,right);
}

bool find(int x) {  
    Vertex *found_element = find(root, x);
    if (found_element==nullptr || found_element->key!=x)
      return false;
    return true;
}

long long sum(int from, int to) {
  Vertex* left = NULL;
  Vertex* middle = NULL;
  Vertex* right = NULL;
  split(root, from, left, middle);
  split(middle, to + 1, middle, right);
  long long ans = (middle!=nullptr)?middle->sum:0ll;
  // Complete the implementation of sum
  root = merge(merge(left,middle),right);
  return ans;  
}


const int MODULO = 1000000001;

int main(){
  int n;
  scanf("%d", &n);
  int last_sum_result = 0;
  // char array[] = {'+','-','?','s'};
  // while(n<50) {
  //   n++;
  //   char type = array[rand()%4];
  //   cout<<"Type - "<<type<<endl;
  //   switch (type) {
  //     case '+' : {
  //       int x;
  //       x = rand()%30;
  //       cout<<"Number - "<<x<<endl;
  //       insert(x);
  //     } break;
  //     case '-' : {
  //       int x;
  //       x = rand()%30;
  //       cout<<"Number - "<<x<<endl;
  //       erase(x);
  //     } break;            
  //     case '?' : {
  //       int x;
  //       x = rand()%30;
  //       cout<<"Number - "<<x<<endl;
  //       printf(find(x) ? "Found\n" : "Not found\n");
  //     } break;
  //     case 's' : {
  //       int l, r;
  //       l = rand()%30;
  //       r =rand()%30+l;
  //       long long res = sum(l, r);
  //       cout<<"Number - "<<l<<" "<<r<<endl;
  //       printf("%lld\n", res);
  //       last_sum_result = int(res);
  //     }
  //   }
  // }
  for (int i = 0; i < n; i++) {
    char buffer[10];
    scanf("%s", buffer);
    char type = buffer[0];
    switch (type) {
      case '+' : {
        int x;
        scanf("%d", &x);
        insert((x + last_sum_result) % MODULO);
      } break;
      case '-' : {
        int x;
        scanf("%d", &x);
        erase((x + last_sum_result) % MODULO);
      } break;            
      case '?' : {
        int x;
        scanf("%d", &x);
        printf(find((x + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
      } break;
      case 's' : {
        int l, r;
        scanf("%d %d", &l, &r);
        long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
        printf("%lld\n", res);
        last_sum_result = int(res % MODULO);
      }
    }
  }
  return 0;
}
