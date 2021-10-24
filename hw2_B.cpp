#include <cstring>
#include <iostream>
using namespace std;

int fa[2000];

int find(int x) {
    return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    int rootx = find(x);
    int rooty = find(y);
    fa[rootx] = rooty;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    while (cin >> n >> m) {
        int a, b, rel;
        for (int i = 0; i < 2 * n; ++i) {
            fa[i] = i;
        }

        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> rel;
            if (rel) {
                merge(a + n, b);
                merge(a, b + n);
            } else {
                merge(a, b);
                merge(a + n, b + n);
            }
        }

        bool ok = true;
        for (int i = 0; i < n; ++i) {
            if (find(i) == find(i + n)) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "YES" : "NO") << endl;
    }
    return 0;
}