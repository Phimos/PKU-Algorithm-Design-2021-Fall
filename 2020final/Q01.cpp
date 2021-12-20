#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int v, a, x, y;
    cin >> v >> a;

    vector<vector<int>> nxt(v + 1);
    vector<int> in(v + 1, 0);
    vector<bool> visit(v + 1, false);

    for (int i = 0; i < a; ++i) {
        cin >> x >> y;
        nxt[x].push_back(y);
        ++in[y];
    }

    int cnt = 0;
    vector<int> ans;
    while (ans.size() < v) {
        for (int i = 1; i <= v; ++i) {
            if (in[i] == 0 && !visit[i]) {
                ans.push_back(i);
                visit[i] = true;
                for (auto& u : nxt[i])
                    --in[u];
                break;
            }
        }
    }
    for (auto& i : ans) {
        cout << 'v' << i << ' ';
    }
}