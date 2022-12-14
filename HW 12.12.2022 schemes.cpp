#include <time.h>
#include <iostream>
#include <windows.h>
#include <windowsx.h>

using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Draw(HWND hwnd);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PWSTR lpCmdLine, int nCmdShow) {

    MSG  msg;
    WNDCLASSW wc = { 0 };

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"The Tree";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Pixels",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 1000, 800, NULL, NULL, hInstance, NULL);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    srand(time(NULL));

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    switch (msg) {

    case WM_PAINT:

        Draw(hwnd);
        break;

    case WM_DESTROY:

        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void Draw(HWND hwnd) {

    PAINTSTRUCT ps;
    RECT rect;

    GetClientRect(hwnd, &rect);

    if (rect.bottom == 0) {

        return;
    }

    HDC hdc = BeginPaint(hwnd, &ps);

    srand(time(NULL));

    int y_below = 750;
    int y_upside;
    int x_left = 50;
    int x_right = 100; 

    int g, b, r;
    for (int i = 0; i < 12; i++) {
        b = 0 + rand() % 255;
        g = 0 + rand() % 255;
        r = 0 + rand() % 255;
        y_upside = 100 + rand() % 500;

        HBRUSH brush = CreateSolidBrush(RGB(r, b, g));
        SelectBrush(hdc, brush);
        Rectangle(hdc, x_left, y_upside, x_right, y_below);
        x_left += 75;
        x_right += 75;
    }

    EndPaint(hwnd, &ps);
}

