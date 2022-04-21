//======================================================================
// PenTrac - Tracks stylus movement
//
// Written for the book Programming Windows CE
// Copyright (C) 2007 Douglas Boling
//======================================================================
#include <windows.h>                 // For all that Windows stuff
#include "pentrac.h"                 // Program-specific stuff

//----------------------------------------------------------------------
// Global data
//
const TCHAR szAppName[] = TEXT ("PenTrac");
HINSTANCE hInst;                     // Program instance handle

// Message dispatch table for MainWindowProc
const struct decodeUINT MainMessages[] = {
    WM_LBUTTONDOWN, DoMouseMain,
    WM_MOUSEMOVE, DoMouseMain,
    WM_CLOSE, DoDestroyMain,
};

// WM_CLOSE = first ask, then close
// WM_DESTROY = first close, then ask.

//======================================================================
// Program entry point
//
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPWSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    int rc = 0;
    HWND hwndMain;

    // Initialize this instance.
    hwndMain = InitInstance (hInstance, lpCmdLine, nCmdShow);
    if (hwndMain == 0)
        return 0x10;

    // Application message loop
    while (GetMessage (&msg, NULL, 0, 0)) {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }
    // Instance cleanup
    return TermInstance (hInstance, msg.wParam);
}
//----------------------------------------------------------------------
// InitApp - Application initialization
//
HWND InitInstance (HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc;
    HWND hWnd;

#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
// If Windows Mobile, allow only one instance of the application.
    hWnd = FindWindow (szAppName, NULL);
    if (hWnd) {
        SetForegroundWindow ((HWND)(((DWORD)hWnd) | 0x01));    
        return 0;
    }
#endif
    // Save program instance handle in global variable.
    hInst = hInstance;

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
    wc.lpszClassName = szAppName;             // Window class name

    if (RegisterClass (&wc) == 0) return 0;

    // Create main window.
    hWnd = CreateWindowEx (WS_EX_NODRAG, szAppName, TEXT ("LAB2_M11007444_M11007444"),
                         WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, // WINDOWS STYLE
                         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
                         CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    // Return fail code if window not created.
    if (!IsWindow (hWnd)) return 0;

    // Standard show and update calls
    ShowWindow (hWnd, nCmdShow);
    UpdateWindow (hWnd);
    return hWnd;
}
//----------------------------------------------------------------------
// TermInstance - Program cleanup
//
int TermInstance (HINSTANCE hInstance, int nDefRC) {
    return nDefRC;
}
//======================================================================
// Message handling procedures for MainWindow
//

//----------------------------------------------------------------------
// MainWndProc - Callback function for application window
//
LRESULT CALLBACK MainWndProc (HWND hWnd, UINT wMsg, WPARAM wParam,
                              LPARAM lParam) {
    INT i;
    //
    // Search message list to see if we need to handle this
    // message.  If in list, call procedure.
    //
    for (i = 0; i < dim(MainMessages); i++) {
        if (wMsg == MainMessages[i].Code)
            return (*MainMessages[i].Fxn)(hWnd, wMsg, wParam, lParam);
    }
    return DefWindowProc (hWnd, wMsg, wParam, lParam);
}
//----------------------------------------------------------------------
// DoMouseMain - Process WM_LBUTTONDOWN and WM_MOUSEMOVE messages
// for window.
//

int R_flag = 255;
int G_flag = 0;
int B_flag = 0;
int tmp_flag = 0;

LRESULT DoMouseMain (HWND hWnd, UINT wMsg, WPARAM wParam, 
                     LPARAM lParam) {
    POINT pt[64];
    POINT ptM;
    UINT i, uPoints = 0;
    HDC hdc;

    ptM.x = LOWORD (lParam);
    ptM.y = HIWORD (lParam);
    hdc = GetDC (hWnd);
    // If shift and mouse move, see if any lost points.

	if (wMsg == WM_MOUSEMOVE) {
        if (wParam & MK_SHIFT) 
		{
            GetMouseMovePoints (pt, 64, &uPoints);
			tmp_flag = R_flag;
			R_flag = G_flag;
			G_flag = B_flag;
			B_flag = tmp_flag;
			for (i = 0; i < uPoints; i++) 
			{
				pt[i].x /= 4;  // Convert move pts to screen coords
				pt[i].y /= 4;
				// Covert screen coordinates to window coordinates
				MapWindowPoints (HWND_DESKTOP, hWnd, &pt[i], 1);
				SetPixel (hdc, ptM.x, ptM.y, RGB (R_flag, G_flag, B_flag));
				SetPixel (hdc, ptM.x+1, ptM.y, RGB (R_flag, G_flag, B_flag));
				SetPixel (hdc, ptM.x, ptM.y+1, RGB (R_flag, G_flag, B_flag));
				SetPixel (hdc, ptM.x-1, ptM.y, RGB (R_flag, G_flag, B_flag));
				SetPixel (hdc, ptM.x, ptM.y-1, RGB (R_flag, G_flag, B_flag));
			}
		}
		else if (wParam& MK_CONTROL)
		{
			SetPixel (hdc, ptM.x, ptM.y, RGB (255, 255, 255));
			SetPixel (hdc, ptM.x+1, ptM.y,RGB (255, 255, 255));
			SetPixel (hdc, ptM.x, ptM.y+1, RGB (255, 255, 255));
			SetPixel (hdc, ptM.x-1, ptM.y, RGB (255, 255, 255));
			SetPixel (hdc, ptM.x, ptM.y-1, RGB (255,255,255));
			SetPixel (hdc, ptM.x+1, ptM.y+1, RGB (255, 255, 255));
			SetPixel (hdc, ptM.x+1, ptM.y-1, RGB (255, 255, 255));
			SetPixel (hdc, ptM.x-1, ptM.y+1, RGB (255, 255, 255));
			SetPixel (hdc, ptM.x-1, ptM.y-1, RGB (255, 255, 255));
		}
		else
		{
			SetPixel (hdc, ptM.x, ptM.y, RGB (0, 0, 255));
			SetPixel (hdc, ptM.x+1, ptM.y, RGB (0, 0, 255));
			SetPixel (hdc, ptM.x, ptM.y+1, RGB (0, 0, 255));
			SetPixel (hdc, ptM.x-1, ptM.y, RGB (0, 0, 255));
			SetPixel (hdc, ptM.x, ptM.y-1, RGB (0, 0, 255));
		}
    }
    // The original point is drawn last in case one of the points 
    // returned by GetMouseMovePoints overlaps it.  
   

    ReleaseDC (hWnd, hdc);

    // Kill time to make believe we are busy.
    Sleep(25);
    return 0;
}
//----------------------------------------------------------------------
// DoDestroyMain - Process WM_DESTROY message for window.
//
LRESULT DoDestroyMain (HWND hWnd, UINT wMsg, WPARAM wParam,
                       LPARAM lParam) {
	int mb = MessageBox (NULL,TEXT("FUCK"),TEXT("CLOSE????"),MB_YESNO);
	if(mb == IDNO)
	{
		return 0;
	}
	PostQuitMessage (0);
    return 0;
}

