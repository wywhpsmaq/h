#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

#include "config.h"
#include "drawing_client.h"
#include <utility>
#include <string>
#include <memory>
#include <cmath>

class CoordinateSystem {
    int x_range;
    int y_range;
    std::shared_ptr<DrawingClient> client;

public:
    explicit CoordinateSystem(const int x_range_ = DEFAULT_X_RANGE, const int y_range_ = DEFAULT_Y_RANGE,
                              const std::shared_ptr<DrawingClient> &client_ = nullptr) : x_range(x_range_), y_range(y_range_), client(client_) {
        if (!client) { client = std::make_shared<DrawingClient>(); }
    }

    // 坐标转换：数学坐标 -> 画布坐标
    std::pair<int, int> mathToCanvas(const double math_x, const double math_y) const {
        int canvas_x = ORIGIN_X + static_cast<int>(math_x * (CANVAS_WIDTH / 2.0) / x_range);
        int canvas_y = ORIGIN_Y - static_cast<int>(math_y * (CANVAS_HEIGHT / 2.0) / y_range);
        return {canvas_x, canvas_y};
    }

    // 坐标转换：画布坐标 -> 数学坐标
    std::pair<double, double> canvasToMath(const int canvas_x, const int canvas_y) const {
        double math_x = (canvas_x - ORIGIN_X) * x_range / (CANVAS_WIDTH / 2.0);
        double math_y = (ORIGIN_Y - canvas_y) * y_range / (CANVAS_HEIGHT / 2.0);
        return {math_x, math_y};
    }

    // 检查坐标是否在画布内
    static bool isInCanvas(const int canvas_x, const int canvas_y) {
        return canvas_x >= 0 && canvas_x < CANVAS_WIDTH &&
               canvas_y >= 0 && canvas_y < CANVAS_HEIGHT;
    }

    // 绘制数学坐标系中的点
    void drawMathPoint(const double math_x, const double math_y, const std::string &color) const {
        if (auto [canvas_x, canvas_y] = mathToCanvas(math_x, math_y); isInCanvas(canvas_x, canvas_y)) { client->drawPoint(canvas_x, canvas_y, color); }
    }

    // 使用Bresenham算法绘制直线
    void drawLineBresenham(const double x1, const double y1, const double x2, const double y2, const std::string &color) const {
        auto [cx1, cy1] = mathToCanvas(x1, y1);
        auto [cx2, cy2] = mathToCanvas(x2, y2);

        const int dx = abs(cx2 - cx1),dy = abs(cy2 - cy1);
        const int sx = cx1 < cx2 ? 1 : -1,sy = cy1 < cy2 ? 1 : -1;
        int err = dx - dy;

        std::vector<std::tuple<int, int, std::string> > points;

        while (true) {
            if (isInCanvas(cx1, cy1)) { points.emplace_back(cx1, cy1, color); }

            if (cx1 == cx2 && cy1 == cy2) break;

            const int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                cx1 += sx;
            }
            if (e2 < dx) {
                err += dx;
                cy1 += sy;
            }
        }

        client->drawPoints(points);
    }

    // 绘制坐标系网格
    void drawGrid(const int step_x = 1, const int step_y = 1, const std::string &color = "#CCCCCC") const {
        std::vector<std::tuple<int, int, std::string> > points;

        // 垂直线
        for (double x = -x_range; x <= x_range; x += step_x) {
            for (double y = -y_range; y <= y_range; y += 0.1) {
                if (auto [cx, cy] = mathToCanvas(x, y); isInCanvas(cx, cy)) { points.emplace_back(cx, cy, color); }
            }
        }

        // 水平线
        for (double y = -y_range; y <= y_range; y += step_y) {
            for (double x = -x_range; x <= x_range; x += 0.1) {
                if (auto [cx, cy] = mathToCanvas(x, y); isInCanvas(cx, cy)) { points.emplace_back(cx, cy, color); }
            }
        }

        client->drawPoints(points);
    }

    // 绘制坐标轴
    void drawAxes(const std::string &color = Colors::BLACK) const {
        std::vector<std::tuple<int, int, std::string> > points;

        // X轴
        for (int x = 0; x < CANVAS_WIDTH; ++x) {
            if (auto [math_x, math_y] = canvasToMath(x, ORIGIN_Y); fabs(math_y) < 0.5) { // 在X轴附近
                points.emplace_back(x, ORIGIN_Y, color);
                points.emplace_back(x, ORIGIN_Y - 1, color);
                points.emplace_back(x, ORIGIN_Y + 1, color);
            }
        }

        // Y轴
        for (int y = 0; y < CANVAS_HEIGHT; ++y) {
            if (auto [math_x, math_y] = canvasToMath(ORIGIN_X, y); fabs(math_x) < 0.5) { // 在Y轴附近
                points.emplace_back(ORIGIN_X, y, color);
                points.emplace_back(ORIGIN_X - 1, y, color);
                points.emplace_back(ORIGIN_X + 1, y, color);
            }
        }

        // 坐标轴箭头
        for (int i = 0; i <= 5; ++i) {
            points.emplace_back(CANVAS_WIDTH - 1 - i, ORIGIN_Y - i, color); // X轴箭头
            points.emplace_back(CANVAS_WIDTH - 1 - i, ORIGIN_Y + i, color);
            points.emplace_back(ORIGIN_X - i, i, color); // Y轴箭头
            points.emplace_back(ORIGIN_X + i, i, color);
        }

        client->drawPoints(points);
    }

    // 设置坐标系范围
    void setRange(const int new_x_range, const int new_y_range) {
        x_range = new_x_range;
        y_range = new_y_range;
    }

    int getXRange() const { return x_range; }
    int getYRange() const { return y_range; }
};

#endif // COORDINATE_SYSTEM_H
