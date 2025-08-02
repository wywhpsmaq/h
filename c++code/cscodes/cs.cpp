#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;
int n = 1, m = 0;
bool vis[50][50] = {};
int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
int ex, ey,sx,sy;
char cc[50][50];
int nnnn;
struct uu {int x, y = 0;} p[50][50];
void sc (int idx, int col) {cout << "\033[" << idx << ";" << col << "H";}
void dt (int i, int j, char ch) {
	sc (i, (j - 1) * 3 + 1);
	if (i == ex && j == ey) {cout << "0  ";}
	else if (ch == '*') {cout << "*  ";}
	else {
		if (ch != '0' && ch != '1') {
			cout << "\033[31m" << ch << "\033[0m  ";
		} else {
			if (ch == '0') {cout << "\033[32m0\033[0m  ";}
			else {cout << "\033[33m1\033[0m  ";}
		}
	}
	cout.flush ();
}
void dfs (int sx, int sy) {
	int x = sx, y = sy;
	int lx = 0, ly = 0;
	system ("cls");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i == ex && j == ey) {cout << "0  ";}
			else if (i == sx && j == sy) {cout << "*  ";}
			else {
				if (cc[i][j] != '0' && cc[i][j] != '1') cout << "\033[31m" << cc[i][j] << "\033[0m  ";
				else cout << (cc[i][j] == '0' ? "\033[32m0\033[0m  " : "\033[33m1\033[0m  ");
			}
		}
		cout << '\n';
	}
	cout.flush ();
	while (true) {
		if (x == ex && y == ey) {
			system ("cls");
			cout << "great\ntime:" << time (0) - nnnn;
			exit (0);
		}
		char c = _getch ();
		if (c == 0 || c == -32) { c = _getch (); }
		int nx = x, ny = y;
		if (c == 77) {ny = y + 1;}
        else if (c == 75) {ny = y - 1;} 
        else if (c == 72) {nx = x - 1;}
        else if (c == 80) {nx = x + 1;}
        else {continue;}
		if (nx < 1 || nx > n || ny < 1 || ny > m || p[nx][ny].x != 0) { continue; }
		if (nx != x) {cc[x][y] = '|';}
        else {cc[x][y] = '-';}
		lx = x,ly = y,x = nx,y = ny;
		dt (lx, ly, cc[lx][ly]);
		dt (x, y, '*');
	}
}
int main () {
	random_device rd;
	mt19937 gen (rd ());
	uniform_int_distribution<> f (10, 29);
	n = f (gen), m = f (gen);
	uniform_int_distribution<> f1 (1, n), f2 (1, m);
	int x = f1 (gen), y = f2 (gen);
	sx= x, sy = y;
	ex = f1 (gen), ey = f2 (gen);
	while (x == ex && y == ey) { ex = f1 (gen), ey = f2 (gen); }
	for (int i = 1; i <= n; i++) {for (int j = 1; j <= m; j++) { p[i][j].x = 1; }}
	stack<pair<int, int>> st;
	p[x][y].x = 0;
	st.push ({x, y});
	while (!st.empty ()) {
		auto [cx, cy] = st.top ();
		st.pop ();
		vector<int> dirs = {0, 1, 2, 3};
		shuffle (dirs.begin (), dirs.end (), gen);
		for (int d : dirs) {
			int nx = cx + 2 * dx[d];
			int ny = cy + 2 * dy[d];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && p[nx][ny].x == 1) {
				p[cx + dx[d]][cy + dy[d]].x = 0;
				p[nx][ny].x = 0;
				st.push ({nx, ny});
			}
		}
	}
	if (p[ex][ey].x != 0) {
		queue<pair<int, int>> q;
		vector<vector<bool>> vis (n + 1, vector<bool> (m + 1, false));
		vector<vector<pair<int, int>>> pre (n + 1, vector<pair<int, int>> (m + 1, {-1, -1}));
		q.push ({ex, ey});
		vis[ex][ey] = true;
		pair<int, int> lf = {-1, -1};
		while (!q.empty ()) {
			auto [u, v] = q.front ();
			q.pop ();
			if (p[u][v].x == 0) {
				lf = {u, v};
				break;
			}
			for (int i = 0; i < 4; i++) {
				int nu = u + dx[i], nv = v + dy[i];
				if (nu >= 1 && nu <= n && nv >= 1 && nv <= m && !vis[nu][nv]) {
					vis[nu][nv] = true;
					pre[nu][nv] = {u, v};
					q.push ({nu, nv});
				}
			}
		}
		if (lf.first != -1) {
			auto [u, d] = lf;
			while (u != -1) {
				p[u][d].x = 0;
				auto [px, py] = pre[u][d];
				u = px, d = py;
			}
		}
	}
	for (int i = 1; i <= n; i++) {for (int j = 1; j <= m; j++) { cc[i][j] = '0' + p[i][j].x; }}
	cout<<n<<" "<<m<<'\n'<<sx<<" "<<sy<<" "<<ex<<" "<<ey<<'\n';
	system("pause");
	nnnn = time (0);
	dfs (x, y);
}