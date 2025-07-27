#include<iostream>
using namespace std;
template <typename lx> struct vector {
    lx c[114514];
    int tot = 0;
    void push_back(const lx& x) {c[tot++] = x;}                                                                                                   
    void pop_back() {if (tot > 0) tot--;}
    int size() const {return tot;}
    lx& operator[](int idx) {return c[idx];}
    const lx& operator[](int idx) const {return c[idx];}
    lx* begin() {return c;}
    lx* end() {return c + tot;}
    const lx* begin() const {return c;}
    const lx* end() const {return c + tot;}
    bool empty() const {return tot == 0;}
    void clear() {tot = 0;}
    void erase(int idx) {
        for (int i = idx; i < tot - 1; i++) {
            c[i] = c[i + 1];
        }
        tot--;
    }
    void insert(int idx, const lx& x) {
        for (int i = tot; i > idx; i--) {
            c[i] = c[i - 1];
        }
        c[idx] = x;
        tot++;
    }
    friend ostream& operator<<(ostream& out, const vector& x) {
        for (int i = 0; i < x.tot; i++) {
            out << x.c[i] << " ";
        }
        return out;
    }
};
int main() {
    
}