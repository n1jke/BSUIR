#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

void heapDown(vector<ll>& heap, ll i){
  ll size = heap.size();
  
  while (true){
    ll left = 2 * i + 1;
    ll right = 2 * i + 2;
    ll large = i;

    if (left < size && heap[left] > heap[large]){
      large = left;
    }

    if (right < size && heap[right] > heap[large]){
      large = right;
    }

    if (large != i){
      swap(heap[i] , heap[large]);
      i = large;
    } else break;
  }
}

struct myHeap{//2i + 1, 2i + 2, (i - 1) / 2
  vector<ll> heap;

  void Insert(ll num){
    heap.push_back(num);
    ll curr = heap.size() - 1;
    while (curr != 0) {
      ll parent = (curr - 1) / 2;
      if (heap[curr] > heap[parent]){
        swap(heap[curr], heap[parent]);
        curr = parent;
      } else break;
    }
  }

  void Extract(){
    cout << heap[0] << '\n';
    swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    heapDown(heap, 0);
  }

};

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  myHeap heap;
  ll count, oper, num;
  cin >> count;


  while (count){
    cin >> oper;
    if (oper == 0){
      cin >> num;
      heap.Insert(num);
    } else {
      heap.Extract();
    }

    --count;
  }


  return 0;
}