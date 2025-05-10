#include<bits/stdc++.h>
using namespace std;
struct uu {
    int a, b, c, d;
};
uu a, b, c, d;
int main() {
    cin >> a.a >> a.b >> a.c;
    cin >> b.a >> b.b >> b.c;
    cin >> c.a >> c.b >> c.c;
    cin >> d.a >> d.b >> d.c;
    for (int i = 1; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            for (int k = 0; k <= 100; k++) {
                for (int o = 0; o <= 100; o++) {
                    if (i * a.a == j * b.a + k * c.a + o * d.a && i * a.b == j * b.b + k * c.b + o * d.b && i * a.c == j * b.c + k * c.c + o * d.c) {
                        cout << j << " " << k << " " << o << " " << i;
                        return 0;
                    }
                }
            }
        }
    }
    cout << "NONE";
}