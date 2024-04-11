#include <windows.h>

// Function to terminate explorer.exe
void terminateExplorer() {
    system("taskkill /f /im explorer.exe");
}

// Function to start explorer.exe
void startExplorer() {
    ShellExecute(NULL, L"open", L"explorer.exe", NULL, NULL, SW_SHOWNORMAL); // Start explorer.exe process
}

// Window procedure for the main window
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        // Create "Shutdown Explorer" button
        CreateWindowW(L"BUTTON", L"Shutdown Explorer", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 50, 200, 50, hwnd, (HMENU)1, NULL, NULL);

        // Create "Start Explorer" button
        CreateWindowW(L"BUTTON", L"Start Explorer", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 150, 200, 50, hwnd, (HMENU)2, NULL, NULL);
        break;
    case WM_COMMAND:
        // Handle button clicks
        switch (LOWORD(wParam)) {
        case 1: // Shutdown Explorer button clicked
            terminateExplorer();
            break;
        case 2: // Start Explorer button clicked
            startExplorer();
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Entry point of the program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register window class
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"WindowClass";
    RegisterClassW(&wc);

    // Create window
    HWND hwnd = CreateWindowW(L"WindowClass", L"Explorer Control", WS_OVERLAPPEDWINDOW,
        100, 100, 400, 300, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
