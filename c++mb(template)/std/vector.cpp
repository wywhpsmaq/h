#include<iostream>
using namespace std;
template <typename lx> struct vector {
    lx c[114514];
    int tot = 0;
    void push_back(int x) {
        c[tot++] = x;
    }
    void pop_back() {
        tot--;
    }
    int size() {
        return tot + 1;
    }
    vector operator[](vector& x) {
        return x.c;
    }
    vector operator=(int n) {
        return c[n];
    }
    friend ostream& operator<<(ostream& out, const vector& x) {
        for (int i = 0; i < x.tot; i++) {
            out << x.c[i] << " ";
        }
        return out;
    }

};
int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.pop_back();
    cout << v;
}