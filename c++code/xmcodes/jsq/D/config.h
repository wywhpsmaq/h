#ifndef CONFIG_H
#define CONFIG_H

// 画布配置
constexpr int CANVAS_WIDTH = 1598;
constexpr int CANVAS_HEIGHT = 798;
constexpr int ORIGIN_X = 800; // 原点x坐标
constexpr int ORIGIN_Y = 400; // 原点y坐标

// 服务器配置
constexpr auto SERVER_HOST = "127.0.0.1";
constexpr int SERVER_PORT = 3002;

// 坐标系配置
constexpr int DEFAULT_X_RANGE = 80;
constexpr int DEFAULT_Y_RANGE = 40;

// 颜色常量
namespace Colors {
    constexpr auto BLACK = "#000000";
    constexpr auto RED = "#FF0000";
    constexpr auto GREEN = "#00FF00";
    constexpr auto BLUE = "#0000FF";
    constexpr auto YELLOW = "#FFFF00";
    constexpr auto CYAN = "#00FFFF";
    constexpr auto MAGENTA = "#FF00FF";
}

#endif // CONFIG_H
