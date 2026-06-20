#include <iostream>
#include <vector>
using namespace std;
string mb[10][13];

void lmb() {
    const string s = " ----- ", s2 = "|     |", s3 = "      |", s4 = "|      ", s5 = "       ";
    mb[0][0] = mb[0][12] = s, mb[0][1] = mb[0][2] = mb[0][3] = mb[0][4] = mb[0][5] = mb[0][7] = mb[0][8] = mb[0][9] = mb[0][10] = mb[0][11] = s2, mb[
        0][6] = s5;
    mb[1][0] = mb[1][12] = mb[1][6] = s5, mb[1][1] =
            mb[1][2] = mb[1][3] = mb[1][4] = mb[1][5] = mb[1][7] = mb[1][8] = mb[1][9] = mb[1][10] = mb[1][11] = s3;
    mb[2][0] = mb[2][6] = mb[2][12] = s, mb[2][1] = mb[2][2] = mb[2][3] = mb[2][4] = mb[2][5] = s3, mb[2][7] =
            mb[2][8] = mb[2][9] = mb[2][10] = mb[2][11] = s4;
    mb[3][0] = mb[3][6] = mb[3][12] = s, mb[3][1] =
            mb[3][2] = mb[3][3] = mb[3][4] = mb[3][5] = mb[3][7] = mb[3][8] = mb[3][9] = mb[3][10] = mb[3][11] = s3;
    mb[4][0] = mb[4][12] = s5, mb[4][1] = mb[4][2] = mb[4][3] = mb[4][4] = mb[4][5] = s2, mb[4][6] = s, mb[4][7] =
            mb[4][8] = mb[4][9] = mb[4][10] = mb[4][11] = s3;
    mb[5][0] = mb[5][6] = mb[5][12] = s, mb[5][1] = mb[5][2] = mb[5][3] = mb[5][4] = mb[5][5] = s4, mb[5][7] =
            mb[5][8] = mb[5][9] = mb[5][10] = mb[5][11] = s3;
    mb[6][0] = mb[6][6] = mb[6][12] = s, mb[6][1] = mb[6][2] = mb[6][3] = mb[6][4] = mb[6][5] = s4, mb[6][7] =
            mb[6][8] = mb[6][9] = mb[6][10] = mb[6][11] = s2;
    mb[7][0] = s, mb[7][6] = mb[7][12] = s5, mb[7][1] =
            mb[7][2] = mb[7][3] = mb[7][4] = mb[7][5] = mb[7][7] = mb[7][8] = mb[7][9] = mb[7][10] = mb[7][11] = s3;
    mb[8][0] = mb[8][6] = mb[8][12] = s, mb[8][1] =
            mb[8][2] = mb[8][3] = mb[8][4] = mb[8][5] = mb[8][7] = mb[8][8] = mb[8][9] = mb[8][10] = mb[8][11] = s2;
    mb[9][0] = mb[9][6] = mb[9][12] = s, mb[9][1] = mb[9][2] = mb[9][3] = mb[9][4] = mb[9][5] = s2, mb[9][7] =
            mb[9][8] = mb[9][9] = mb[9][10] = mb[9][11] = s3;
}

void sc(const string &ss) {
    vector<string> v(13, "");
    for (const char i: ss) {
        if (i == '-') {
            const string s = "      ";
            v[0] += s, v[1] += s, v[2] += s, v[3] += s, v[4] += s, v[5] += s, v[6] += "----- ", v[7] += s, v[8] += s, v[9] += s, v[10] += s, v[11] +=
                    s, v[12] += s;
        } else if (i == ':') {
            const string s = "      ";
            v[0] += s, v[1] += s, v[2] += s, v[3] += "  -   ", v[4] += s, v[5] += s, v[6] += s, v[7] += s, v[8] += s, v[9] += "  -   ", v[10] += s, v[
                11] += s, v[12] += s;
        } else {
            int num = i - '0';
            for (int j = 0; j < 13; j++) { v[j] += mb[num][j], v[j] += " "; }
        }
    }
    for (const string &i: v) { cout << i << '\n'; }
}

constexpr int bz = 1775139140; //2026-4-2-22-12-19
int main() {
    int num = time(0), y = 2026, mo = 4, d = 2, h = 22, m = 12, s = 20;
    s += (time(0) - bz);
    m += s / 60, s %= 60, h += m / 60, m %= 60, d += h / 24, h %= 24;
    //	lmb();
    string ss = "";
    while (1) {
        int qp = 180;
        while (qp) {
            if (time(0) != num) {
                //				system("cls");
                sc(ss);
                s++, qp--;
                // printf("%d-%d-%d-%d:%d:%d\n", y, mo, d, h, m, s);
                num = time(0);
                m += s / 60, s %= 60, h += m / 60, m %= 60, d += h / 24, h %= 24;
                ss += (char) (y / 1000 + '0')+((char)((y/100)%10)+'0')+((char)((y/10)%10));
            }
        }
        num = time(0), y = 2026, mo = 4, d = 2, h = 22, m = 12, s = 20;
        s += (time(0) - bz);
        m += s / 60, s %= 60, h += m / 60, m %= 60, d += h / 24, h %= 24;
    }
}
