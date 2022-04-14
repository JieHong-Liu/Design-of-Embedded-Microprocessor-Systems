//======================================================================
// Hello3 - A simple application for Windows CE
//
// Written for the book Programming Windows CE
// Copyright (C) 2007 Douglas Boling
//======================================================================
#include <windows.h>                 // For all that Windows stuff

LRESULT CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);

//======================================================================
// Program entry point
//
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPWSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc;
    HWND hWnd;
    MSG msg;

    // Register application main window class.
    wc.style = 0;                             // Window style
    wc.lpfnWndProc = MainWndProc;             // Callback function
    wc.cbClsExtra = 0;                        // Extra class data
    wc.cbWndExtra = 0;                        // Extra window data
    wc.hInstance = hInstance;                 // Owner handle
    wc.hIcon = NULL,                          // Application icon
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);// Default cursor
    wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
    wc.lpszMenuName =  NULL;                  // Menu name
    wc.lpszClassName = TEXT("MyClass");       // Window class name

    if (RegisterClass (&wc) == 0) return -1;

    // Create main window.
    hWnd = CreateWindowEx(WS_EX_NODRAG,       // Ex style flags
                          TEXT("MyClass"),    // Window class
                          TEXT("Hello"),      // Window title
                          // Style flags
                          WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
                          CW_USEDEFAULT,      // x position
                          CW_USEDEFAULT,      // y position
                          CW_USEDEFAULT,      // Initial width
                          CW_USEDEFAULT,      // Initial height
                          NULL,               // Parent
                          NULL,               // Menu, must be null
                          hInstance,          // Application instance
                          NULL);              // Pointer to create
                                              // parameters
    if (!IsWindow (hWnd)) return -2;  // Fail code if not created.

    // Standard show and update calls
    ShowWindow (hWnd, nCmdShow);
    UpdateWindow (hWnd);

    // Application message loop
    while (GetMessage (&msg, NULL, 0, 0)) {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }
    // Instance cleanup
    return msg.wParam;
}
//======================================================================
// MainWndProc - Callback function for application window
//
LRESULT CALLBACK MainWndProc (HWND hWnd, UINT wMsg, WPARAM wParam, 
                              LPARAM lParam) {
    PAINTSTRUCT ps;
    RECT rect;
    HDC hdc;

    switch (wMsg) {
    case WM_PAINT:
        // Get the size of the client rectangle
        GetClientRect (hWnd, &rect);

        hdc = BeginPaint (hWnd, &ps); 
        DrawText (hdc, TEXT ("M11007444"), -1, &rect, 
                  DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        EndPaint (hWnd, &ps); 
        return 0;

    case WM_DESTROY:
        PostQuitMessage (0);
        break;
    }
    return DefWindowProc (hWnd, wMsg, wParam, lParam);
} 
