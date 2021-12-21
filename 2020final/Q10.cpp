#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define maxn 10010
#define maxm 20010

struct Edge {
    int to, length, nxt;
    Edge() {}
    Edge(int to, int length, int nxt) : to(to), length(length), nxt(nxt) {}
} edges[maxm];
int edgecnt;
int head[maxn];
int n, k;

void addedge(int u, int v, int l) {
    edges[edgecnt] = Edge(v, l, head[u]);
    head[u] = edgecnt++;
    edges[edgecnt] = Edge(u, l, head[v]);
    head[v] = edgecnt++;
}

int get_centroid(int root,
                 int father,
                 int num_nodes,
                 int* centroids,
                 vector<int>& vis) {
    int max_size = 0;
    int sum_size = 1;
    for (int i = head[root]; ~i; i = edges[i].nxt) {
        if (edges[i].to == father || vis[edges[i].to])
            continue;
        int child_size =
            get_centroid(edges[i].to, root, num_nodes, centroids, vis);
        max_size = max(max_size, child_size);
        sum_size += child_size;
    }
    max_size = max(max_size, num_nodes - sum_size);
    if (max_size <= (num_nodes >> 1)) {
        centroids[centroids[0] != -1] = root;
    }
    return sum_size;
}

int get_size(int root, int father, vector<int>& vis) {
    int sum_size = 1;
    for (int i = head[root]; ~i; i = edges[i].nxt) {
        if (edges[i].to == father || vis[edges[i].to])
            continue;
        sum_size += get_size(edges[i].to, root, vis);
    }
    return sum_size;
}

int count_pairs(vector<int>& dis, int k) {
    sort(dis.begin(), dis.end());
    int l = 0, r = dis.size() - 1;
    int ans = 0;
    for (; l < dis.size(); ++l) {
        while (r >= 0 && dis[l] + dis[r] > k)
            --r;
        ans += r + 1 - (r >= l);
    }
    return ans >> 1;
}

void get_distance(int root,
                  int father,
                  int bias,
                  vector<int>& vis,
                  vector<int>& dis) {
    dis.push_back(bias);
    for (int i = head[root]; ~i; i = edges[i].nxt) {
        if (edges[i].to == father || vis[edges[i].to])
            continue;
        get_distance(edges[i].to, root, bias + edges[i].length, vis, dis);
    }
}

void valid_pairs(int root, int father, int k, int& ans, vector<int>& vis) {
    vis[root] = 1;

    for (int i = head[root]; ~i; i = edges[i].nxt) {
        if (edges[i].to == father || vis[edges[i].to])
            continue;
        int centroids[2] = {-1, -1};
        get_centroid(edges[i].to, root, get_size(edges[i].to, root, vis),
                     centroids, vis);
        valid_pairs(centroids[0], -1, k, ans, vis);

        vector<int> distance;
        get_distance(edges[i].to, root, edges[i].length, vis, distance);
        ans -= count_pairs(distance, k);
    }
    vector<int> distance;
    get_distance(root, -1, 0, vis, distance);
    ans += count_pairs(distance, k);

    vis[root] = 0;  // reset
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n >> k, n && k) {
        fill(head, head + n + 1, -1);
        edgecnt = 0;

        int u, v, l;
        for (int i = 1; i < n; ++i) {
            cin >> u >> v >> l;
            addedge(u, v, l);
        }

        vector<int> vis(n + 1, 0);
        int centroids[2] = {-1, -1};
        get_centroid(1, -1, n, centroids, vis);

        int ans = 0;

        valid_pairs(centroids[0], -1, k, ans, vis);
        cout << ans << endl;
    }
}