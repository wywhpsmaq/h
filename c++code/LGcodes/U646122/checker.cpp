#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[])
{
    setName("T3");
    registerInteraction(argc, argv);

    // 从测试数据中读取输入
    int k = inf.readInt();
    int n = inf.readInt();
    int m = inf.readInt();
    vector<int> arr;

    for (int i = 0;i < k;i++) {
        arr.push_back(inf.readInt());
    }
    int fs = inf.readInt();
    int pa = inf.readInt();

    //塞给交互库
    cout << k << " " << n << " " << m << endl;
    for (int i = 0;i < k;i++) {
        cout << arr[i] << " ";
    }

    vector<int> xs;
    for (int i = 0; i < k; i++) {
        int x;
        cin>>x;
        xs.push_back(x);
    }

    //计算分数
    double xs_fs = 0.00;
    if (pa) {
        xs_fs = fs;
        for (int i = 0;i < k;i++) {
            if (xs[i] != arr[i]) {
                xs_fs = 0.00;
                break;
            }
        }
    }
    else for (int i = 0;i < k;i++) if (xs[i] == arr[i]) xs_fs += fs / k;


    if ((int)xs_fs != fs) quitp(fs / xs_fs, "PC");
    else quitf(_ok, "AC");
}