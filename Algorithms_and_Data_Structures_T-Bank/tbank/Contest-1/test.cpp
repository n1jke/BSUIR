#include <iostream>
#include <vector>
using namespace std;
#define ll  long long

ll merge(vector<ll>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<ll> leftVec(n1), rightVec(n2);

    for (int i = 0; i < n1; i++)
        leftVec[i] = vec[left + i];

    for (int j = 0; j < n2; j++)
        rightVec[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    ll count = 0;

    while (i < n1 && j < n2) {
        if (leftVec[i] <= rightVec[j]) {
            vec[k++] = leftVec[i++];
        } else {
            vec[k++] = rightVec[j++];
            count += (n1 - i); // count of other elements
        }
    }

    while (i < n1)
        vec[k++] = leftVec[i++];

    while (j < n2)
        vec[k++] = rightVec[j++];

    return count;
}

ll mergeSort(vector<ll>& vec, int left, int right) {
    ll count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        count += mergeSort(vec, left, mid);
        count += mergeSort(vec, mid + 1, right);
        count += merge(vec, left, mid, right);
    }
    return count;
}

int main() {
    int n;
    cin >> n;
    vector<ll> vec(n);

    for (int i = 0; i < n; i++)
        cin >> vec[i];

    ll inversions = mergeSort(vec, 0, n - 1);

    cout << inversions << "\n";
    for (ll num : vec)
        cout << num << " ";
    cout << "\n";

    return 0;
}
