#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool row[8], lu2rd[16], ld2ru[16];
int board[8][8];
int cnt;

void print_board() {
    cout << "No. " << (++cnt) << endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

void dfs(int cur) {
    if (cur == 8) {
        print_board();
        return;
    }
    for (int i = 0; i < 8; ++i) {
        if (lu2rd[i - cur + 7])
            continue;
        if (ld2ru[i + cur])
            continue;
        if (row[i])
            continue;
        lu2rd[i - cur + 7] = true;
        ld2ru[i + cur] = true;
        row[i] = true;
        board[i][cur] = 1;
        dfs(cur + 1);
        lu2rd[i - cur + 7] = false;
        ld2ru[i + cur] = false;
        row[i] = false;
        board[i][cur] = 0;
    }
}

int main() {
    dfs(0);
}
