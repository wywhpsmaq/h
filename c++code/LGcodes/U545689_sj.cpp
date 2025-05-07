#include <bits/stdc++.h>
using namespace std;
string s;
string hw()
{
    random_device rd;
    mt19937 gen (rd ());
    uniform_int_distribution < > f(32,126),f1(1,10);
    string s1;
    int a=f1(gen);
    for(int i=0;i<a;i++)
    {
        s1+=(char)f(gen);
    }
    for(int i=0;i<a;i++)
    {
        s1+=s1[a-i-1];
    }
    return s1;
}
string fhw()
{
    random_device rd;
    mt19937 gen (rd ());
    uniform_int_distribution < > f(32,126),f1(1,7);
    string s1;
    int a=f1(gen);
    for(int i=0;i<a;i++)
    {
        s1+=(char)f(gen);
    }
    return s1;
}
int main() {
    random_device r;
    mt19937 ge (r ());
    uniform_int_distribution < > f(1,3);
    for(int i=0;i<100;i++)
    {
        int n=f(ge);
        if(n==1){
            s+=hw();
        }
        else if(n==2){
            s+=fhw();
        }
        else{
            s+=" "; 
        }
    }
    cout<<s<<'\n'<<s.size();
}