#include <bits/stdc++.h>
using namespace std;
string s="",s1="",s11="put on:";
void js(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> f(0, n),fff(1000,9999);
    int a = time(0), m = f(gen);
    cout<<" "<<(3-m)*(fff(gen)/100)<<"KB\\s";
    while (1) {
        if (time(0)==a+m){
            return;
        } 
    }
}

void ff(){
    for(int i=1;i<=20;i++){
        system("cls");
        cout<<s1<<" [";
        for(int j=0;j<i;j++)
        {
            cout<<'=';
        }
        cout<<"] ";
        cout<<i*5<<"%";
        js(2);
    }
}
int main() {
    s="Wywhpsmaq";
    string s_=" [====================] 100%\n";
    
    s1=s;
    ff();
    
    s1=s+s_;
    s="wywhpsmaq";
    s1+=s;
    s=s1;
    ff();
    
    s1=s+s_;
    s="1123";
    s1+=s;
    s=s1;
    ff();
}