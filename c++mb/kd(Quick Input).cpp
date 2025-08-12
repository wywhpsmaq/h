//快读快写
#include <bits/stdc++.h>
using namespace std;

// 快速读取整数
template<typename T>
inline T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
template<typename T>
inline T fastread() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar_unlocked();
    }
    return x * f;
}
// 快速输出整数
template<typename T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
// 刷新输出缓冲区
inline void flush() {
    fflush(stdout);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 使用示例
    int n = read<int>();
    long long m = read<long long>();
    write(n);
    write(m);
    flush();
    return 0;
}