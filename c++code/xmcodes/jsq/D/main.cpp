#include <iostream>
#include <string>
#include <memory>
#include "config.h"
#include "geometry.h"
#include "coordinate_system.h"

class DrawingApplication {
    std::shared_ptr<CoordinateSystem> coord_system;
    GeometryManager geometry_manager;
    std::shared_ptr<DrawingClient> client;

    static void printHelp() {
        std::cout << "\n=== 绘图系统命令帮助 ===\n";
        std::cout << "1. 新建点: new point <名称> <x> <y> [颜色]\n";
        std::cout << "2. 通过两点新建线: new line point <线名> <点1> <点2> [颜色]\n";
        std::cout << "3. 通过方程新建线: new line equation <线名> <斜率k> <截距b> [颜色]\n";
        std::cout << "4. 绘制所有图形: draw all\n";
        std::cout << "5. 清空画布: clear\n";
        std::cout << "6. 显示网格: grid on/off\n";
        std::cout << "7. 设置坐标系范围: set range <x范围> <y范围>\n";
        std::cout << "8. 帮助: help\n";
        std::cout << "9. 退出: exit\n\n";
    }

    void processCommand(const std::string &command) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = command.find(' ');

        while (end != std::string::npos) {
            tokens.push_back(command.substr(start, end - start));
            start = end + 1;
            end = command.find(' ', start);
        }
        tokens.push_back(command.substr(start));

        if (tokens.empty()) return;

        try {
            if (tokens[0] == "new" && tokens.size() >= 2) {
                if (tokens[1] == "point" && tokens.size() >= 5) {
                    const std::string name = tokens[2];
                    const double x = std::stod(tokens[3]);
                    const double y = std::stod(tokens[4]);
                    const std::string color = tokens.size() >= 6 ? tokens[5] : Colors::BLACK;

                    const auto point = geometry_manager.addPoint(name, x, y, color);
                    point->draw();
                    std::cout << "点 " << name << " 创建成功\n";
                } else if (tokens[1] == "line" && tokens.size() >= 5) {
                    if (tokens[2] == "point" && tokens.size() >= 6) {
                        const std::string line_name = tokens[3];
                        const std::string p1_name = tokens[4];
                        const std::string p2_name = tokens[5];
                        const std::string color = tokens.size() >= 7 ? tokens[6] : Colors::BLUE;

                        const auto line = geometry_manager.addLineByPoints(line_name, p1_name, p2_name, color);
                        line->draw();
                        std::cout << "直线 " << line_name << " 创建成功: " << line->getEquation() << "\n";
                    } else if (tokens[2] == "equation" && tokens.size() >= 6) {
                        const std::string line_name = tokens[3];
                        const Fraction slope = Fraction::fromString(tokens[4]);
                        const Fraction intercept = Fraction::fromString(tokens[5]);
                        const std::string color = tokens.size() >= 7 ? tokens[7] : Colors::GREEN;

                        const auto line = geometry_manager.addLineByEquation(line_name, slope, intercept, color);
                        line->draw();
                        std::cout << "直线 " << line_name << " 创建成功: " << line->getEquation() << "\n";
                    }
                }
            } else if (tokens[0] == "draw" && tokens[1] == "all") {
                geometry_manager.drawAll();
                std::cout << "所有图形已绘制\n";
            } else if (tokens[0] == "clear") {
                client->clearCanvas("#FFFFFF");
                geometry_manager.clear();
                coord_system->drawAxes();
                std::cout << "画布已清空\n";
            } else if (tokens[0] == "grid" && tokens.size() >= 2) {
                if (tokens[1] == "on") {
                    coord_system->drawGrid();
                    std::cout << "网格已显示\n";
                } else if (tokens[1] == "off") {
                    // 清空并重绘坐标轴
                    client->clearCanvas("#FFFFFF");
                    coord_system->drawAxes();
                    geometry_manager.drawAll();
                    std::cout << "网格已隐藏\n";
                }
            } else if (tokens[0] == "set" && tokens[1] == "range" && tokens.size() >= 4) { const int x_range = std::stoi(tokens[2]);
                const int y_range = std::stoi(tokens[3]);
                coord_system->setRange(x_range, y_range);
                std::cout << "坐标系范围已设置为: x=" << x_range << ", y=" << y_range << "\n";
            } else if (tokens[0] == "help") { printHelp(); } else if (tokens[0] == "exit") {
                std::cout << "退出程序\n";
                exit(0);
            } else { std::cout << "未知命令，输入 'help' 查看帮助\n"; }
        } catch (const std::exception &e) { std::cerr << "错误: " << e.what() << "\n"; }
    }

public:
    DrawingApplication() {
        client = std::make_shared<DrawingClient>();
        coord_system = std::make_shared<CoordinateSystem>(DEFAULT_X_RANGE, DEFAULT_Y_RANGE, client);
        geometry_manager = GeometryManager(coord_system);

        // 初始化画布
        client->clearCanvas("#FFFFFF");
        coord_system->drawAxes();
    }

    [[noreturn]] void run() {
        std::cout << "=== 平面直角坐标系绘图系统 ===\n";
        std::cout << "输入 'help' 查看命令列表\n\n";

        while (true) {
            std::cout << "> ";
            std::string command;
            std::getline(std::cin, command);

            if (command.empty()) continue;
            processCommand(command);
        }
    }
};

int main() {
    try {
        DrawingApplication app;
        app.run();
    } catch (const std::exception &e) {
        std::cerr << "程序错误: " << e.what() << "\n";
        return 1;
    }
}
