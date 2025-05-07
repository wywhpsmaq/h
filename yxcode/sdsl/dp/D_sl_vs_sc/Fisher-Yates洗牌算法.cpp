#include <bits/stdc++.h>
using namespace std;
//sl-html
// Fisher-Yates洗牌算法
class clsl {
private:
    vector<vector<char>> s;
    vector<vector<char>> l;
    int rows, cols;
    int m;

    void initializes() {
        int count = m;
        while (count > 0) {
            int x = rand() % rows;
            int y = rand() % cols;
            if (s[x][y] != '*') {
                s[x][y] = '*';
                count--;
            }
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (s[i][j] != '*') {
                    int count = f(i, j);
                    s[i][j] = count + '0';
                }
            }
        }
    }
    int f(int x, int y) {
        int count = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newX = x + i;
                int newY = y + j;
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                    if (s[newX][newY] == '*') count++;
                }
            }
        }
        return count;
    }

public:
    clsl(int r = 10, int c = 10, int m = 10) : rows(r), cols(c), m(m) {
        s = vector<vector<char>>(rows, vector<char>(cols, '0'));
        l = vector<vector<char>>(rows, vector<char>(cols, '.'));
        srand(time(0));
        initializes();
    }

    void prints() {
        cout << "  ";
        for (int j = 0; j < cols; j++) cout << j << " ";
        cout << "\n";
        for (int i = 0; i < rows; i++) {
            cout << i << " ";
            for (int j = 0; j < cols; j++) {
                cout << l[i][j] << " ";
            }
            cout << "\n";
        }
    }

    bool cell(int x, int y) {
        if (s[x][y] == '*') return false;
        l[x][y] = s[x][y];
        return true;
    }
};

int main() {
    clsl game(8, 8, 10); // 8x8 s with 10 m
    bool ga = false;
    while (!ga) {
        game.prints();
        int x, y;
        cout << "Enter row and column (x y): ";
        cin >> x >> y;

        if (x < 0 || x >= 8 || y < 0 || y >= 8) {
            cout << "Invalid coordinates!\n";
            continue;
        }

        if (!game.cell(x, y)) {
            cout << "Game Over! You hit a mine!\n";
            ga = true;
        }
    }
    return 0;
}