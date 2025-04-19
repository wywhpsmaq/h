#include <bits/stdc++.h>
using namespace std;
char p[1010][1010];
int id[1010][1010];
int s[1010 * 1010];
int cnt = 0;
int n, m;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
void dfs(int x, int y, int cid)
{
    stack<pair<int, int>> st;
    st.push({x, y});
    id[x][y] = cid;
    s[cid]++;
    while (!st.empty())
    {
        auto [cx, cy] = st.top();
        st.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !id[nx][ny] && p[cx][cy] != p[nx][ny])
            {
                id[nx][ny] = cid;
                s[cid]++;
                st.push({nx, ny});
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> (p[i]);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!id[i][j])
            {
                cnt++;
                dfs(i, j, cnt);
            }
        }
    }
    while (m--)
    {
        int i, j;
        cin >> i >> j;
        cout << s[id[i - 1][j - 1]] << '\n';
    }
    return 0;
}
