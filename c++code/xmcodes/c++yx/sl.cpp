#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
vector<vector<bool> > dt;
vector<vector<pair<int, int> > > v;
void ks() { cout << "扫雷游戏\n"; }

void sc() {
    cout << "    ";
    for (int i = 1; i <= v.size() - 2; i++) { cout << "\033[34m" << setw(3) << i; }
    cout << '\n';
    for (int i = 1; i <= v.size() - 2; i++) {
        cout << "\033[34m" << setw(3) << i << " ";
        for (int j = 1; j <= v[i].size() - 2; j++) {
            if (v[i][j].second == 0) cout << "\033[0m" << setw(3) << "*";
            else if (v[i][j].second == 1) cout << "\033[32m" << setw(3) << v[i][j].first;
            else if (v[i][j].second == -1) cout << "\033[31m" << setw(3) << "|";
            else if (v[i][j].second == -2) cout << "\033[0m" << setw(3) << "-";
        }
        cout << '\n';
    }
}

int dk(const int x, const int y) {
    int ans = 0;
    if (v[x][y].second == 1 || v[x][y].second == -1 || v[x][y].second == -2) return 0;
    if (x < 1 || y < 1 || x > v.size() - 2 || y > v.size() - 2) return 0;
    if (v[x][y].first == 9) return 0;
    v[x][y].second = 1;
    if (v[x][y].first != 0) return 1;
    v[x][y].second = -2;
    for (int i = 0; i < 4; i++) {
        constexpr int dy[] = {0, 0, 1, -1};
        constexpr int dx[] = {1, -1, 0, 0};
        const int nx = x + dx[i], ny = y + dy[i];
        ans += dk(nx, ny);
    }
    return ans + 1;
}

void js(const int n) { if (n == 0) cout << "踩到雷了！！！"; }

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "UTF-8");
    random_device rd;
    mt19937 gen(rd());
    ks();
    int a, n;
    cin >> a >> n;
    if (n == 0) { n = a * a / 10; }
    dt.resize(a + 2), v.resize(a + 2);
    for (int i = 0; i <= a + 1; i++) { dt[i].resize(a + 2), v[i].resize(a + 2); }
    for (int i = 0; i < n; i++) {
        uniform_int_distribution dist(1, a);
        int x = dist(gen), y = dist(gen);
        while (dt[x][y]) { x = dist(gen), y = dist(gen); }
        dt[x][y] = true;
    }
    for (int i = 2; i <= a; i++) {
        for (int j = 1; j <= a; j++) { cout << dt[i][j] << " "; }
        cout << '\n';
    }
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= a; j++) {
            v[i][j].first = dt[i - 1][j - 1] + dt[i - 1][j] + dt[i - 1][j + 1] + dt[i][j - 1] + dt[i][j + 1] + dt[i + 1]
                            [j - 1] + dt[i + 1][j] + dt[i + 1][j + 1];
            if (dt[i][j]) v[i][j].first = 9;
        }
    }
    cout << '\n';
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= a; j++) { cout << v[i][j].first << " "; }
        cout << '\n';
    }
    int x, y, k, num = n, sum = a * a - n;
    while (num && sum) {
        sc();
        cin >> x >> y >> k;
        if (k == 0) { //打开
            if (dt[x][y]) {
                js(0);
                return 0;
            }
            sum -= dk(x, y);
        } else if (k == 1) { //标记
            if (dt[x][y]) { num--; }
            v[x][y].second = -1;
        } else {}
    }
    cout << "恭喜，成功了！！！";
}
