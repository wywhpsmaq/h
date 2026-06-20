#include<iostream>
using namespace std;

template<typename lx>
struct vector {
    lx c[114514];
    int tot = 0;
    void push_back(const lx &x) { c[tot++] = x; } //O(1)
    void pop_back() { if (tot > 0) tot--; } //O(1)
    int size() const { return tot; } //O(1)
    lx &operator[](int idx) { return c[idx]; } //O(1)
    const lx &operator[](int idx) const { return c[idx]; } //O(1)
    lx *begin() { return c; } //O(1)
    lx *end() { return c + tot; } //O(1)
    const lx *begin() const { return c; } //O(1)
    const lx *end() const { return c + tot; } //O(1)
    bool empty() const { return tot == 0; } //O(1)
    void clear() { tot = 0; } //O(1)
    void erase(const int idx) { //O(n)
        for (int i = idx; i < tot - 1; i++) { c[i] = c[i + 1]; }
        tot--;
    }

    void insert(int idx, const lx &x) { //O(n)
        for (int i = tot; i > idx; i--) { c[i] = c[i - 1]; }
        c[idx] = x;
        tot++;
    }

    bool operator<(vector<lx> const &v) {
        for (int i = 0; i < min(v.size(), tot); i++) { if (c[i] > v[i]) return true; }
        return false;
    }

    friend ostream &operator<<(ostream &out, const vector &x) { //O(n)
        for (int i = 0; i < x.tot; i++) { out << x.c[i] << " "; }
        return out;
    }

    friend istream &operator>>(istream &in, vector &x) { //O(n)
        lx xx;
        while (cin >> xx) x.push_back(xx);
        return in;
    }
};

int main() {
    int x;
    vector<int> v, v1;
    for (int i = 0; i < 5; i++) {
        cin >> x;
        v.push_back(x);
    }
    for (int i = 0; i < 5; i++) {
        cin >> x;
        v1.push_back(x);
    }
    cout << (v < v1);
}
