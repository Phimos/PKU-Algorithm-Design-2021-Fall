/*
 * Dinic algo for max flow
 *
 * This implementation assumes that #nodes, #edges, and capacity on each edge <=
 * INT_MAX, which means INT_MAX is the best approximation of INF on edge
 * capacity. The total amount of max flow computed can be up to LLONG_MAX (not
 * defined in this file), but each 'dfs' call in 'dinic' can return <= INT_MAX
 * flow value.
 */
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#define N (300 + 2)
#define M (N * N + 4 * N)

typedef long long LL;

using namespace std;

struct edge {
    int v, cap, next, ori_cap;
};
edge e[M];

int head[N], level[N], cur[N];
int num_of_edges;

/*
 * When there are multiple test sets, you need to re-initialize before each
 */
void dinic_init(void) {
    num_of_edges = 0;
    memset(head, -1, sizeof(head));
    return;
}

int add_edge(int u, int v, int c1, int c2) {
    int& i = num_of_edges;

    assert(c1 >= 0 && c2 >= 0 &&
           c1 + c2 >= 0);  // check for possibility of overflow
    e[i].v = v;
    e[i].cap = c1;
    e[i].ori_cap = c1;
    e[i].next = head[u];
    head[u] = i++;

    e[i].v = u;
    e[i].cap = c2;
    e[i].ori_cap = c2;
    e[i].next = head[v];
    head[v] = i++;
    return i;
}

void clean_grpah() {
    for (int i = 0; i < num_of_edges; ++i) {
        e[i].cap = e[i].ori_cap;
    }
}

void print_graph(int n) {
    for (int u = 0; u < n; u++) {
        printf("%d: ", u);
        for (int i = head[u]; i >= 0; i = e[i].next) {
            printf("%d(%d)", e[i].v, e[i].cap);
        }
        printf("\n");
    }
    return;
}

/*
 * Find all augmentation paths in the current level graph
 * This is the recursive version
 */
int dfs(int u, int t, int bn) {
    if (u == t)
        return bn;
    int left = bn;
    for (int& i = cur[u]; i >= 0; i = e[i].next) {
        int v = e[i].v;
        int c = e[i].cap;
        if (c > 0 && level[u] + 1 == level[v]) {
            int flow = dfs(v, t, min(left, c));
            if (flow > 0) {
                e[i].cap -= flow;
                e[i ^ 1].cap += flow;
                cur[u] = i;
                left -= flow;
                if (!left)
                    break;
            }
        }
    }
    if (left > 0)
        level[u] = 0;
    return bn - left;
}

bool bfs(int s, int t) {
    memset(level, 0, sizeof(level));
    level[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == t)
            return true;
        for (int i = head[u]; i >= 0; i = e[i].next) {
            int v = e[i].v;
            if (!level[v] && e[i].cap > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return false;
}

LL dinic(int s, int t) {
    LL max_flow = 0;

    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        max_flow += dfs(s, t, INT_MAX);
    }
    return max_flow;
}

int upstream(int s, int n) {
    int cnt = 0;
    vector<bool> visited(n);
    queue<int> q;
    visited[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i >= 0; i = e[i].next) {
            int v = e[i].v;
            if (e[i].cap > 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
                cnt++;
            }
        }
    }
    return cnt;  // excluding s
}

int main() {
    char line[1024];
    int beats[16];
    int m;
    cin >> m;
    cin.getline(line, 1024);
    for (int mm = 0; mm < m; ++mm) {
        cin.getline(line, 1024);
        stringstream ss;
        int tmp;
        ss << line;
        int n = 0;
        while (ss >> tmp) {
            n += 1;
            beats[n] = tmp;
        }

        int ans = 1;

        for (ans = 1; ans <= n; ++ans) {
            dinic_init();
            int s = 0, t = n * n * 2 + n + 1;
            for (int i = 1; i <= n; ++i) {
                for (int j = i + 1; j <= n; ++j) {
                    if (i + ans <= n || beats[i] >= beats[j]) {
                        add_edge(i, i * n + j, 1, 0);  // i win j
                        add_edge(j, j * n + i, 1, 0);
                        add_edge(i * n + j, n * n + min(i, j) * n + max(i, j),
                                 1, 0);
                        add_edge(j * n + i, n * n + min(i, j) * n + max(i, j),
                                 1, 0);
                    }
                }
            }

            int sum_flow = 0;
            bool flag = false;
            for (int i = n; i > 0; --i) {
                int need_to_beat = 0;
                for (int j = i + 1; j <= n; ++j)
                    if (beats[j] > beats[i])
                        ++need_to_beat;
                if (i + ans <= n)
                    need_to_beat = 0;
                sum_flow += beats[i] - need_to_beat;
                if (beats[i] < need_to_beat) {
                    flag = true;
                    break;
                }
                // cout << ". " << i << ' ' << need_to_beat << endl;
                add_edge(s, i, beats[i] - need_to_beat, 0);
            }
            if (flag)
                break;

            for (int i = 1; i <= n; ++i)
                for (int j = i + 1; j <= n; ++j)
                    add_edge(n * n + i * n + j, t, 1, 0);
            if (sum_flow != dinic(s, t))
                break;
        }
        cout << ans - 1 << endl;
    }
    return 0;
}
