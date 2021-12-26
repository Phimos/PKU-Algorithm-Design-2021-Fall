#include <cstring>
#include <iostream>
using namespace std;
#define maxn 128

int mat[maxn][maxn];
int n;
bool vis[maxn];
int dis[maxn];

int prim() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[0] = 0;
    vis[0] = true;

    int u = 0;
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        int idx = -1;
        for (int v = 0; v < n; ++v) {
            if (!vis[v] && mat[u][v] < dis[v]) {
                dis[v] = mat[u][v];
            }
        }
        for (int v = 0; v < n; ++v) {
            if (!vis[v] && (idx == -1 || dis[v] < dis[idx])) {
                idx = v;
            }
        }
        vis[idx] = true;
        ans += dis[idx];
        u = idx;
    }
    return ans;
}

int main() {
    while (cin >> n) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> mat[i][j];
        cout << prim() << endl;
    }
    return 0;
}
