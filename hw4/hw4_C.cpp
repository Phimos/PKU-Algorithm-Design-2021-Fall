#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge {
    int to, next, cost;
    Edge(int to, int next, int cost) : to(to), next(next), cost(cost) {}
    Edge() {}
} edges[2000];

int head[501];
int edgecnt = 0;
vector<int> cows[501];

int dis[501];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int f, p, c, m;  // field, path, cow, seconds
    cin >> f >> p >> c >> m;
    int f1, f2, t;
    fill(head, head + 501, -1);
    for (int i = 0; i < p; ++i) {
        cin >> f1 >> f2 >> t;
        edges[edgecnt] = Edge(f2, head[f1], t);
        head[f1] = edgecnt++;
        edges[edgecnt] = Edge(f1, head[f2], t);
        head[f2] = edgecnt++;
    }
    for (int i = 1; i <= c; ++i) {
        cin >> f1;
        cows[f1].push_back(i);
    }

    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;

    priority_queue<pair<int, int>> pq;
    pq.emplace(0, 1);

    while (!pq.empty()) {
        auto tmp = pq.top();
        pq.pop();
        int d = -tmp.first;
        int u = tmp.second;
        if (dis[u] < d)
            continue;
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            int t = edges[i].cost;
            if (dis[v] > dis[u] + t) {
                dis[v] = dis[u] + t;
                pq.emplace(-dis[v], v);
            }
        }
    }

    vector<int> ans;

    for (int i = 1; i <= f; ++i) {
        if (dis[i] <= m) {
            for (auto c : cows[i]) {
                ans.push_back(c);
            }
        }
    }

    sort(ans.begin(), ans.end());

    cout << ans.size() << endl;
    for (auto c : ans) {
        cout << c << endl;
    }

    return 0;
}
