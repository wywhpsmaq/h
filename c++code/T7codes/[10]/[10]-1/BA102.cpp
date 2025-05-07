#include<bits/stdc++.h>
using namespace std;
int p[999][999];
void fz(int x1, int y1, int x2, int y2, int a) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            p[x1 + i][y1 + j] = p[x2 + i][y2 + j];
        }
    }
}
int main() {
    int a;
    cin >> a;
    int b = pow(2, a);
    for (int i = 1; i <= b; i += pow(2, i)) p[1][i] = i;
    for (int i = 0; i < a; i++) {
        for (int j = 1; j <= b; j += pow(2, i)) {
            if (int((j) / pow(2, i)) % 2 == 1) {
                fz(i + pow(2, i) + 1, j + pow(2, i) + 1, i + 1, j, pow(2, i));
            } else {
                fz(i - pow(2, i) + 1, j - pow(2, i) + 1, i + 1, j, pow(2, i));
            }
        }
    }
    for (int i = 0; i < b; i++) {
        for (int j = 1; j <= b; j++) {
            cout << p[i][j] << " ";
        }
        cout << '\n';
    }
}