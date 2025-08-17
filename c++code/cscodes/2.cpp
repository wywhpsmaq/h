#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
struct man {
	int xl;
	int dj[20];
};
int zd, jd;
int zjd[50];
int ain[50];
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
void dj2 (int num, int yy) {
	if (!yy) {
		cout << name << "使用了手铐" << endl;
		cout << "它被困住了！！！" << endl;
		m1.dj[2]--;
	} else {
		cout << "它使用了手铐" << endl;
		cout << name << "被困住了！！！" << endl;
		m2.dj[2]--;
	}
	xyg = !num;
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
		m2.dj[3]--;
	}
}
void dj4 (int& num, int yy) {
	if (!yy) {
		cout << name << "使用了汽水" << endl;
		cout << name << "退掉了一发子弹！！！" << endl;
		m1.dj[4]--;
	} else {
		cout << "它使用了汽水" << endl;
		cout << "它退掉了一发子弹！！！" << endl;
		m2.dj[4]--;
	}
	num++;
}
void dj5 (int num, int yy) {
	if (!yy) {
		cout << name << "使用了放大镜" << endl;
		cout << "这发子弹是" << (zjd[num] > 0 ? "真" : "假") << "的！！！" << endl;
		m1.dj[5]--;
	} else {
		cout << "它使用了放大镜" << endl;
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
void dl (int& num) {
	/*版本1
	vector<int> available;
	bool used = false;
	if (m2.xl <= 3 && m2.dj[6] > 0) {
		dj6 (1);
		used = true;
	}

	if (!used && sh == 1 && m2.dj[1] > 0) {
		dj1 (1);
		if (m2.dj[2] > 0) {
			dj2 (1, 1);
			used = true;
		}
	}
	if (!used && zd + jd - num < 4) {
		if (m2.dj[5] > 0) { dj5 (num, 1); }
		if (m2.dj[5] > 0) {
			dj5 (num, 1);
			if (ain[num] != -1 ? !ain[num] : !zjd[num]) {
				dj4 (&num, 1);
				used = true;
			}
		}
	}
	if (!used) {
		for (int i = 1; i <= 6; i++) {
			if (m2.dj[i] > 0) available.push_back (i);
		}
		if (!available.empty ()) {
			uniform_int_distribution<> dis (0, available.size () - 1);
			int choice = available[dis (gen)];
			switch (choice) {
			case 1:
				dj1 (1);
				break;
			case 2:
				dj2 (1, 1);
				break;
			case 3:
				dj3 (num, 1);
				break;
			case 4:
				dj4 (&num, 1);
				break;
			case 5:
				dj5 (num, 1);
				break;
			case 6:
				dj6 (1);
				break;
			}
		}
	}
	if (available.empty ()) {
		for (int i = 1; i <= 6; i++) {
			if (m2.dj[i] > 0) available.push_back (i);
		}
	}
	if (available.empty ()) {
		cout << "它没有可用的道具！" << endl;
		return;
	}
	uniform_int_distribution<> dis (0, available.size () - 1);
	int choice = available[dis (gen)];
	switch (choice) {
	case 1:
		dj1 (1);
		break;
	case 2:
		dj2 (1, 1);
		break;
	case 3:
		dj3 (1, 1);
		break;
	case 4:
		static int temp_num = 1;
		dj4 (&temp_num, 1);
		break;
	case 5:
		dj5 (temp_num, 1);
		break;
	case 6:
		dj6 (1);
		break;
	}
	*/
	//版本2
	if(ain[num]!=-1) return;
	if(m2.xl<=3&&m2.dj[6]>=1){

	}
}
void xdj () {//随机道具
	memset (m1.dj, 0, sizeof (m1.dj));
	memset (m2.dj, 0, sizeof (m2.dj));
	uniform_int_distribution<> djs (2, 10);
	int djs1 = djs (gen);
	for (int i = 0; i < djs1; i++) {
		uniform_int_distribution<> dj1 (1, 6);
		int type = dj1 (gen);
		m1.dj[type]++;
	}
	for (int i = 0; i < djs1; i++) {
		uniform_int_distribution<> dj1 (1, 6);
		int type = dj1 (gen);
		m2.dj[type]++;
	}
	cout << name << "的新道具:\n"
		 << m1.dj[1] << "个刀，" << m1.dj[2] << "个手铐，" << m1.dj[3] << "个电话，" << m1.dj[4] << "个汽水，" << m1.dj[5] << "个放大镜，" << m1.dj[6]
		 << "个药，" << endl;
	cout << "它的新道具:\n"
		 << m2.dj[1] << "个刀，" << m2.dj[2] << "个手铐，" << m2.dj[3] << "个电话，" << m2.dj[4] << "个汽水，" << m2.dj[5] << "个放大镜，" << m2.dj[6]
		 << "个药，" << endl;
}
void xzd () {//随机子弹
	memset (ain, -1, sizeof (ain));
	memset (zjd, -1, sizeof (zjd));
	uniform_int_distribution<> zds (1, 6);
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
void games () {//游戏
	int num = 1;
	sh = 1;
	aq = -1;
	xyg = false;
	xzd ();
	memset (m1.dj, 0, sizeof (m1.dj));
	memset (m2.dj, 0, sizeof (m2.dj));
	cout << "有" << zd << "发真子弹，" << jd << "发假子弹！！！" << endl;
	system ("pause");
	system ("cls");
	xdj ();
	system ("pause");
	cout << "开始！！！";
	system ("pause");
	system ("cls");
	while (m1.xl > 0 && m2.xl > 0) {
		bool zxy = xyg;
		if (num > zd + jd) {
			cout << "子弹用完了，重新生成子弹和道具！！！" << endl;
			num = 1;
			xzd ();
			xdj ();
			cout << "新的一轮有" << zd << "发真子弹，" << jd << "发假子弹！！！" << endl;
			system ("pause");
			system ("cls");
		}
		if (!xyg) {
			cout << "你的回合！！！" << endl;
			cout << name << "的血量:" << m1.xl << endl;
			cout << "它的血量:" << m2.xl << endl;
			cout << "当前是第" << num << "发子弹" << endl;
			cout << name << "的道具:\n"
				 << "1." << m1.dj[1] << "个刀， 2." << m1.dj[2] << "个手铐， 3." << m1.dj[3] << "个电话， 4." << m1.dj[4] << "个汽水， 5." << m1.dj[5]
				 << "个放大镜， 6." << m1.dj[6] << "个药。" << endl;
			cout << "请选择：" << "1.使用刀 2.使用手铐 3.使用电话 4.使用汽水 5.使用放大镜 6.使用药 7.直接开枪！！！" << endl;
			int u;
			while (cin >> u && u != 7) {
				if (u == 1) {
					if (m1.dj[1] > 0) {
						dj1 (0);
					} else {
						cout << "你没有刀了！！！" << endl;
					}
				} else if (u == 2) {
					if (m1.dj[2] > 0) {
						dj2 (0, 0);
					} else {
						cout << "你没有手铐了！！！" << endl;
					}
				} else if (u == 3) {
					if (m1.dj[3] > 0) {
						dj3 (num, 0);
					} else {
						cout << "你没有电话了！！！" << endl;
					}
				} else if (u == 4) {
					if (m1.dj[4] > 0) {
						dj4 (num, 0);
						if (num > zd + jd) {
							cout << "已经没有子弹了，将重新生成！！！" << endl;
							break;
						}
					} else {
						cout << "你没有汽水了！！！" << endl;
					}
				} else if (u == 5) {
					if (m1.dj[5] > 0) {
						dj5 (num, 0);
					} else {
						cout << "你没有放大镜了！！！" << endl;
					}
				} else if (u == 6) {
					if (m1.dj[6] > 0) {
						dj6 (0);
					} else {
						cout << "你没有药了！！！" << endl;
					}
				} else {
					cout << "输入错误！！！" << endl;
				}
				system ("pause");
				system ("cls");
				cout << "你的回合！！！" << endl;
				cout << name << "的血量:" << m1.xl << endl;
				cout << "m2的血量:" << m2.xl << endl;
				cout << "当前是第" << num << "发子弹" << endl;
				cout << name << "的道具:\n"
					 << "1." << m1.dj[1] << "个刀， 2." << m1.dj[2] << "个手铐， 3." << m1.dj[3] << "个电话， 4." << m1.dj[4] << "个汽水， 5."
					 << m1.dj[5] << "个放大镜， 6." << m1.dj[6] << "个药。" << endl;
				cout << "请选择：" << "1.使用刀 2.使用手铐 3.使用电话 4.使用汽水 5.使用放大镜 6.使用药 7.直接开枪！！！" << endl;
			}
			system ("pause");
			system ("cls");
			cout << "你的选择是：1.向" << name << "开枪 2.向它开枪\n";
			cin >> aq;
			while (aq != 1 && aq != 2) {
				cout << "输入错误，请重新选择：1.向" << name << "开枪 2.向它开枪\n";
				cin >> aq;
			}
			aq = (aq == 1) ? 2 : 1;
		} else {
			cout << "它的回合！！！" << endl;
			cout << name << "的血量:" << m1.xl << endl;
			cout << "m2的血量:" << m2.xl << endl;
			cout << "它的道具:\n"
				 << m2.dj[1] << "个刀，" << m2.dj[2] << "个手铐，" << m2.dj[3] << "个电话，" << m2.dj[4] << "个汽水，" << m2.dj[5] << "放大镜，"
				 << m2.dj[6] << "个药，" << endl;
			dl (num);
			int x=xz();
			cout << "它选择向" << (aq == 1 ? "m2" : name) << "开枪" << endl;//2-name,1-m2
		}
		system ("pause");
		system ("cls");
		cout << "这发是第" << num << "发子弹，是" << (zjd[num] == 0 ? "假" : "真") << "子弹！！！" << endl;
		system ("pause");
		system ("cls");
		int damage = sh * (zjd[num] == 1 ? 1 : 0);
		if (aq == 1) {
			m2.xl -= damage;
		} else {
			m1.xl -= damage;
		}
		num++;
		if (zxy == xyg) {
			xyg = (aq == 1) ? 1 : 0;
		} else {
			xyg = !xyg;
		}
		sh = 1;
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
void start () {//主界面
	while (1) {
		cout << "1.开始游戏" << endl;
		cout << "2.退出游戏" << endl;
		int choice;
		cin >> choice;
		system ("cls");
		if (choice == 1) {
			cout << "请输入血量:";
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
	cout << "你好," << name << endl;
	system ("pause");
	system ("cls");
	start ();
	return 0;
}