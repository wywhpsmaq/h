#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
struct man {
    int xl;
    int dj[20];
};
int zd, jd;
int zjd[50];
int ain[50] = {-1};
int sh = 1;
random_device rd;
mt19937 gen (rd ());
string name;
man m1, m2;
int aq = -1;
bool xyg = true;

void dj1 (int yy) {
    if (!yy) {
        cout << name << "使用了刀" << endl;
        cout << "下一发伤害+1！！！" << endl;
        m1.dj[1]--;
    } else {
        cout << "它使用了刀" << endl;
        cout << "下一发伤害+1！！！" << endl;
        m2.dj[1]--;
    }
    sh++;
}

void dj2 (int yy) {
    if (!yy) {
        cout << name << "使用了手铐" << endl;
        cout << "它被困住了！！！" << endl;
        m1.dj[2]--;
        xyg = true; // 锁住对手
    } else {
        cout << "它使用了手铐" << endl;
        cout << name << "被困住了！！！" << endl;
        m2.dj[2]--;
        xyg = false; // 锁住玩家
    }
}

void dj3 (int num, int yy) {
    if (!yy) {
        cout << name << "使用了电话" << endl;
        uniform_int_distribution<> f (num, zd + jd);
        int x = f (gen);
        cout << "第" << x << "发子弹是" << (zjd[x] > 0 ? "真" : "假") << "的！！！" << endl;
        m1.dj[3]--;
    } else {
        cout << "它使用了电话" << endl;
        uniform_int_distribution<> f (num, zd + jd);
        int x = f (gen);
        ain[x] = zjd[x];
        cout << "第" << x << "发子弹是" << (zjd[x] > 0 ? "真" : "假") << "的！！！" << endl;
        m2.dj[3]--;
    }
}

void dj4 (int *num, int yy) {
    if (!yy) {
        cout << name << "使用了汽水" << endl;
        cout << name << "退掉了一发子弹！！！" << endl;
        m1.dj[4]--;
    } else {
        cout << "它使用了汽水" << endl;
        cout << "它退掉了一发子弹！！！" << endl;
        m2.dj[4]--;
    }
    (*num)++;
}

void dj5 (int num, int yy) {
    if (!yy) {
        cout << name << "使用了放大镜" << endl;
        cout << "这发子弹是" << (zjd[num] > 0 ? "真" : "假") << "的！！！" << endl;
        m1.dj[5]--;
    } else {
        cout << "它使用了放大镜" << endl;
        ain[num] = zjd[num];
        cout << "这发子弹是" << (zjd[num] > 0 ? "真" : "假") << "的！！！" << endl;
        m2.dj[5]--;
    }
}

void dj6 (int yy) {
    if (!yy) {
        cout << name << "使用了药" << endl;
        cout << name << "恢复了1点血量！！！" << endl;
        m1.xl++;
        m1.dj[6]--;
    } else {
        cout << "它使用了药" << endl;
        cout << "它恢复了1点血量！！！" << endl;
        m2.xl++;
        m2.dj[6]--;
    }
}

// 增强版AI逻辑，支持多道具组合
void dl (int *num) {
    // 策略1: 生命值低于30%时优先治疗
    if (m2.xl <= 3 && m2.dj[6] > 0) {
        dj6(1);
        return;
    }
    
    // 策略2: 组合刀+手铐攻击
    if (sh == 1 && m2.dj[1] > 0 && m2.dj[2] > 0) {
        dj1(1);
        dj2(1);
        return;
    }
    
    // 策略3: 危险子弹处理（最后3发子弹）
    int remaining = zd + jd - *num + 1;
    if (remaining <= 3) {
        // 优先使用放大镜查看当前子弹
        if (m2.dj[5] > 0 && ain[*num] == -1) {
            dj5(*num, 1);
        }
        
        // 如果是假子弹且血量不足，使用汽水跳过
        if (ain[*num] == 0 && m2.xl < 3 && m2.dj[4] > 0) {
            dj4(num, 1);
            return;
        }
        
        // 使用电话获取关键信息
        if (m2.dj[3] > 0) {
            dj3(*num, 1);
            return;
        }
    }
    
    // 策略4: 优势时压制对手
    if (m2.xl > m1.xl && m2.dj[2] > 0) {
        dj2(1); // 用手铐锁住对手
        if (m2.dj[1] > 0) {
            dj1(1); // 再用刀增加伤害
        }
        return;
    }
    
    // 策略5: 随机使用其他道具
    vector<int> available;
    for (int i = 1; i <= 6; i++) {
        if (m2.dj[i] > 0) available.push_back(i);
    }
    
    if (!available.empty()) {
        // 优先使用高价值道具
        vector<int> priorityList = {2, 1, 5, 3, 6, 4}; // 手铐 > 刀 > 放大镜 > 电话 > 药 > 汽水
        
        for (int prop : priorityList) {
            auto it = find(available.begin(), available.end(), prop);
            if (it != available.end()) {
                switch (prop) {
                    case 1: dj1(1); return;
                    case 2: dj2(1); return;
                    case 3: dj3(*num, 1); return;
                    case 4: dj4(num, 1); return;
                    case 5: dj5(*num, 1); return;
                    case 6: dj6(1); return;
                }
            }
        }
    }
    
    cout << "它没有可用的道具！" << endl;
}

// 增强版AI开枪决策
int makeShootDecision(int num) {
    // 如果知道当前子弹信息
    if (ain[num] != -1) {
        // 假子弹：向自己开枪（安全）
        if (ain[num] == 0) return 1;
        // 真子弹：向玩家开枪
        return 2;
    }
    
    // 不知道子弹信息时的策略
    int remaining = zd + jd - num + 1;
    
    // 策略1: 最后几发子弹时保守策略
    if (remaining <= 2) {
        // 自己血量高时向自己开枪
        if (m2.xl > m1.xl) return 1;
        // 玩家血量高时向玩家开枪
        return 2;
    }
    
    // 策略2: 根据血量比例决策
    float selfRatio = (float)m2.xl / (m1.xl + m2.xl);
    uniform_real_distribution<> dis(0.0, 1.0);
    
    // 血量占优时更可能向自己开枪
    if (selfRatio > 0.6 && dis(gen) > 0.3) return 1;
    // 血量劣势时更可能向玩家开枪
    if (selfRatio < 0.4 && dis(gen) > 0.3) return 2;
    
    // 默认策略：随机选择
    uniform_int_distribution<> shoot(1, 2);
    return shoot(gen);
}

void generate_new_props () {
    memset (m1.dj, 0, sizeof (m1.dj));
    memset (m2.dj, 0, sizeof (m2.dj));
    uniform_int_distribution<> djs (3, 8); // 减少道具数量使决策更重要
    int djs1 = djs (gen);
    
    // 玩家道具
    for (int i = 0; i < djs1; i++) {
        uniform_int_distribution<> dj1 (1, 6);
        int type = dj1 (gen);
        m1.dj[type]++;
    }
    
    // AI道具 - 增加手铐和刀的概率
    for (int i = 0; i < djs1; i++) {
        // 增加手铐(2)和刀(1)的权重
        vector<int> weighted = {1,1,1,2,2,3,3,4,5,6};
        uniform_int_distribution<> idx(0, weighted.size()-1);
        int type = weighted[idx(gen)];
        m2.dj[type]++;
    }
    
    cout << name << "的新道具:\n"
         << m1.dj[1] << "个刀，" << m1.dj[2] << "个手铐，" << m1.dj[3] << "个电话，" << m1.dj[4] << "个汽水，" << m1.dj[5] << "个放大镜，" << m1.dj[6]
         << "个药，" << endl;
    cout << "它的新道具:\n"
         << m2.dj[1] << "个刀，" << m2.dj[2] << "个手铐，" << m2.dj[3] << "个电话，" << m2.dj[4] << "个汽水，" << m2.dj[5] << "个放大镜，" << m2.dj[6]
         << "个药，" << endl;
}

void generate_new_bullets () {
    memset (zjd, -1, sizeof (zjd));
    uniform_int_distribution<> zds (2, 8); // 增加子弹数量
    zd = zds (gen);
    jd = zds (gen);
    uniform_int_distribution<> wz (1, zd + jd);
    
    for (int i = 0; i < zd; i++) {
        int xy = wz (gen);
        while (zjd[xy] != -1) xy = wz (gen);
        zjd[xy] = 1;
    }
    for (int i = 0; i < jd; i++) {
        int xy = wz (gen);
        while (zjd[xy] != -1) xy = wz (gen);
        zjd[xy] = 0;
    }
}

void games () {
    int num = 1;
    sh = 1;
    aq = -1;
    xyg = false;
    memset(ain, -1, sizeof(ain)); // 重置子弹信息记录
    generate_new_bullets ();
    memset (m1.dj, 0, sizeof (m1.dj));
    memset (m2.dj, 0, sizeof (m2.dj));
    
    cout << "有" << zd << "发真子弹，" << jd << "发假子弹！！！" << endl;
    system ("pause");
    system ("cls");
    
    generate_new_props ();
    system ("pause");
    cout << "开始！！！";
    system ("pause");
    system ("cls");
    
    while (m1.xl > 0 && m2.xl > 0) {
        bool zxy = xyg;
        if (num > zd + jd) {
            cout << "子弹用完了，重新生成子弹和道具！！！" << endl;
            num = 1;
            sh = 1;
            memset(ain, -1, sizeof(ain));
            generate_new_bullets ();
            generate_new_props ();
            cout << "新的一轮有" << zd << "发真子弹，" << jd << "发假子弹！！！" << endl;
            system ("pause");
            system ("cls");
        }
        
        if (!xyg) { // 玩家回合
            cout << "你的回合！！！" << endl;
            cout << name << "的血量:" << m1.xl << endl;
            cout << "它的血量:" << m2.xl << endl;
            cout << "当前是第" << num << "发子弹" << endl;
            cout << name << "的道具:\n"
                 << "1." << m1.dj[1] << "个刀， 2." << m1.dj[2] << "个手铐， 3." << m1.dj[3] << "个电话， 4." << m1.dj[4] << "个汽水， 5." << m1.dj[5]
                 << "个放大镜， 6." << m1.dj[6] << "个药。" << endl;

            bool continueUsing = true;
            while (continueUsing) {
                cout << "请选择：1.使用刀 2.使用手铐 3.使用电话 4.使用汽水 5.使用放大镜 6.使用药 7.结束道具使用并开枪" << endl;
                int u;
                cin >> u;

                if (u >= 1 && u <= 6) {
                    if (u == 1 && m1.dj[1] > 0) {
                        dj1(0);
                    } else if (u == 2 && m1.dj[2] > 0) {
                        dj2(0);
                    } else if (u == 3 && m1.dj[3] > 0) {
                        dj3(num, 0);
                    } else if (u == 4 && m1.dj[4] > 0) {
                        dj4(&num, 0);
                        if (num > zd + jd) {
                            cout << "已经没有子弹了，将重新生成！！！" << endl;
                            break;
                        }
                    } else if (u == 5 && m1.dj[5] > 0) {
                        dj5(num, 0);
                    } else if (u == 6 && m1.dj[6] > 0) {
                        dj6(0);
                    } else {
                        cout << "道具不足或无效选择！" << endl;
                    }
                    
                    // 显示更新后状态
                    system ("pause");
                    system ("cls");
                    cout << "你的回合！！！" << endl;
                    cout << name << "的血量:" << m1.xl << endl;
                    cout << "它的血量:" << m2.xl << endl;
                    cout << "当前是第" << num << "发子弹" << endl;
                    cout << name << "的道具:\n"
                         << "1." << m1.dj[1] << "个刀， 2." << m1.dj[2] << "个手铐， 3." << m1.dj[3] << "个电话， 4." << m1.dj[4] << "个汽水， 5."
                         << m1.dj[5] << "个放大镜， 6." << m1.dj[6] << "个药。" << endl;
                } else if (u == 7) {
                    continueUsing = false;
                } else {
                    cout << "输入错误！" << endl;
                }
            }
            
            system ("pause");
            system ("cls");
            cout << "请选择开枪对象：1.向自己开枪 2.向它开枪" << endl;
            cin >> aq;
            while (aq != 1 && aq != 2) {
                cout << "输入错误，请重新选择：1.向自己开枪 2.向它开枪" << endl;
                cin >> aq;
            }
        } else { // AI回合
            cout << "它的回合！！！" << endl;
            cout << name << "的血量:" << m1.xl << endl;
            cout << "它的血量:" << m2.xl << endl;
            cout << "当前是第" << num << "发子弹" << endl;
            cout << "它的道具:\n"
                 << m2.dj[1] << "个刀，" << m2.dj[2] << "个手铐，" << m2.dj[3] << "个电话，" << m2.dj[4] << "个汽水，" << m2.dj[5] << "个放大镜，"
                 << m2.dj[6] << "个药。" << endl;
            
            // AI可以使用多个道具
            int actions = 0;
            int maxActions = 2; // AI每回合最多使用2个道具
            
            while (actions < maxActions) {
                dl(&num);
                actions++;
                
                // 如果使用汽水导致子弹用完，则退出
                if (num > zd + jd) break;
            }
            
            // AI开枪决策
            aq = makeShootDecision(num);
            cout << "它选择向" << (aq == 1 ? "自己" : name) << "开枪" << endl;
        }
        
        system ("pause");
        system ("cls");
        cout << "第" << num << "发子弹是" << (zjd[num] == 0 ? "假" : "真") << "子弹！！！" << endl;
        system ("pause");
        system ("cls");
        
        int damage = sh * (zjd[num] == 1 ? 1 : 0);
        if (aq == 1) {
            m2.xl -= damage;
            if (damage > 0) {
                cout << "它对自身造成了" << damage << "点伤害！" << endl;
            } else {
                cout << "它对自己开枪但没有造成伤害！" << endl;
            }
        } else {
            m1.xl -= damage;
            if (damage > 0) {
                cout << "它对" << name << "造成了" << damage << "点伤害！" << endl;
            } else {
                cout << "它对" << name << "开枪但没有造成伤害！" << endl;
            }
        }

        num++;
        sh = 1; // 重置伤害倍率

        // 显示回合后状态
        cout << name << "的血量:" << m1.xl << endl;
        cout << "它的血量:" << m2.xl << endl;
        system ("pause");
        system ("cls");
    }

    if (m1.xl <= 0 && m2.xl <= 0) {
        cout << "双方同归于尽！" << endl;
    } else if (m1.xl <= 0) {
        cout << "它赢了！" << endl;
    } else {
        cout << name << "赢了！" << endl;
    }
    system ("pause");
}

void start () {
    while (1) {
        cout << "1.开始游戏" << endl;
        cout << "2.退出游戏" << endl;
        int choice;
        cin >> choice;
        system ("cls");

        if (choice == 1) {
            cout << "请输入血量(推荐3-8):";
            cin >> m1.xl;
            m2.xl = m1.xl;
            system ("cls");
            games ();
        } else {
            exit (0);
        }
    }
}

int main () {
    SetConsoleOutputCP (65001);
    cout << "你的名字:";
    cin >> name;
    cout << "你好," << name << "！准备迎接挑战吧！" << endl;
    system ("pause");
    system ("cls");
    start ();
    return 0;
}