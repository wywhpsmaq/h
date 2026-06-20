#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    bool operator < (const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }

    bool operator == (const Point& p) const {
        return x == p.x && y == p.y;
    }
};

// 计算叉积
double cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 计算两点之间的距离
double distance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// 计算多边形的面积
double polygon_area(const vector<Point>& poly) {
    double area = 0.0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return fabs(area) / 2.0;
}

// 计算多边形的周长
double polygon_perimeter(const vector<Point>& poly) {
    double perimeter = 0.0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        perimeter += distance(poly[i], poly[j]);
    }
    return perimeter;
}

// 计算凸包（Andrew算法）
vector<Point> convex_hull(vector<Point> points) {
    int n = points.size();
    if (n <= 1) return points;

    sort(points.begin(), points.end());

    vector<Point> hull;
    hull.reserve(n + 1);

    // 下凸包
    for (int i = 0; i < n; hull.push_back(points[i++])) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
    }

    // 上凸包
    for (int i = n - 2, t = hull.size() + 1; i >= 0; hull.push_back(points[i--])) {
        while (hull.size() >= t && cross(hull[hull.size() - 2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
    }

    hull.pop_back();  // 去掉重复的起点
    return hull;
}

// 从凸包中选择m个点
vector<Point> select_points_from_hull(const vector<Point>& hull, int m) {
    int n = hull.size();
    if (n <= m) return hull;

    // 我们选择间隔均匀的点
    vector<Point> selected;
    selected.reserve(m);

    double step = (double)n / m;
    for (int i = 0; i < m; i++) {
        int idx = round(i * step);
        if (idx >= n) idx = n - 1;
        selected.push_back(hull[idx]);
    }

    return selected;
}

// 从字符串中解析点坐标
Point parse_point(const string& s) {
    stringstream ss(s);
    char c;
    double x, y;
    ss >> c >> x >> c >> y >> c;
    return Point(x, y);
}

int main() {
    // freopen("U515197-10.in", "r", stdin);
    // freopen("U515197-10.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<Point> points;
    points.reserve(n);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        points.push_back(parse_point(s));
    }

    // 计算凸包
    vector<Point> hull = convex_hull(points);

    // 选择m个点
    vector<Point> selected = select_points_from_hull(hull, m);

    // 计算面积和周长
    double area = polygon_area(selected);
    double perimeter = polygon_perimeter(selected);

    // 输出结果，保留6位小数
    cout << fixed << setprecision(6);
    cout << perimeter << " " << area << endl;

    return 0;
}
