//
// Created by wywhpsmaq on 2026/1/20.
//
#pragma once
#include <cmath>
#include <string>
#include <utility>
#include "API.h"
#ifndef H_MAIN_YH_H
#define H_MAIN_YH_H

class main_yh {};

#endif //H_MAIN_YH_H

inline bool jc(const int x, const int y) { return x >= 0 && y >= 0 && x <= 798 && y <= 1598; } //检查坐标是否在范围内
inline int gcd_(const int x, const int y) { return y == 0 ? x : gcd_(y, x % y); } //最大公约数
inline int lcm_(const int x, const int y) { return x * y / gcd_(x, y); } //最小公倍数
inline void hz(const int x, const int y, const std::string &color) { //将x行y列的点标成color颜色
    if (jc(x, y)) {
        APIClient client("127.0.0.1", 3002);
        client.setColor(x, y, color);
    }
}

inline std::pair<int, int> hy(const double x, const double y, const int d_x, const int d_y) { //通过坐标系坐标和大小还原画布坐标
    return std::make_pair(400 - y * (400.0 / d_y), 800 + x * (800.0 / d_x));
}

inline std::pair<double, double> fhy(const int x, const int y, const int d_x, const int d_y) { //通过画布坐标和大小还原坐标系坐标
    return std::make_pair((y - 400) / d_x, (400 - x) / d_y);
}

struct fs { //分数相关处理
    int fz, fm;
    /*
     * 本段内容目标：完成分数相关处理
     * @fz：分子
     * @fm:分母
     */
    fs(const int x, const int y) : fz(x), fm(y) {
        if (fz < 0 && fm < 0) fz = -fz, fm = -fm;
        if (fz > 0 && fm < 0) fz = -fz, fm = -fm;
        fz /= abs(gcd_(x, y));
        fm /= abs(gcd_(x, y));
    }
};

inline fs operator+(const fs &x, const fs &y) { //重载分数加法
    const int cnt = lcm_(x.fm, y.fm);
    const fs x_d = {x.fz * (cnt / x.fm), cnt}, y_d = {y.fz * (cnt / y.fm), cnt}; //通分
    return fs(x_d.fz + y_d.fz, cnt);
}

inline fs operator-(const fs &x, const fs &y) { //重载分数减法运算
    const int cnt = lcm_(x.fm, y.fm);
    const fs x_d = {x.fz * (cnt / x.fm), cnt}, y_d = {y.fz * (cnt / y.fm), cnt}; //通分
    return fs(x_d.fz - y_d.fz, cnt);
}

inline fs operator*(const fs &x, const fs &y) { //重载分数乘法运算
    return fs(x.fz * y.fz, x.fm * y.fm);
}

inline fs operator/(const fs &x, const fs &y) { //重载分数除法运算
    const auto cnt = fs(y.fm, y.fz);
    return x * cnt;
}

struct point {
    std::string name;
    int x, y;
    int z_x, z_y;
    std::string color;
    /*
     * 本段内容目标：完成点的储存
     * @name：名字
     * @x：点在画布中的纵坐标（第一个）
     * @y：点在画布中的横坐标（第二个）
     * @z_x：点在平面直角坐标系中的横坐标（第一个）
     * @z_y：点在平面直角坐标系中的纵坐标（的二个）
     * @color：点的颜色
     */
    point(std::string name_, const int a, const int b, std::string color_, const int d_x, const int d_y) : name(std::move(name_)),
        x(hy(a, b, d_x, d_y).first), y(hy(a, b, d_x, d_y).second), z_x(a), z_y(b), color(std::move(color_)) {}
};

struct jxs {
    std::string s;
    fs k, b;
    /*
     * 本段内容目标：完成解析式相关储存
     * @s：字符串版解析式
     * @k：解析式中的k
     * @b：解析式中的b
     */
    // jxs(const std::string &s_, const fs k_, const fs b_) : s(s_), k(k_), b(b_) {}
};

inline fs string_fs(const std::string &s) { //中字符串中提取分数
    int fz = 0, fm = 1;
    const bool f = s[0] != '-';
    int i = s[0] == '-' ? 1 : 0;
    for (; i < s.size(); i++) {
        if (s[i] == '/') break;
        fz *= 10;
        fz += s[i] - '0';
    }
    for (i++; i < s.size(); i++) {
        fm *= 10;
        fm += s[i] - '0';
    }
    fz = f ? fz : -fz;
    return fs(fz, fm);
}

inline std::string int_string(int x) {
    bool f = false;
    if (x < 0) f = true, x = -x;
    std::string s;
    while (x) {
        s = static_cast<char>(x % 10 + '0') + s;
        x /= 10;
    }
    return f ? "-" + s : s;
}

inline jxs string_jxs(std::string s) { //由字符串到解析式
    s.erase(0, 2);
    std::string s1 = "";
    int i = 0;
    for (; i < s.size(); i++) {
        if (s[i] == '/') break;
        s1 += s[i];
    }
    const fs k = string_fs(s1);
    s1.clear();
    for (i++; i < s.size(); i++) { s1 += s[i]; }
    const fs b = string_fs(s1);
    return {s, k, b};
}

inline jxs kb_jxs(const fs k, const fs b) { //从kb到字符串解析式
    std::string s;
    s += "y=" + int_string(k.fz) + "/" + int_string(k.fm) + "x" + int_string(b.fz) + "/" + int_string(b.fm);
    return {s, k, b};
}

struct line {
    std::string name;
    point d_x, d_y;
    jxs s;
    std::string color;
    /*
     * 本段内容目标：完成直线相关储存
     * @d_x：直线与x轴的交点
     * @d_y：直线与y轴的交点
     * @s：直线的解析式
     * @color：直线的颜色
     */
};

void gz() {
    for (int i = 0; i <= 1598; i++) {
        APIClient client("127.0.0.1", 3002);
        client.setColor(400, i, "#000000");
    }
    for (int i = 0; i <= 798; i++) {
        APIClient client("127.0.0.1", 3002);
        client.setColor(i, 800, "#000000");
    }
    APIClient client("127.0.0.1", 3002);
    client.setColor(1, 799, "#000000");
    APIClient client1("127.0.0.1", 3002);
    client1.setColor(2, 798, "#000000");
    APIClient client2("127.0.0.1", 3002);
    client2.setColor(3, 797, "#000000");
    APIClient client3("127.0.0.1", 3002);
    client3.setColor(4, 796, "#000000");
    APIClient client4("127.0.0.1", 3002);
    client4.setColor(5, 795, "#000000");
    APIClient client5("127.0.0.1", 3002);
    client5.setColor(1, 801, "#000000");
    APIClient client6("127.0.0.1", 3002);
    client6.setColor(2, 802, "#000000");
    APIClient client7("127.0.0.1", 3002);
    client7.setColor(3, 803, "#000000");
    APIClient client8("127.0.0.1", 3002);
    client8.setColor(4, 804, "#000000");
    APIClient client9("127.0.0.1", 3002);
    client9.setColor(5, 805, "#000000");

    APIClient client10("127.0.0.1", 3002);
    client10.setColor(399, 1597, "#000000");
    APIClient client11("127.0.0.1", 3002);
    client11.setColor(398, 1596, "#000000");
    APIClient client12("127.0.0.1", 3002);
    client12.setColor(397, 1595, "#000000");
    APIClient client13("127.0.0.1", 3002);
    client13.setColor(396, 1594, "#000000");
    APIClient client14("127.0.0.1", 3002);
    client14.setColor(395, 1593, "#000000");
    APIClient client15("127.0.0.1", 3002);
    client15.setColor(401, 1597, "#000000");
    APIClient client16("127.0.0.1", 3002);
    client16.setColor(402, 1596, "#000000");
    APIClient client17("127.0.0.1", 3002);
    client17.setColor(403, 1595, "#000000");
    APIClient client18("127.0.0.1", 3002);
    client18.setColor(404, 1594, "#000000");
    APIClient client19("127.0.0.1", 3002);
    client19.setColor(405, 1593, "#000000");
}
