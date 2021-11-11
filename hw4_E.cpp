#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

#define MAXN 300
#define MAXE 1000
#define INT_MAX 0x7fffffff

struct Edge {
    int to, cap, flow, next;
    Edge(int to, int cap, int flow, int next)
        : to(to), cap(cap), flow(flow), next(next) {}
    Edge() {}
};

Edge edges[MAXE];
int edgecnt;
int head[MAXN];
int step[MAXN];

void add_edge(int a, int b, int cap = 1) {
    edges[edgecnt] = Edge(b, cap, 0, head[a]);
    head[a] = edgecnt++;
    edges[edgecnt] = Edge(a, 0, 0, head[b]);
    head[b] = edgecnt++;
}

int bfs(int s, int t) {
    memset(step, 0, sizeof(step));
    step[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; ~i; i = edges[i].next) {
            int v = edges[i].to;
            if (!step[v] && edges[i].cap > edges[i].flow) {
                step[v] = step[u] + 1;
                q.push(v);
            }
        }
        if (step[t])
            return step[t];
    }
    return step[t];
}

int dfs(int u, int t, int inflow) {
    if (u == t || inflow == 0)
        return inflow;
    int flow = 0, f;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to;
        if (step[v] == step[u] + 1 && edges[i].cap > edges[i].flow &&
            (f = dfs(v, t, min(inflow, edges[i].cap - edges[i].flow))) > 0) {
            edges[i].flow += f;
            edges[i ^ 1].flow -= f;
            flow += f;
            inflow -= f;
        }
        if (inflow == 0)
            break;
    }
    return flow;
}

int maxflow(int s, int t) {
    int flow = 0;
    while (bfs(s, t))
        flow += dfs(s, t, INT_MAX);
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, s, e, c;

    while (cin >> n >> m) {
        fill(head, head + MAXN, -1);
        edgecnt = 0;
        for (int i = 0; i < n; ++i) {
            cin >> s >> e >> c;
            add_edge(s, e, c);
        }
        cout << maxflow(1, m) << endl;
    }

    return 0;
}