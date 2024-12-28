#include <bits/stdc++.h>
using namespace std;

vector<int>LIS;

int findLongestIncreasingSubsequence(int arr[], int n) {
        LIS.resize(n + 1, 1);

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j] && LIS[i] < LIS[j] + 1) {
                LIS[i] = LIS[j] + 1;
            }
        }
    }

    sort(LIS.begin(),LIS.end(),greater<>());
    return LIS[0];
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << findLongestIncreasingSubsequence(arr, n) << endl;
    return 0;
}

