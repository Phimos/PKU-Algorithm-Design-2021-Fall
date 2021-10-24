#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> intervals(n, vector<int>(2));
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i][0] >> intervals[i][1];
    }
    sort(intervals.begin(), intervals.end(),
         [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; });

    vector<int> cur(intervals[0]);

    for (int i = 1; i < n; ++i) {
        if (cur[1] < intervals[i][0]) {
            cout << "no" << endl;
            return 0;
        } else {
            cur[1] = max(cur[1], intervals[i][1]);
        }
    }
    cout << cur[0] << ' ' << cur[1] << endl;
    return 0;
}