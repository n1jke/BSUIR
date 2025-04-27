#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

struct treeNode {
  int val;
  vector<treeNode*> child;
  treeNode(int x) : val(x) {}
};

/*

int dfsToLongest(treeNode* root){ // find longest way
  if (!root) return 0;
  int maxHeight = 0;
  treeNode* longest = root;
  for (treeNode* children : root->child){
    int temp = maxHeight;
    maxHeight = max(maxHeight, dfsToLongest(children));
    if (temp != maxHeight) longest = children;
  }
  return maxHeight + 1;
} 

pair<int, int> dfsDiameter(treeNode* node) {
  if (node->child.empty()) {
      return {0, 0};
  }
  
  int maxHeight1 = 0; 
  int maxHeight2 = 0; 
  int bestDiameter = 0; 
  
  // Обходим всех детей текущего узла
  for (treeNode* child : node->child) {
    auto [childHeight, childDiameter] = dfsDiameter(child);
    // При переходе к ребёнку учитываем ребро: h = childHeight + 1
    int h = childHeight + 1;
    if (h > maxHeight1) {
      maxHeight2 = maxHeight1;
      maxHeight1 = h;
    } else if (h > maxHeight2) {
      maxHeight2 = h;
    }
    // updt diam
    bestDiameter = max(bestDiameter, childDiameter);
  }
  
  int diameterThroughNode = maxHeight1 + maxHeight2;
  int currentDiameter = max(bestDiameter, diameterThroughNode);
  int currentHeight = maxHeight1;
  
  return {currentHeight, currentDiameter};
}
*/

int treeHeight(treeNode* root) {
  if (!root) return -1;
  int height = -1;
  queue<treeNode*> q;
  q.push(root);
  while (!q.empty()) {
    int levelSize = q.size();
    height++;  // after every level
    for (int i = 0; i < levelSize; ++i) {
      treeNode* node = q.front();
      q.pop();
      for (treeNode* child : node->child) {
        q.push(child);
      }
    }
  }
  return height;
}

pair<int, treeNode*> bfsFarthest(treeNode* start) {
  queue<treeNode*> q;
  q.push(start);
  unordered_map<treeNode*, int> dist; 
  dist[start] = 0;
  treeNode* farthest = start;
  int maxDist = 0;
  while (!q.empty()) {
    treeNode* cur = q.front();
    q.pop();
    int d = dist[cur];
    if (d > maxDist) {
      maxDist = d;
      farthest = cur;
    }
  
    for (treeNode* child : cur->child) {
      if (dist.find(child) == dist.end()) {
        dist[child] = d + 1;
        q.push(child);
      }
    }
  }
  return {maxDist, farthest};
}

int getDiameter(treeNode* root) {
  if (!root) return 0;
  auto first = bfsFarthest(root);
  auto second = bfsFarthest(first.second);
  
  return second.first; 
}

// bfs to every node dist
void bfs(treeNode* root) {
  if (!root) return;
  queue<treeNode*> que;
  que.push(root);
  int distance = 0;
  while (!que.empty()) {
    int levelSize = que.size();
    for (int i = 0; i < levelSize; ++i) {
      treeNode* node = que.front();
      que.pop();
      cout << distance << ' ';
      for (treeNode* child : node->child) { 
        que.push(child);
      }
    }
    ++distance;
  }
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  ll size;
  cin >> size;

  vector<int> childrens(size - 1);
  for (int i = 0; i < size - 1; ++i){
    cin >> childrens[i];
  }

  vector<treeNode*> nodes(size); 
  for (int i = 0; i < size; ++i){
    nodes[i] = new treeNode(i);
  }
  for (int i = 0; i < size - 1; ++i){ 
    int parent = childrens[i];    
    nodes[parent]->child.push_back(nodes[i + 1]); 
  }
  
  int height = treeHeight(nodes[0]);
  int diameter = getDiameter(nodes[0]);
  cout << height << ' ' << diameter << '\n';
  
  bfs(nodes[0]);

  for (int i = 0; i < size; ++i) {
    delete nodes[i];
  }

  return 0;
}
