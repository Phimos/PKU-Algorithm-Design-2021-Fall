#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    int ans = 0;
    vector<int> seq;

    for (int i = 0; i < n; ++i) {
        int ub = upper_bound(seq.begin(), seq.end(), nums[i]) - seq.begin();
        if (ub == seq.size() && (seq.empty() || nums[i] != seq.back()))
            seq.push_back(nums[i]);
        else
            seq[ub] = nums[i];
        ans = max(ans, int(seq.size()));
    }
    cout << ans << endl;
}