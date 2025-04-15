#include<bits/stdc++.h>
using namespace std;

bool canGet24(const vector<int>& nums) {
    char ops[] = {'+', '-', '*'};
    
    for (char op1 : ops) {
        for (char op2 : ops) {
            for (char op3 : ops) {
                int result = nums[0];
                
                // 第一个运算符
                if (op1 == '+') result += nums[1];
                else if (op1 == '-') result -= nums[1];
                else result *= nums[1];
                
                // 第二个运算符
                if (op2 == '+') result += nums[2];
                else if (op2 == '-') result -= nums[2];
                else result *= nums[2];
                
                // 第三个运算符
                if (op3 == '+') result += nums[3];
                else if (op3 == '-') result -= nums[3];
                else result *= nums[3];
                
                if (result == 24) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    int count = 0;
    
    for (int i = 0; i < n; ++i) {
        vector<int> nums(4);
        for (int j = 0; j < 4; ++j) {
            cin >> nums[j];
        }
        if (canGet24(nums)) {
            count++;
        }
    }
    
    cout << count << endl;
    return 0;
}
