#include<iostream>
using namespace std;
template <typename lx,typename lx1> struct pair{
    lx first;
    lx1 second;
    pair(const lx& f, const lx1& s) : first(f), second(s) {}
};
template <typename lx,typename lx1> struct map{
    pair<lx,lx1>* c;
    size_t size;
    size_t capacity;
    
    map() : c(new pair<lx,lx1>[8]), size(0), capacity(8) {}
    
    ~map() { delete[] c; }
    
    void reserve(size_t new_cap) {
        if(new_cap <= capacity) return;
        pair<lx,lx1>* new_c = new pair<lx,lx1>[new_cap];
        for(size_t i=0; i<size; ++i) {
            new_c[i] = c[i];
        }
        delete[] c;
        c = new_c;
        capacity = new_cap;
    }
    
    pair<lx,lx1>* find(const lx& key) {
        for(size_t i=0; i<size; ++i) {
            if(c[i].first == key) return &c[i];
        }
        return nullptr;
    }
    
    lx1& operator[](const lx& key) {
        auto ptr = find(key);
        if(ptr) return ptr->second;
        
        if(size >= capacity) reserve(capacity*2);
        c[size].first = key;
        c[size].second = lx1();
        return c[size++].second;
    }
    
    pair<pair<lx,lx1>*, bool> insert(const pair<lx,lx1>& p) {
        if(auto ptr = find(p.first)) return {ptr, false};
        
        if(size >= capacity) reserve(capacity*2);
        c[size] = p;
        return {&c[size++], true};
    }
    
    bool erase(const lx& key) {
        for(size_t i=0; i<size; ++i) {
            if(c[i].first == key) {
                for(size_t j=i; j<size-1; ++j) c[j] = c[j+1];
                size--;
                return true;
            }
        }
        return false;
    }
    
    typedef pair<lx,lx1>* iterator;
    iterator begin() { return c; }
    iterator end() { return c + size; }
};