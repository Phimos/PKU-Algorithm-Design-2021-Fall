#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int L, M;
    cin >> L >> M;
    vector<vector<int>> pos(M, vector<int>(2));
    for (int i = 0; i < M; ++i) {
        cin >> pos[i][0] >> pos[i][1];
    }
    sort(pos.begin(), pos.end(),
         [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; });

    int ans = L + 1;
    vector<int> cur(pos[0]);

    for (int i = 1; i < M; ++i) {
        if (cur[1] < pos[i][0]) {
            ans -= cur[1] - cur[0] + 1;
            cur = pos[i];
        } else {
            cur[1] = max(cur[1], pos[i][1]);
        }
    }
    ans -= cur[1] - cur[0] + 1;

    cout << ans << endl;
    return 0;
}