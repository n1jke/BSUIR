#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

struct AVL {
  ll val;
  AVL* right;
  AVL* left;
  AVL(int x, AVL* r = nullptr, AVL* l = nullptr) : val(x), right(r), left(l){};
};

ll isAVL(AVL* root, ll min_val, ll max_val){
  if (!root) return 0;

  if (root->val <= min_val || root->val >= max_val) return -1;// check bst

  ll leftheight = isAVL(root->left, min_val, root->val);// check for left subtree
  if (leftheight == -1) return -1;

  ll rightheight = isAVL(root->right, root->val, max_val);//  check for right subtree
  if (rightheight == -1) return -1;

  if (abs(leftheight - rightheight) > 1) return -1;// check bst balance

  return max(leftheight, rightheight) + 1;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  ll size, root, left, right;
  cin >> size >> root;

  vector<AVL*> nodes(size);
  for( ll i = 0;i < size; ++i){
    nodes[i] = new AVL(i);
  }
  for (ll i = 0; i < size; ++i){
    cin >> left >> right;
      if (left != -1) nodes[i]->left = nodes[left];
      if (right != -1) nodes[i]->right = nodes[right];
  }

  if (isAVL(nodes[root], -1, size) != -1) {
    cout << 1 << '\n';
  }  else {
    cout << 0 << '\n';
  }

  for (auto node : nodes) delete node;

  return 0;
}