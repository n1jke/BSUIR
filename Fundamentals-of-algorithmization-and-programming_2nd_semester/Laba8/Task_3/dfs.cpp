#include <bits/stdc++.h>
using namespace std;

class node {
  public:
  int val;
  node* left;
  node* right;
};

void bfs(node* root) {
  queue<node*> q;
  q.push(root);
  while (!q.empty()) {
    node* cur = q.front();
    q.pop();
    cout << cur->val << " ";
    if (cur->left) q.push(cur->left);
    if (cur->right) q.push(cur->right);
  }
}

/*
      5

      
*/