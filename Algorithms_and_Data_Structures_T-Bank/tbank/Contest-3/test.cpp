#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> children;
vector<int> depth;
int max_diameter = 0;

int dfs(int v, int d) {
  depth[v] = d;
  vector<int> heights;
  for (int c : children[v]) {
    int h = dfs(c, d + 1);
    heights.push_back(h + 1);
  }
  if (heights.size() >= 2) {
    sort(heights.begin(), heights.end(), greater<int>());
    int candidate = heights[0] + heights[1];
    max_diameter = max(max_diameter, candidate);
  } else if (heights.size() == 1) {
    int candidate = heights[0];
    max_diameter = max(max_diameter, candidate);
  }
  if (heights.empty()) {
    return 0;
  } else {
    return *max_element(heights.begin(), heights.end());
  }
}

int main() {
  int n;
  cin >> n;
  vector<int> p(n - 1);
  for (int i = 0; i < n - 1; ++i) {
    cin >> p[i];
  }
  children.resize(n);
  depth.resize(n);
  for (int i = 1; i < n; ++i) {
    children[p[i - 1]].push_back(i);
  }
  int height = dfs(0, 0);
  cout << height << " " << max_diameter << endl;
  for (int i = 0; i < n; ++i) {
    cout << depth[i] << (i < n - 1 ? " " : "\n");
  }
  return 0;
}