#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

map<string, int> index_mapping;
vector<string> currencies;

double mat[32][32];
double dis[32];
int cnt[32];
int t, n, m;

bool spfa() {
    for (int i = 0; i < n; ++i) {
        dis[i] = 0;
        cnt[i] = 0;
    }
    dis[0] = 1;
    cnt[0] = 1;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; ++v) {
            if (dis[u] * mat[u][v] > dis[v] + 1e-8) {
                dis[v] = dis[u] * mat[u][v];
                ++cnt[v];
                q.push(v);
                if (cnt[v] > n)
                    return true;
            }
        }
    }
    return false;
}

int main() {
    string namea, nameb;
    double rate;
    t = 0;
    while (cin >> n, n) {
        ++t;
        currencies.clear();
        index_mapping.clear();
        memset(mat, 0, sizeof(mat));

        for (int i = 0; i < n; ++i) {
            cin >> namea;
            currencies.push_back(namea);
            index_mapping[namea] = i;
        }
        cin >> m;
        for (int i = 0; i < m; ++i) {
            cin >> namea >> rate >> nameb;
            mat[index_mapping[namea]][index_mapping[nameb]] = rate;
        }

        cout << "Case " << t << ": " << (spfa() ? "Yes" : "No") << endl;
    }
}
