#include <iostream>
using namespace std;

int board[8][8];
bool row[8], col[8];
bool bslash[16];  // backward slash
bool slash[16];
int cnt = 0;

void print_board() {
    cout << "No. " << (++cnt) << endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << board[i][j] << (j < 7 ? " " : "\n");
        }
    }
}

void solve(int col_idx) {
    if (col_idx == 8) {
        print_board();
        return;
    }
    for (int i = 0; i < 8; ++i) {
        if (row[i] || slash[i + col_idx] || bslash[7 - col_idx + i])
            continue;
        bool old_row = row[i];
        bool old_slash = slash[i + col_idx];
        bool old_bslash = bslash[7 - col_idx + i];

        row[i] = true;
        slash[i + col_idx] = true;
        bslash[7 - col_idx + i] = true;
        board[i][col_idx] = 1;

        solve(col_idx + 1);

        row[i] = old_row;
        slash[i + col_idx] = old_slash;
        bslash[7 - col_idx + i] = old_bslash;
        board[i][col_idx] = 0;
    }
}

int main() {
    solve(0);
    return 0;
}