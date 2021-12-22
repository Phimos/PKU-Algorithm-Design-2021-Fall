#include <iostream>
using namespace std;

#define maxn 1024

int lft[maxn], rgt[maxn], par[maxn];

void tree_init() {
    fill(lft, lft + maxn, -1);
    fill(rgt, rgt + maxn, -1);
    fill(par, par + maxn, -1);
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int t, n, m, x, y, z, op;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        tree_init();
        for (int i = 0; i < n; ++i) {
            cin >> x >> y >> z;
            lft[x] = y;
            rgt[x] = z;
            if (~y)
                par[y] = x;
            if (~z)
                par[z] = x;
        }
        for (int i = 0; i < m; ++i) {
            cin >> op;
            if (op == 1) {
                cin >> x >> y;
                if (lft[par[x]] == x && lft[par[y]] == y)
                    swap(&lft[par[x]], &lft[par[y]]);
                else if (lft[par[x]] == x && rgt[par[y]] == y)
                    swap(&lft[par[x]], &rgt[par[y]]);
                else if (rgt[par[x]] == x && lft[par[y]] == y)
                    swap(&rgt[par[x]], &lft[par[y]]);
                else
                    swap(&rgt[par[x]], &rgt[par[y]]);
                swap(par[x], par[y]);
            } else {
                cin >> x;
                while (~lft[x])
                    x = lft[x];
                cout << x << endl;
            }
        }
    }
    return 0;
}
