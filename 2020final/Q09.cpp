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
#include <vector>
#define N (5000 + 2)
#define M (65000 * 3)

typedef long long LL;

using namespace std;

struct edge {
    LL v, cap, next;
};
edge e[M];

LL head[N], level[N], cur[N];
LL num_of_edges;

/*
 * When there are multiple test sets, you need to re-initialize before each
 */
void dinic_init(void) {
    num_of_edges = 0;
    memset(head, -1, sizeof(head));
    return;
}

LL add_edge(LL u, LL v, LL c1, LL c2) {
    LL& i = num_of_edges;

    assert(c1 >= 0 && c2 >= 0 &&
           c1 + c2 >= 0);  // check for possibility of overflow
    e[i].v = v;
    e[i].cap = c1;
    e[i].next = head[u];
    head[u] = i++;

    e[i].v = u;
    e[i].cap = c2;
    e[i].next = head[v];
    head[v] = i++;
    return i;
}

// void print_graph(LL n) {
//     for (LL u = 0; u < n; u++) {
//         printf("%d: ", u);
//         for (LL i = head[u]; i >= 0; i = e[i].next) {
//             printf("%d(%d)", e[i].v, e[i].cap);
//         }
//         printf("\n");
//     }
//     return;
// }

/*
 * Find all augmentation paths in the current level graph
 * This is the recursive version
 */
LL dfs(LL u, LL t, LL bn) {
    if (u == t)
        return bn;
    LL left = bn;
    for (LL& i = cur[u]; i >= 0; i = e[i].next) {
        LL v = e[i].v;
        LL c = e[i].cap;
        if (c > 0 && level[u] + 1 == level[v]) {
            LL flow = dfs(v, t, min(left, c));
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

bool bfs(LL s, LL t) {
    memset(level, 0, sizeof(level));
    level[s] = 1;
    queue<LL> q;
    q.push(s);
    while (!q.empty()) {
        LL u = q.front();
        q.pop();
        if (u == t)
            return true;
        for (LL i = head[u]; i >= 0; i = e[i].next) {
            LL v = e[i].v;
            if (!level[v] && e[i].cap > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return false;
}

LL dinic(LL s, LL t) {
    LL max_flow = 0;

    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        max_flow += dfs(s, t, LONG_MAX);
    }
    return max_flow;
}

LL upstream(LL s, LL n) {
    LL cnt = 0;
    vector<bool> visited(n);
    queue<LL> q;
    visited[s] = true;
    q.push(s);
    while (!q.empty()) {
        LL u = q.front();
        q.pop();
        for (LL i = head[u]; i >= 0; i = e[i].next) {
            LL v = e[i].v;
            if (e[i].cap > 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
                cnt++;
            }
        }
    }
    return cnt;  // excluding s
}

LL get_closure(LL s, vector<LL>& vis) {
    LL cnt = 1;
    vis[s] = true;
    for (LL i = head[s]; i >= 0; i = e[i].next) {
        if (e[i].cap == 0 || vis[e[i].v])
            continue;
        cnt += get_closure(e[i].v, vis);
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    LL n, m, u, v;
    cin >> n >> m;

    dinic_init();
    LL s = 0, t = n + 1;
    LL sum_positive = 0;
    for (LL i = 1; i <= n; ++i) {
        cin >> u;
        if (u > 0) {
            add_edge(s, i, u, 0);
            sum_positive += u;
        } else if (u < 0) {
            add_edge(i, t, -u, 0);
        }
    }
    for (LL j = 0; j < m; ++j) {
        cin >> u >> v;
        add_edge(u, v, LONG_MAX, 0);
    }
    LL ans = dinic(s, t);

    vector<LL> vis(n + 2, 0);
    LL size_of_closure = get_closure(s, vis) - 1;
    cout << size_of_closure << ' ' << sum_positive - ans << endl;
    return 0;
}