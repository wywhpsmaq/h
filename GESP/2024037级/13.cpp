int count_triple(int n) {
    int cnt = 0;
    for (int a = 1; a <= n; a++)
        for (int b = a; a + b <= n; b++)
            for (int c = b; a + b + c <= n; c++)
                if (a * a + b * b == c * c) cnt++;
    return cnt;
}