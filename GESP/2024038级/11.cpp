int choose(int n, int m) {
    if (m == 0 || m == n) return 1;
    return choose(n - 1, m - 1) + choose(n - 1, m);
}