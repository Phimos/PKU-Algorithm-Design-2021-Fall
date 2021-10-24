#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int in[101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int v, a;
    cin >> v >> a;
    vector<vector<int>> nxt = vector<vector<int>>(v + 1);

    int x, y;
    for (int i = 0; i < a; ++i) {
        cin >> x >> y;
        nxt[x].push_back(y);
        ++in[y];
    }
    vector<int> ans;

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= v; ++i) {
        if (in[i] == 0) {
            pq.push(i);
        }
    }

    while (!pq.empty()) {
        int tmp = pq.top();
        pq.pop();
        cout << 'v' << tmp << ' ';
        for (auto& u : nxt[tmp]) {
            --in[u];
            if (in[u] == 0) {
                pq.push(u);
            }
        }
    }
    return 0;
}