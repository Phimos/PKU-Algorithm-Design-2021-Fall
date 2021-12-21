#include <cstring>
#include <iostream>
using namespace std;

int dir[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void bfs(int x, int y, char m[32][32], bool vis[32][32]) {
    vis[x][y] = true;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (!vis[nx][ny] && m[x][y] == m[nx][ny]) {
            bfs(nx, ny, m, vis);
        }
    }
}

int main() {
    int k, n;
    char m[32][32];
    bool vis[32][32];

    cin >> k;
    while (k--) {
        cin >> n;
        for (int i = 0; i < 32; ++i)
            for (int j = 0; j < 32; ++j)
                m[i][j] = '#';
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; ++i) {
            cin >> &m[i][1];
            m[i][n + 1] = '#';
        }
        int cnt_r = 0, cnt_b = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (m[i][j] == 'b' && !vis[i][j]) {
                    ++cnt_b;
                    bfs(i, j, m, vis);
                } else if (m[i][j] == 'r' && !vis[i][j]) {
                    ++cnt_r;
                    bfs(i, j, m, vis);
                }
            }
        }
        cout << cnt_r << ' ' << cnt_b << endl;
    }
}