#include <iostream>
#include <vector>
using namespace std;
#define maxn 1024
int w[maxn], s[maxn];
double t[maxn];

int main() {
    int max_load, length, n;
    while (cin >> max_load >> length >> n, n) {
        for (int i = 1; i <= n; ++i)
            cin >> w[i] >> s[i];
        t[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int min_speed = s[i];
            int sum_weight = 0;
            t[i] = 1e10;
            for (int j = i; j > 0; --j) {
                min_speed = min(min_speed, s[j]);
                sum_weight += w[j];
                if (sum_weight <= max_load)
                    t[i] = min(t[j - 1] + (double)length / (double)min_speed,
                               t[i]);
                else
                    break;
            }
        }
        printf("%.1lf\n", t[n] * 60.);
    }
    return 0;
}
