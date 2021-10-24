#include <cstring>
#include <iostream>
using namespace std;

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int fa[1000001];
bool open[1000][1000];

int find(int x) {
    return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    int rootx = find(x);
    int rooty = find(y);
    fa[rootx] = rooty;
}

bool query(int x, int y) {
    return find(x) == find(y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, t, x, y;
    int nx, ny;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        memset(open, 0, sizeof(open));
        for (int i = 0; i < n * n; ++i) {
            fa[i] = i;
        }
        for (int i = 1; i < n; ++i) {
            merge(0, i);
        }
        for (int i = (n - 1) * n + 1; i < n * n; ++i) {
            merge((n - 1) * n, i);
        }

        int ans = 0;
        for (int i = 0; i < m; ++i) {
            cin >> x >> y;
            --x, --y;
            if (ans)
                continue;
            open[x][y] = true;
            for (int j = 0; j < 4; ++j) {
                nx = x + dir[j][0];
                ny = y + dir[j][1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && open[nx][ny]) {
                    merge(nx * n + ny, x * n + y);
                }
            }
            if (query(0, n * n - 1)) {
                ans = i + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}