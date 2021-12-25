#include <iostream>
using namespace std;
#define maxn 30010

int fa[maxn];
int n, m;

int getroot(int x) {
    return fa[x] == x ? x : fa[x] = getroot(fa[x]);
}

void merge(int x, int y) {
    int rootx = getroot(x);
    int rooty = getroot(y);
    fa[rootx] = rooty;
}

void init() {
    for (int i = 0; i < n; ++i)
        fa[i] = i;
}

int main() {
    while (cin >> n >> m, n || m) {
        init();
        int a, b, k;
        for (int i = 0; i < m; ++i) {
            cin >> k;
            for (int j = 0; j < k; ++j) {
                if (j == 0) {
                    cin >> a;
                } else {
                    cin >> b;
                    merge(a, b);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (getroot(i) == getroot(0)) {
                ++ans;
            }
        }
        cout << ans << endl;
    }
}
