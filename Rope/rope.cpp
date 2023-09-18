#include <cstdio>
#include <string>
#include <iostream>
#include <stack>

struct Node{
	char key;
	Node *left;
	Node *right;
	Node *parent;
	int size;
	Node(int key, Node* left, Node* right, Node* parent, int size)  : key(key), left(left), right(right), parent(parent), size(size) {}
};
Node *create_tree(const std::string &, int left, int right);
void splay(Node *&root, Node* v);
Node *find(Node *root, int i);
Node *merge(Node *, Node *);
void update_size(Node *, int );
void split(Node *, Node *&, Node *&);
void update(Node *);

class Rope {
	std::string s;
	Node *root;
public:
	Rope(const std::string &s) : s(s) { 
		root = create_tree(s, 0, s.size()-1);
	}

	void process( int i, int j, int k ) {
                // Replace this code with a faster implementation
                // std::string t = s.substr(0, i) + s.substr(j + 1);
                // s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
		Node *subtree_start = find(root, i+1);
		splay(root, subtree_start); // splay first char of the substr
		splay(root, find(root, j+1)); // splay last char of the substr

		Node *right_side = root->right; // on the right from the substr
		Node *left_side = subtree_start->left; // on the left from the substr

		Node *subtree_root = root;
		subtree_root->right = nullptr;
		subtree_start->left = nullptr;

		if (right_side!=nullptr){
			right_side->parent = nullptr;
			subtree_root->size-=right_side->size;
		}
		if (left_side!=nullptr){
			left_side->parent = nullptr;
			update_size(subtree_root, left_side->size);
		}
		root = merge(left_side, right_side);
		// we have root(string without substring) and the subtree root(substring)
		add_substr(subtree_root, k);
	}

	void add_substr(Node* subtree_root, int k){
		if (k==0){
			root = merge(subtree_root, root);
			return;
		}
		Node *add_after = find(root, k);
		splay(root, add_after);

		Node *left_side = nullptr;
		Node *right_side = nullptr;
		split(root, right_side, left_side);
		root = merge(merge(left_side, subtree_root), right_side);
	}

	std::string result() {
		std::string res;
		std::stack<Node *> letters;
		Node *curr = root;
		letters.push(root);
		while (!letters.empty()){
			while (curr->left!=nullptr){
				curr = curr->left;
				letters.push(curr);
			}
			Node *last_el = letters.top();
			res+=last_el->key;
			letters.pop();
			if (last_el->right!=nullptr){
				letters.push(last_el->right);
				curr = last_el->right;
			}
		}
		return res;
	}
};

void update_size(Node* node_to_update, int size_to_substract){
	if (node_to_update==nullptr)
		return;
	while (node_to_update!=nullptr){
		node_to_update->size -= size_to_substract;
		node_to_update = node_to_update->left;
	}
	
}

void update(Node *v){
	if (v==nullptr) return;
	if (v->left!=nullptr)
		v->left->parent = v;
	if (v->right!=nullptr)
		v->right->parent = v;
}

void small_rotation(Node *v){
	Node *parent = v->parent;
	if (parent == nullptr)
		return;
	Node *grandparent = parent->parent;
	if (parent->left==v){
		Node *right = v->right;
		parent->left = right;
		v->right = parent;
		if (right!=nullptr)
			parent->size += right->size;
		parent->size = parent->size - v->size;
		if (right!=nullptr)
			v->size = v->size - right->size;
		v->size = v->size + parent->size;
	}
	else if (parent->right==v){
		Node *left = v->left;
		parent->right = left;
		v->left = parent;
		if (left!=nullptr)
			parent->size += left->size;
		parent->size = parent->size - v->size;
		if (left!=nullptr)
			v->size = v->size - left->size;
		v->size = v->size + parent->size;
	}
	update(v);
	update(parent);
	v->parent = grandparent;
	if (grandparent!=nullptr){
		if (grandparent->left == parent)
			grandparent->left = v;
		else	
			grandparent->right = v;
	}
}

void big_rotation(Node *v){
	if (v->parent->left == v && v->parent->parent->left == v->parent){
		small_rotation(v->parent);
		small_rotation(v);
	}
	else if (v->parent->right == v && v->parent->parent->right == v->parent){
		small_rotation(v->parent);
		small_rotation(v);
	}
	else{
		small_rotation(v);
		small_rotation(v);
	}
}

void splay(Node*& root, Node* v){
	if (v==nullptr) return;
	while(v->parent!=nullptr){
		if (v->parent->parent==nullptr){
			small_rotation(v);
			break;
		}
		big_rotation(v);
	}
	root = v;
}

Node *find(Node *r, int i){//finding i-th smallest element
	int s = 0;
	if (r==nullptr)
		return nullptr;
	while (true){
		s = 0;
		if (r->left!=nullptr)
			s = r->left->size;
		if (i==s+1)
			return r;
		else if (i<s+1)
			r = r->left;
		else{
			r = r->right;
			i = i-s-1;
		}
	}
}

Node *merge(Node *left, Node *right){
	if (left==nullptr)
		return right;
	if (right==nullptr)
		return left;
	Node *min_right = right;
	while (min_right->left!=nullptr)
		min_right = min_right->left;
	splay(right, min_right);
	right->left = left;
	right->size += left->size;
	update(right);
	return right;
}

void split(Node *root, Node *&right, Node *&left){
	if (root == nullptr)
		return;
	right = root->right;
	left = root;
	left->right = nullptr;
	if (right!=nullptr){
		right->parent = nullptr;
		left->size -= right->size;
	}
}

Node *create_tree(const std::string &s, int left, int right){
	Node *root = new Node(s.at(0), nullptr, nullptr, nullptr, s.size());
	Node *curr = root;
	for (int i = 1;i<s.size();i++){
		curr->right = new Node(s.at(i), nullptr, nullptr, nullptr, s.size()-i);
		update(curr);
		curr = curr->right;
		splay(root, curr);
	}
	return root;

}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s);
	int actions;
	std::cin >> actions;
        for (int action_index = 0; action_index < actions; ++action_index) {
                int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	std::cout << rope.result() << std::endl;
}
