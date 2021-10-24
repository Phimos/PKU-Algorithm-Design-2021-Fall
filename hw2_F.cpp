#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int dist[100][100];
int min_dist[100];
int visit[100];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> dist[i][j];
            }
        }

        memset(min_dist, 0x3f, sizeof(min_dist));
        memset(visit, 0, sizeof(visit));
        int result = 0;
        visit[0] = true;
        for (int i = 0; i < n; ++i) {
            min_dist[i] = dist[0][i];
        }
        for (int i = 1; i < n; ++i) {
            int t = -1;
            for (int j = 0; j < n; ++j) {
                if (!visit[j] && (t == -1 || min_dist[t] > min_dist[j])) {
                    t = j;
                }
            }
            result += min_dist[t];
            visit[t] = true;
            for (int j = 0; j < n; ++j) {
                if (!visit[j]) {
                    min_dist[j] = min(min_dist[j], dist[t][j]);
                }
            }
        }
        cout << result << endl;
    }
    return 0;
}
