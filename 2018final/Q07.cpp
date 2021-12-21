#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

#define maxn 1000010
#define maxm 1000010

typedef long long LL;

struct Edge {
    int from, to, price, nxt;
    Edge() {}
    Edge(int from, int to, int price, int nxt)
        : from(from), to(to), price(price), nxt(nxt) {}
} edges[maxm];
int head[maxn];
int edgecnt;
int dis[maxn];

void init_graph() {
    edgecnt = 0;
    fill(head, head + maxn, -1);
}

void add_edge(int u, int v, int price) {
    edges[edgecnt] = Edge(u, v, price, head[u]);
    head[u] = edgecnt++;
}

void reverse_graph() {
    int m = edgecnt;
    init_graph();
    for (int i = 0; i < m; ++i) {
        add_edge(edges[i].to, edges[i].from, edges[i].price);
    }
}

LL dijkstra(int n) {
    memset(dis, 0x3f, sizeof(dis));

    priority_queue<pair<int, int>> pq;
    dis[1] = 0;
    pq.emplace(0, 1);
    while (!pq.empty()) {
        pair<int, int> tmp = pq.top();
        pq.pop();
        int u = tmp.second;
        int d = -tmp.first;

        if (d > dis[u])
            continue;
        for (int i = head[u]; ~i; i = edges[i].nxt) {
            int& v = edges[i].to;
            int& p = edges[i].price;
            if (dis[u] + p < dis[v]) {
                dis[v] = dis[u] + p;
                pq.emplace(-dis[v], v);
            }
        }
    }
    LL ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += (LL)dis[i];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t, n, m, u, v, p;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        init_graph();
        for (int i = 0; i < m; ++i) {
            cin >> u >> v >> p;
            add_edge(u, v, p);
        }

        LL ans = dijkstra(n);
        reverse_graph();
        ans += dijkstra(n);
        cout << ans << endl;
    }
}