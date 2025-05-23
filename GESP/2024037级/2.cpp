int pos[8];
void queen(int n) {
    for (int i = 0; i < 8; i++) {
        pos[n] = i;
        bool attacked = false;
        for (int j = 0; j < n; j++)
            if (pos[n] == pos[j] || pos[n] + n == pos[j] + j || pos[n] - n == pos[j] - j) {
                attacked = true;
                break;
            }
        if (attacked) continue;
        if (n == 7) {
            return;
        } else {
            queen(n + 1);
        }
    }
}