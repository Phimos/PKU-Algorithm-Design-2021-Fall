#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void solve(int infix_l,
           int infix_r,
           int post_l,
           int post_r,
           vector<int>& infix,
           vector<int>& post,
           vector<int>& pre) {
    if (infix_r < infix_l || post_r < post_l)
        return;
    int root_idx = -1;
    for (int i = infix_l; i <= infix_r; ++i) {
        if (infix[i] == post[post_r]) {
            root_idx = i;
        }
    }
    pre.push_back(infix[root_idx]);
    solve(infix_l, root_idx - 1, post_l, post_l + root_idx - infix_l - 1, infix,
          post, pre);
    solve(root_idx + 1, infix_r, post_r - infix_r + root_idx, post_r - 1, infix,
          post, pre);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    stringstream ss;
    string s;
    vector<int> infix, post;
    int x;

    getline(cin, s);
    ss.clear();
    ss << s;
    while (ss >> x)
        infix.push_back(x);

    getline(cin, s);
    ss.clear();
    ss << s;
    while (ss >> x)
        post.push_back(x);

    vector<int> pre;
    solve(0, infix.size() - 1, 0, post.size() - 1, infix, post, pre);
    for (auto& n : pre) {
        cout << n << ' ';
    }
}