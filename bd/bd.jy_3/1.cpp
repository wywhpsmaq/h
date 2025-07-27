#include <Windows.h>
#include <string>
#include <vector>
#include<iostream>

// 自定义消息框返回代码
#define ID_BUTTON1 100
#define ID_BUTTON2 101
#define ID_BUTTON3 102
#define ID_BUTTON4 103

// 自定义消息框过程
INT_PTR CALLBACK CustomMessageBoxProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    (void)lParam; // 消除未使用参数警告
    
    switch (uMsg) {
    case WM_INITDIALOG: {
        // 设置对话框标题
        SetWindowTextW(hDlg, L"kill极域2");
        
        // 创建按钮
        std::vector<std::pair<std::wstring, int>> buttons = {
            {L"爆破极域", ID_BUTTON1},
            {L"按钮2", ID_BUTTON2},
            {L"按钮3", ID_BUTTON3},
            {L"按钮4", ID_BUTTON4}
        };
        
        // 计算按钮位置
        int x = 20, y = 50;
        const int buttonWidth = 80, buttonHeight = 24;
        const int spacing = 10;
        
        for (const auto& btn : buttons) {
            CreateWindowW(
                L"BUTTON", btn.first.c_str(),
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                x, y, buttonWidth, buttonHeight,
                hDlg, reinterpret_cast<HMENU>(static_cast<INT_PTR>(btn.second)), 
                NULL, NULL
            );
            x += buttonWidth + spacing;
        }
        
        // 创建提示文本
        CreateWindowW(
            L"STATIC", L"请选择一个选项:",
            WS_VISIBLE | WS_CHILD,
            20, 20, 200, 20,
            hDlg, NULL, NULL, NULL
        );
        
        return TRUE;
    }
    
    case WM_COMMAND: {
        int id = LOWORD(wParam);
        if (id >= ID_BUTTON1 && id <= ID_BUTTON4) {
            EndDialog(hDlg, id);
            return TRUE;
        }
        break;
    }
    
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}

// 显示自定义消息框
int ShowCustomMessageBox(HINSTANCE hInstance) {
    // 创建简单的对话框模板
    DLGTEMPLATE dlgTemplate = {};
    dlgTemplate.style = DS_SETFONT | DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU;
    dlgTemplate.dwExtendedStyle = 0;
    dlgTemplate.cdit = 0; // 控件数量（我们将动态添加）
    dlgTemplate.x = 0;
    dlgTemplate.y = 0;
    dlgTemplate.cx = 300; // 对话框宽度
    dlgTemplate.cy = 150; // 对话框高度
    
    return DialogBoxIndirectParam(
        hInstance,
        &dlgTemplate,
        NULL,
        CustomMessageBoxProc,
        0
    );
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance; // 消除未使用参数警告
    (void)lpCmdLine;    // 消除未使用参数警告
    (void)nCmdShow;     // 消除未使用参数警告
    
    // 显示自定义消息框
    int result = ShowCustomMessageBox(hInstance);
    int n=0;
    // 处理用户选择
    std::wstring choice;
    if (result == 0) {
        choice = L"关闭对话框";
    } else {
        switch (result) {
        case ID_BUTTON1: n=1;choice = L"正在使用HME1爆破极域"; break;
        case ID_BUTTON2: n=2;choice = L"按钮2"; break;
        case ID_BUTTON3: n=3;choice = L"按钮3"; break;
        case ID_BUTTON4: n=4;choice = L"按钮4"; break;
        default: choice = L"未知选择(ID: " + std::to_wstring(result) + L")"; break;
        }
    }
    
    // 显示选择结果
    if(n==1){
        MessageBoxW(NULL, (L"" + choice).c_str(), L"通知", MB_OK);
    }
    //std::cout<<choice.c_str();
    
    return 0;
}