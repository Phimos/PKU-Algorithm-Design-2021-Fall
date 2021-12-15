#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

double distance2(double x1, double y1, double x2, double y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, d;
    int num = 0;

    while (cin >> n >> d) {
        if (n == 0 && d == 0)
            break;

        vector<pair<double, double>> islands;
        int x, y;
        double dx;

        bool unable = false;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            if (y > d)
                unable = true;
            if (unable)
                continue;
            dx = sqrt(double(d * d - y * y));
            islands.push_back(make_pair(double(x) - dx, double(x) + dx));
        }

        if (!unable) {
            sort(islands.begin(), islands.end());
            double rx = islands[0].first - 1;
            int cnt = 0;

            for (int i = 0; i < islands.size(); ++i) {
                auto island = islands[i];
                double l = island.first, r = island.second;
                if (rx < l) {
                    rx = r;
                    ++cnt;
                } else if (rx > r) {
                    rx = r;
                }
            }
            cout << "Case " << ++num << ": " << cnt << endl;
        } else {
            cout << "Case " << ++num << ": " << -1 << endl;
        }
    }
    return 0;
}
