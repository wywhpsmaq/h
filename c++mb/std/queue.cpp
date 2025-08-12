#include<iostream>
using namespace std;
template <typename lx> struct queue {
    lx c[114514];
    int tot=0,head=0,tail=0;
    void push(const lx& x) {c[tail++]=x;tot++;}
    void pop() {if (tot>0) {head++;tot--;}}
    int size() const {return tot;}
    lx& front() {return c[head];}
    lx& back() {return c[tail-1];}
    bool empty() const {return tot==0;}
    void clear() {tot=0;head=0;tail=0;}
};
int main() {
    
}