#include <cmath>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

struct Edge {
    int to, next;
    double r, c;
    Edge(int to, int next, double r, double c)
        : to(to), next(next), r(r), c(c) {}
    Edge() {}
};

Edge edges[205];
int head[105];
int edge_cnt;

double dis[105];
int vis[105];
int cnt[105];

void add_edge(int u, int v, double r, double c) {
    edges[edge_cnt] = Edge(v, head[u], r, c);
    head[u] = edge_cnt++;
}

int main() {
    int n, m, s;
    double val;
    cin >> n >> m >> s >> val;

    fill(head, head + n + 1, -1);

    double rab, cab, rba, cba;
    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> rab >> cab >> rba >> cba;
        add_edge(a, b, rab, cab);
        add_edge(b, a, rba, cba);
    }

    // SPFA
    dis[s] = val;

    queue<int> q;
    q.push(s);
    vis[s] = 1;

    bool flag = false;
    while (!q.empty() & !flag) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; ~i; i = edges[i].next) {
            int v = edges[i].to;
            if (dis[v] < (dis[u] - edges[i].c) * edges[i].r) {
                dis[v] = (dis[u] - edges[i].c) * edges[i].r;

                cnt[v]++;
                if (dis[s] > val) {
                    flag = true;
                }
                if (vis[v] == 0) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }

    cout << (flag ? "YES" : "NO") << endl;

    return 0;
}