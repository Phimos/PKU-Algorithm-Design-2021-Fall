#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

#define maxn 2048

int dis[maxn][maxn];
int mindis[maxn];
char str[maxn][8];
bool vis[maxn];
int n;

int prim() {
    int ans = 0;
    mindis[0] = 0;
    memset(vis, 0, sizeof(vis));
    vis[0] = true;

    for (int i = 1; i < n; ++i) {
        mindis[i] = dis[0][i];
    }
    mindis[0] = 0;
    for (int i = 1; i < n; ++i) {
        int idx = -1, minimum = 0x7fffffff;
        for (int j = 0; j < n; ++j) {
            if (!vis[j] && mindis[j] < minimum) {
                idx = j;
                minimum = mindis[j];
            }
        }
        vis[idx] = true;
        ans += mindis[idx];
        for (int j = 0; j < n; ++j) {
            if (vis[j])
                continue;
            mindis[j] = min(mindis[j], dis[idx][j]);
        }
    }
    return ans;
}

int main() {
    while (scanf("%d", &n), n) {
        memset(dis, 0, sizeof(dis));
        for (int i = 0; i < n; ++i)
            scanf("%s", str[i]);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = 0; k < 7; ++k) {
                    if (str[i][k] != str[j][k])
                        ++dis[i][j];
                }
                dis[j][i] = dis[i][j];
            }
        }
        printf("The highest possible quality is 1/%d.\n", prim());
    }
    return 0;
}