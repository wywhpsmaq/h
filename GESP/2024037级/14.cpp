#include <iostream>
    using namespace std;
int down(int n) {
    if (n <= 1) return n;
    return down(n - 1) + down(n - 2) + down(n - 3);
}
int main() {
    cout << down(6) << endl;
    return 0;
}
