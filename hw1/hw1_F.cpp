#include <iostream>
using namespace std;

int _left[100], _right[100], _parent[100];

void init() {
    fill(_left, _left + 100, -1);
    fill(_right, _right + 100, -1);
    fill(_parent, _parent + 100, -1);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        init();
        int n, m;
        cin >> n >> m;
        int x, y, z;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y >> z;
            if (~y) {
                _left[x] = y;
                _parent[y] = x;
            }
            if (~z) {
                _right[x] = z;
                _parent[z] = x;
            }
        }

        int op;
        for (int i = 0; i < m; ++i) {
            cin >> op;
            if (op == 1) {
                cin >> x >> y;
                if (_left[_parent[x]] == x && _left[_parent[y]] == y) {
                    swap(_left[_parent[x]], _left[_parent[y]]);
                } else if (_left[_parent[x]] == x && _right[_parent[y]] == y) {
                    swap(_left[_parent[x]], _right[_parent[y]]);
                } else if (_right[_parent[x]] == x && _left[_parent[y]] == y) {
                    swap(_right[_parent[x]], _left[_parent[y]]);
                } else {
                    swap(_right[_parent[x]], _right[_parent[y]]);
                }
                swap(_parent[x], _parent[y]);
            } else {
                cin >> x;
                while (~_left[x])
                    x = _left[x];
                cout << x << endl;
            }
        }
    }
    return 0;
}