//
// Created by wywhpsmaq on 2026/3/28.
//

#ifndef H_TACL_H
#define H_TACL_H

#include <random>
#include <vector>
#endif //H_TACL_H

inline int tc_dfs(const int x, const int y, int num, std::vector<std::vector<int> > &v) {//在x,y处生成num个黑色快
    if (num == 0) return 0;
    v[x][y] = 1;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    int nn = dis(gen);
    int sum = 0;
    int nx = x + dx[nn], ny = y + dy[nn];
    while (nx < 0 || ny < 0 || nx > 49 || ny > 49 || v[nx][ny] != 0 || (nx <= 11 && ny <= 11) || (
               nx <= 11 && ny >= 38) || (nx >= 38 && ny <= 11)) {
        sum++, nn++, nn %= 4;
        if (sum == 5) return 1;
        nx = x + dx[nn], ny = y + dy[nn];
    }
    int temp = tc_dfs(nx, ny, num - 1, v);
    if (temp == 1) v[x][y] = 0;
    return temp;
}

inline std::vector<std::vector<int> > txcl_sc(std::vector<std::vector<int> > v) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 49), ddis(8, 15);
    for (int i = 0; i < 1000; i++) {
        int nx = dis(gen), ny = dis(gen);
        if (v[nx][ny] == 1 || (nx <= 11 && ny <= 11) || (nx <= 11 && ny >= 38) || (nx >= 38 && ny <= 11)) {
            i--;
            continue;
        }
        v[nx][ny] = 1;
    }
    // for (int i = 0; i < 60; i++) {
    //     int nx = dis(gen), ny = dis(gen);
    //     if ((nx <= 12 && ny <= 12) || (nx <= 12 && ny >= 38) || (nx >= 38 && ny <= 12)) {
    //         i--;
    //         continue;
    //     }
    //     if (tc_dfs(nx, ny, ddis(gen), v) == 1) {
    //         v[nx][ny] = 0;
    //         i--;
    //     }
    // }
    return v;
}