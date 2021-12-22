#include <climits>
#include <cstring>
#include <queue>

#include <iostream>
using namespace std;
#define maxn (1000 + 10)
#define maxm (maxn * maxn + 4 * maxn)

struct Edge {
    int to, w, next;
    Edge() {}
    Edge(int to, int w, int next) : to(to), w(w), next(next) {}
} edges[maxm];
int head[maxn], dis[maxn], vis[maxn];
int edgecnt;

void graph_init() {
    fill(head, head + maxn, -1);
    edgecnt = 0;
}
void add_edge(int u, int v, int w) {
    edges[edgecnt] = Edge(v, w, head[u]);
    head[u] = edgecnt++;
    edges[edgecnt] = Edge(u, w, head[v]);
    head[v] = edgecnt++;
}

int dijkstra(int s, int t) {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    dis[s] = INT_MAX;

    priority_queue<pair<int, int>> pq;
    pq.emplace(INT_MAX, s);

    while (!pq.empty()) {
        pair<int, int> tmp = pq.top();
        pq.pop();
        int& d = tmp.first;
        int& u = tmp.second;
        if (d < dis[u])
            continue;
        for (int i = head[u]; ~i; i = edges[i].next) {
            int& v = edges[i].to;
            if (min(dis[u], edges[i].w) > dis[v]) {
                dis[v] = min(dis[u], edges[i].w);
                pq.emplace(dis[v], v);
            }
        }
    }
    return dis[t];
}

int main() {
    int scenarios, n, m, u, v, w;
    cin >> scenarios;
    for (int s = 1; s <= scenarios; ++s) {
        graph_init();
        cin >> n >> m;
        for (int i = 0; i < m; ++i) {
            cin >> u >> v >> w;
            add_edge(u, v, w);
        }
        cout << "Scenario #" << s << ":" << endl;
        cout << dijkstra(1, n) << endl;
        cout << endl;
    }
}
