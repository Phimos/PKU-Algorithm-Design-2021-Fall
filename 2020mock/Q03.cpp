#include <functional>
#include <iostream>
#include <queue>

using namespace std;

class DynamicMedian {
    priority_queue<int, vector<int>, less<int> > bigroot;
    priority_queue<int, vector<int>, greater<int> > smallroot;

   public:
    int query() { return bigroot.top(); }
    void add(int x) {
        if (bigroot.size() == smallroot.size()) {
            if (smallroot.empty() || x <= smallroot.top())
                bigroot.push(x);
            else {
                bigroot.push(smallroot.top());
                smallroot.pop();
                smallroot.push(x);
            }
        } else {
            if (x >= bigroot.top())
                smallroot.push(x);
            else {
                smallroot.push(bigroot.top());
                bigroot.pop();
                bigroot.push(x);
            }
        }
    }
    void del() {
        if (bigroot.size() == smallroot.size()) {
            bigroot.pop();
            bigroot.push(smallroot.top());
            smallroot.pop();
        } else {
            bigroot.pop();
        }
    }
};

int main() {
    int t, n;
    cin >> t;
    while (t--) {
        DynamicMedian dm;
        cin >> n;
        char op;
        int x;
        for (int i = 0; i < n; ++i) {
            cin >> op;
            if (op == 'I') {
                cin >> x;
                dm.add(x);
            } else if (op == 'Q') {
                cout << dm.query() << endl;
            } else {
                dm.del();
            }
        }
    }
}
