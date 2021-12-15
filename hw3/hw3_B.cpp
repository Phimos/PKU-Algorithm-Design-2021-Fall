#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

double DOUBLE_MAX = 1e20;

struct Point {
    int x, y, id;
    Point(int x, int y, int id) : x(x), y(y), id(id) {}
    Point() {}
};
Point points[2000], tmp[2000];

double dist(Point& p1, Point& p2) {
    if (p1.id == p2.id)
        return DOUBLE_MAX;
    else
        return sqrt(double(p1.x - p2.x) * double(p1.x - p2.x) +
                    double(p1.y - p2.y) * double(p1.y - p2.y));
}

double mindist;

void solve(int l, int r) {
    if (r - l <= 3) {
        for (int i = l; i <= r; ++i)
            for (int j = i + 1; j <= r; ++j)
                mindist = min(mindist, dist(points[i], points[j]));
        sort(points + l, points + r + 1,
             [](Point& p1, Point& p2) { return p1.y < p2.y; });
        return;
    }

    int m = (l + r) >> 1;
    int midx = points[m].x;
    solve(l, m);
    solve(m + 1, r);
    merge(points + l, points + m + 1, points + m + 1, points + r + 1, tmp,
          [](Point& p1, Point& p2) { return p1.y < p2.y; });
    copy(tmp, tmp + r - l + 1, points + l);

    int psize = 0;
    for (int i = l; i <= r; ++i)
        if (abs(points[i].x - midx) < mindist) {
            for (int j = psize - 1; j >= 0 && points[i].y - tmp[j].y < mindist;
                 --j)
                mindist = min(mindist, dist(points[i], tmp[j]));
            tmp[psize++] = points[i];
        }
}

int main() {
    int t, n, x, y;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < 2 * n; ++i) {
            cin >> x >> y;
            points[i] = Point(x, y, i / n);
        }

        sort(points, points + 2 * n, [](Point& p1, Point& p2) {
            return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
        });

        mindist = DOUBLE_MAX;
        solve(0, 2 * n - 1);
        cout << fixed << setprecision(3) << mindist << endl;
    }
    return 0;
}