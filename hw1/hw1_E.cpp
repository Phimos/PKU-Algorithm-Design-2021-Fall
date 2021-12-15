#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

char room[24][24];
bool vis[24][24];
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main() {
    int w, h;
    while (cin >> w >> h, w || h) {
        memset(vis, 0, sizeof(vis));
        memset(room, 0, sizeof(room));
        for (int i = 0; i < h; ++i) {
            cin >> room[i];
        }

        int sx, sy;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (room[i][j] == '@') {
                    sx = i, sy = j;
                }
            }
        }

        queue<pair<int, int>> q;
        q.emplace(sx, sy);
        vis[sx][sy] = true;

        int cnt = 0;
        while (!q.empty()) {
            auto tmp = q.front();
            int x = tmp.first;
            int y = tmp.second;
            q.pop();
            ++cnt;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dir[i][0];
                int ny = y + dir[i][1];
                if (nx >= 0 && nx < h && ny >= 0 && ny < w &&
                    room[nx][ny] == '.' && !vis[nx][ny]) {
                    vis[nx][ny] = true;
                    q.emplace(nx, ny);
                }
            }
        }
        cout << cnt << endl;
    }
    return 0;
}