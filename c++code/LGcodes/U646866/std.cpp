#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;

// 定义优先队列中的元素结构：存储值、行号、列号
struct Pos {
    ll val;
    int r, c;
    Pos(ll v, int r_, int c_) : val(v), r(r_), c(c_) {}
    // 优先队列默认是大顶堆，按值从大到小排序
    bool operator<(const Pos& other) const {
        return val < other.val;
    }
};

int main() {
    freopen("U646866-sj\\U646866-17.in", "r", stdin);
    freopen("U646866-sj\\U646866-17.out", "w", stdout);
    // 加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    int x, y;
    cin >> n >> x >> y;

    // 存储药片的当前治疗值（行/列从1开始，方便计算矩形范围）
    vector<vector<ll>> a(y + 2, vector<ll>(x + 2, 0));
    // 最大堆：存储药片的（值，行，列）
    priority_queue<Pos> pq;

    // 读取输入并初始化堆
    for (int i = 1; i <= y; ++i) {
        for (int j = 1; j <= x; ++j) {
            cin >> a[i][j];
            if (a[i][j] > 0) {
                pq.emplace(a[i][j], i, j);
            }
        }
    }

    ll total_treatment = 0; // 总治疗值
    int operation_times = 0; // 操作次数（每次吃2片）

    while (n > 0) {
        // 找第一个有效最大元素（堆中值与实际值一致）
        Pos max1(0, 0, 0);
        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            if (a[top.r][top.c] == top.val) { // 有效元素
                max1 = top;
                break;
            }
            // 无效元素（值已被修改），直接跳过
        }

        if (max1.val == 0) { // 没有有效药片了
            break;
        }

        // 找第二个有效最大元素（排除第一个的位置）
        Pos max2(0, 0, 0);
        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            if (a[top.r][top.c] == top.val && !(top.r == max1.r && top.c == max1.c)) {
                max2 = top;
                break;
            }
            // 无效元素，直接跳过
        }

        if (max2.val == 0) { // 只剩一片有效药片，无法操作
            break;
        }

        // 计算本次治疗值，并更新剩余严重值
        ll prod = max1.val * max2.val;
        total_treatment += prod;
        operation_times += 1;
        n -= prod;

        if (n <= 0) {
            break;
        }

        // 1. 将选中的两片药归零
        a[max1.r][max1.c] = 0;
        a[max2.r][max2.c] = 0;

        // 2. 计算以两片药为对角的矩形范围
        int r_min = min(max1.r, max2.r);
        int r_max = max(max1.r, max2.r);
        int c_min = min(max1.c, max2.c);
        int c_max = max(max1.c, max2.c);

        // 3. 矩形内所有药片减1，并更新堆
        for (int i = r_min; i <= r_max; ++i) {
            for (int j = c_min; j <= c_max; ++j) {
                if (a[i][j] > 0) {
                    a[i][j] -= 1;
                    pq.emplace(a[i][j], i, j); // 把修改后的值加入堆
                }
            }
        }

        // 将归零的药片加入堆（后续会被判定为无效，不影响）
        pq.emplace(0, max1.r, max1.c);
        pq.emplace(0, max2.r, max2.c);
    }

    // 输出结果
    if (n <= 0) {
        cout << 2 * operation_times << " " << total_treatment << endl;
    }
    else {
        cout << "Not even a little!" << endl;
    }

    return 0;
}