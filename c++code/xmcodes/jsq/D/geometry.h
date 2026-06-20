#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "fraction.h"
#include "coordinate_system.h"
#include <string>
#include <memory>
#include <vector>

class Point {
    std::string name;
    double math_x;
    double math_y;
    std::string color;
    std::shared_ptr<CoordinateSystem> coord_system;

public:
    Point(const std::string &name_, const double x_, const double y_, const std::string &color_ = Colors::BLACK,
          const std::shared_ptr<CoordinateSystem> &cs = nullptr) : name(name_), math_x(x_), math_y(y_), color(color_), coord_system(cs) {
        if (!coord_system) { coord_system = std::make_shared<CoordinateSystem>(); }
    }

    void draw() const { coord_system->drawMathPoint(math_x, math_y, color); }

    std::string getName() const { return name; }
    double getX() const { return math_x; }
    double getY() const { return math_y; }
    std::string getColor() const { return color; }

    void setColor(const std::string &new_color) { color = new_color; }

    void setPosition(const double new_x, const double new_y) {
        math_x = new_x;
        math_y = new_y;
    }
};

class Line {
    std::string name;
    double x1, y1, x2, y2;
    std::string color;
    std::shared_ptr<CoordinateSystem> coord_system;
    Fraction slope; // 斜率k
    Fraction intercept; // 截距b

    void calculateSlopeIntercept() {
        if (fabs(x2 - x1) < 1e-10) { // 垂直线
            slope = Fraction(1, 0); // 无穷大
            intercept = Fraction(static_cast<int>(x1), 1);
        } else { const Fraction k_num(y2 - y1, 1);
            const Fraction k_den(x2 - x1, 1);
            slope = k_num / k_den;

            // b = y1 - k * x1
            const Fraction kx = slope * Fraction(x1, 1);
            intercept = Fraction(y1, 1) - kx;
        }
    }

public:
    Line(const std::string &name_, const double x1_, const double y1_, const double x2_, const double y2_,
         const std::string &color_ = Colors::BLACK,
         const std::shared_ptr<CoordinateSystem> &cs = nullptr) : name(name_), x1(x1_), y1(y1_), x2(x2_), y2(y2_), color(color_), coord_system(cs) {
        if (!coord_system) { coord_system = std::make_shared<CoordinateSystem>(); }
        calculateSlopeIntercept();
    }

    Line(const std::string &name_, const Point &p1, const Point &p2,
         const std::string &color_ = Colors::BLACK,
         const std::shared_ptr<CoordinateSystem> &cs = nullptr) : name(name_), x1(p1.getX()), y1(p1.getY()), x2(p2.getX()), y2(p2.getY()),
                                                           color(color_), coord_system(cs) {
        if (!coord_system) { coord_system = std::make_shared<CoordinateSystem>(); }
        calculateSlopeIntercept();
    }

    void draw() const { coord_system->drawLineBresenham(x1, y1, x2, y2, color); }

    // 获取直线上的点
    double getYatX(const double x) const {
        if (slope.getDenominator() == 0) { // 垂直线
            throw std::runtime_error("Vertical line has no y value for x");
        }
        return slope.toDouble() * x + intercept.toDouble();
    }

    // 获取直线与x轴交点
    double getXIntercept() const {
        if (slope.getDenominator() == 0) { // 垂直线
            return x1;
        }
        if (fabs(slope.toDouble()) < 1e-10) { // 水平线
            throw std::runtime_error("Horizontal line has no x intercept");
        }
        return -intercept.toDouble() / slope.toDouble();
    }

    // 获取直线与y轴交点
    double getYIntercept() const {
        if (slope.getDenominator() == 0) { // 垂直线
            throw std::runtime_error("Vertical line has no y intercept");
        }
        return intercept.toDouble();
    }

    std::string getName() const { return name; }
    Fraction getSlope() const { return slope; }
    Fraction getIntercept() const { return intercept; }
    std::string getColor() const { return color; }

    std::string getEquation() const {
        if (slope.getDenominator() == 0) { return "x = " + intercept.toString(); }
        std::string eq = "y = ";
        if (slope != Fraction(1, 1)) { eq += slope.toString() + "x"; } else { eq += "x"; }

        if (intercept.getNumerator() > 0) { eq += " + " + intercept.toString(); } else if (intercept.getNumerator() < 0) {
            eq += " - " + Fraction(-intercept.getNumerator(), intercept.getDenominator()).toString();
        }
        return eq;
    }
};

class GeometryManager {
    std::vector<std::shared_ptr<Point> > points;
    std::vector<std::shared_ptr<Line> > lines;
    std::shared_ptr<CoordinateSystem> coord_system;

public:
    explicit GeometryManager(const std::shared_ptr<CoordinateSystem> &cs = nullptr) : coord_system(cs) {
        if (!coord_system) { coord_system = std::make_shared<CoordinateSystem>(); }
    }

    std::shared_ptr<Point> addPoint(const std::string &name, double x, double y,
                                    const std::string &color = Colors::BLACK) {
        auto point = std::make_shared<Point>(name, x, y, color, coord_system);
        points.push_back(point);
        return point;
    }

    std::shared_ptr<Line> addLineByPoints(const std::string &name, const std::string &p1_name,
                                          const std::string &p2_name, const std::string &color = Colors::BLACK) {
        const auto p1 = findPoint(p1_name);
        const auto p2 = findPoint(p2_name);

        if (!p1 || !p2) { throw std::runtime_error("One or both points not found"); }

        auto line = std::make_shared<Line>(name, *p1, *p2, color, coord_system);
        lines.push_back(line);
        return line;
    }

    std::shared_ptr<Line> addLineByEquation(const std::string &name, const Fraction &slope,
                                            const Fraction &intercept, const std::string &color = Colors::BLACK) {
        // 计算直线上的两个点
        double x1 = -coord_system->getXRange();
        double y1 = slope.toDouble() * x1 + intercept.toDouble();
        double x2 = coord_system->getXRange();
        double y2 = slope.toDouble() * x2 + intercept.toDouble();

        auto line = std::make_shared<Line>(name, x1, y1, x2, y2, color, coord_system);
        lines.push_back(line);
        return line;
    }

    std::shared_ptr<Point> findPoint(const std::string &name) const {
        for (const auto &point: points) { if (point->getName() == name) { return point; } }
        return nullptr;
    }

    std::shared_ptr<Line> findLine(const std::string &name) const {
        for (const auto &line: lines) { if (line->getName() == name) { return line; } }
        return nullptr;
    }

    void drawAll() const {
        for (const auto &line: lines) { line->draw(); }
        for (const auto &point: points) { point->draw(); }
    }

    void clear() {
        points.clear();
        lines.clear();
    }
};

#endif // GEOMETRY_H
