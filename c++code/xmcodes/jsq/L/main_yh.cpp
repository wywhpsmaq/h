//
// Created by wywhpsmaq on 2026/1/20.
//

#include <bits/stdc++.h>
// #include <iostream>
// #include <vector>
// #include <string>
// #include <map>
// #include <algorithm>
#include "main_yh.h"
// #include "API.h"
// using namespace std;

int d_x, d_y;
/*
 * @d_x：x轴的大小
 * @d_y：y轴的大小
 */

namespace hs { //函数相关内容
    std::pair<fs, fs> point_kb(const point &p1, const point &p2) { //通过两点计算kb
        auto k = fs(p1.z_y - p2.z_y, p1.z_x - p2.z_x);
        return std::make_pair(k, fs(p1.z_y, 1) - k * fs(p1.z_x, 1));
    }

    line point_line(const std::string &name_, const point &p1, const point &p2, const std::string &color_) { //通过两点构造直线
        auto [k, b] = point_kb(p1, p2);
        return {name_, p1, p2, kb_jxs(k, b), color_};
    }

    double jxs_xy(const jxs &s, const double x) { return s.k.fz / s.k.fm * x + s.b.fz / s.b.fm; }

    void hz_hs(const line &l) {
        for (int i = 0; i <= 1600; i++) {
            auto [x, y] = hy(i - 800, jxs_xy(l.s, i - 800), d_x, d_y);
            hz(x, y, l.color);
        }
    }
}

namespace js { //其余计算内容
}

std::map<std::string, point> points;
std::map<std::string, line> lines;

int main() {
    // gz();
    d_x = 800, d_y = 400;
    while (true) {
        std::string s[10];
        /*
         * 本段内容目标：完成命令解析并调用相关函数
         * @s：命令0-9关键字
         */
        std::cin >> s[0];
        if (s[0] == "new"/*||s[0]=="n"*/) { //新建
            std::cin >> s[1];
            if (s[1] == "point"/*||s[1]=="p"*/) { //点
                std::string name, color;
                int x, y;
                std::cin >> name >> x >> y >> color;
                point o = point(name, x, y, color, d_x, d_y);
                points.insert({name, o});
                hz(o.x, o.y, color);
            } else if (s[1] == "line"/*||s[1]=="l"*/) { //线
                std::cin >> s[2];
                if (s[2] == "point"/*||s[2]=="p"*/) { //通过两点
                    std::string name, color, p_name1, p_name2;
                    std::cin >> name >> p_name1 >> p_name2 >> color;
                    line o = {hs::point_line(name, points.at(p_name1), points.at(p_name2), color)};
                    lines.insert({name, o});
                    hs::hz_hs(o);
                } else if (s[2] == "jxs"/*||s[2]=="j"*/) { //通过解析式
                    std::string name, color, jxs_str;
                    std::cin >> name >> jxs_str >> color;
                    jxs p = string_jxs(jxs_str);
                    fs x_d = p.b / p.k;
                    x_d = fs(-x_d.fz, x_d.fm);
                    point ddx = point("", x_d.fz / x_d.fm, 0, "", d_x, d_y);
                    point ddy = point("", 0, p.b.fz / p.b.fm, "", d_x, d_y);
                    line o = {name, ddx, ddy, p, color};
                    lines.insert({name, o});
                    hs::hz_hs(o);
                } else if (s[2] == "line" || s[2] == "l") { //通过与其他线的关系
                    std::cin >> s[3];
                    if (s[3] == "cz"/*||s[3]=="vertical"||s[3]=="c"||s[3]=="v"*/) { //垂直于其他线
                    } else if (s[3] == "px"/*||s[3]==""||s[3]=="p"*/) { //平行于其他线
                    }
                }
            }
        }
    }
}
