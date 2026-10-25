#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

// 定义结构体存储地毯信息
struct Carpet {
    int a, b, g, k; // 左下角坐标(a,b) 和右上角坐标(g,k)
};

const int N = 10005;
Carpet carpets[N];
int n, m, t, ans = -1;

int main() {
    int x, y;

    // 读取地毯数量
    scanf("%d", &n);

    // 读取每张地毯的信息
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &carpets[i].a, &carpets[i].b,&carpets[i].g, &carpets[i].k);
    }

    // 读取查询点坐标
    scanf("%d%d", &x, &y);

    // 从后往前遍历，找到最上面覆盖该点的地毯
    for (int i = n; i >= 1; i--) {
        // 判断点是否在某个地毯范围内
        // x >= a && x <= g && y >= b && y <= k
        if (x >= carpets[i].a && x <= carpets[i].g && 
            y >= carpets[i].b && y <= carpets[i].k) {
            ans = i;  // 找到最上面的地毯编号
            break;    // 因为是逆序遍历，第一个满足条件的就是最上面的
        }
    }

    // 输出结果
    printf("%d\n", ans);

    return 0;
}
