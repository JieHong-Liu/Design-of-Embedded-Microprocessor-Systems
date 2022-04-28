//======================================================================
// HelloCE - A simple application for Windows CE
//
// Written for the book Programming Windows CE
// Copyright (C) 2007 Douglas Boling
//======================================================================
#include <windows.h>                 // For all that Windows stuff
#include <commctrl.h>
#include "resource.h"                 // Program-specific stuff

//----------------------------------------------------------------------
// Global data
//
const TCHAR szAppName[] = TEXT("HelloCE");
HINSTANCE hInst;                     // Program instance handle

// Message dispatch table for MainWindowProc
const struct decodeUINT MainMessages[] = {
    WM_CREATE, DoCreateMain,
	WM_SIZE, DoSizeMain,
	WM_COMMAND, DoCommandMain,
    WM_DESTROY, DoDestroyMain,
};
const struct decodeCMD MainCommandItems[] = {
    ID_OPTION_SETTING, DoMainCommandSetting,
	ID_SENDBTN, DoMainCommandSendText,
    ID_EDIT_CLEAR40005, DoMainCommandClear,
    ID_FILE_EXIT, DoMainCommandExit,
};

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
    if (hwndMain == 0) return 0x10;

    // Application message loop
    while (GetMessage (&msg, NULL, 0, 0)) {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }
    // Instance cleanup
    return TermInstance (hInstance, msg.wParam);
}
//----------------------------------------------------------------------
// InitInstance - Instance initialization
//
HWND InitInstance (HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc;
    HWND hWnd;

    // Save program instance handle in global variable.
    hInst = hInstance;

#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
    // If Windows Mobile, only allow one instance of the application
    hWnd = FindWindow (szAppName, NULL);
    if (hWnd) {
        SetForegroundWindow ((HWND)(((DWORD)hWnd) | 0x01));    
        return 0;
    }
#endif

    // Register application main window class.
    wc.style = 0;                             // Window style
    wc.lpfnWndProc = MainWndProc;             // Callback function
    wc.cbClsExtra = 0;                        // Extra class data
    wc.cbWndExtra = 0;                        // Extra window data
    wc.hInstance = hInstance;                 // Owner handle
    wc.hIcon = NULL,                          // Application icon
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);// Default cursor
    wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
    wc.lpszMenuName = NULL;                   // Menu name
    wc.lpszClassName = szAppName;             // Window class name

    if (RegisterClass (&wc) == 0) return 0;

    // Create main window.
    hWnd = CreateWindow (szAppName,           // Window class
                         TEXT("LAB3"),     // Window title
                         // Style flags
                         WS_VISIBLE,
                         CW_USEDEFAULT,       // x position
                         CW_USEDEFAULT,       // y position
                         CW_USEDEFAULT,       // Initial width
                         CW_USEDEFAULT,       // Initial height
                         NULL,                // Parent
                         NULL,                // Menu, must be null
                         hInstance,           // Application instance
                         NULL);               // Pointer to create
                                              // parameters
    if (!IsWindow (hWnd)) return 0;  // Fail code if not created.
	HICON hIcon;
	hIcon=(HICON)SendMessage(hWnd,WM_GETICON,FALSE,0);
	if (hIcon==0)
	{
	hIcon=(HICON)LoadImage(hInst,MAKEINTRESOURCE(IDI_ICON1),
	IMAGE_ICON,16,16,0);
	}
	SendMessage(hWnd,WM_SETICON,FALSE,(LPARAM)hIcon);
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
// Message handling procedures for main window
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
// DoCreateMain - Process WM_CREATE message for window.
//
LRESULT DoCreateMain (HWND hWnd, UINT wMsg, WPARAM wParam,
                      LPARAM lParam) {
    // Create a command bar. Add a menu and an exit button.
    HWND hwndCB, hC1, hC2, hC3;
	hwndCB = CommandBar_Create(hInst, hWnd, IDC_CMDBAR);
	CommandBar_InsertMenubar(hwndCB, hInst, IDR_MENU1, 0);
	//This function adds the Close button (X) to the commandbar
	CommandBar_AddAdornments (hwndCB, 0, 0);

	// Create child windows. They will be positioned in WM_SIZE.
    // Create receive text window.
    hC1 = CreateWindowEx (WS_EX_CLIENTEDGE, TEXT ("edit"),
                          TEXT (""), WS_VISIBLE | WS_CHILD |
                          WS_VSCROLL | ES_MULTILINE | ES_AUTOHSCROLL |
                          ES_READONLY, 0, 0, 10, 10, hWnd,
                          (HMENU)ID_RCVTEXT, hInst, NULL);
    // Create send text window.
    hC2 = CreateWindowEx (WS_EX_CLIENTEDGE, TEXT ("edit"),
                          TEXT (""), WS_VISIBLE | WS_CHILD,
                          0, 0, 10, 10,  hWnd, (HMENU)ID_SENDTEXT, 
                             hInst, NULL);
    // Create send text window.
    hC3 = CreateWindowEx (WS_EX_CLIENTEDGE, TEXT ("button"),
                          TEXT ("&Send"), WS_VISIBLE | WS_CHILD |
                          BS_DEFPUSHBUTTON, 0, 0, 10, 10,
                          hWnd, (HMENU)ID_SENDBTN, hInst, NULL);
    // Destroy frame if window not created.

    if (!IsWindow (hC1) || !IsWindow (hC2) || !IsWindow (hC3)) {
        DestroyWindow (hWnd);
        return 0;
    }
    return 0;
}
//----------------------------------------------------------------------
LRESULT DoCommandMain (HWND hWnd, UINT wMsg, WPARAM wParam,
                       LPARAM lParam) {
    WORD idItem, wNotifyCode;
    HWND hwndCtl;
    INT  i;

    // Parse the parameters.
    idItem = (WORD) LOWORD (wParam);
    wNotifyCode = (WORD) HIWORD (wParam);
    hwndCtl = (HWND) lParam;

    // Call routine to handle control message.
    for (i = 0; i < dim(MainCommandItems); i++) {
        if (idItem == MainCommandItems[i].Code)
            return (*MainCommandItems[i].Fxn)(hWnd, idItem, hwndCtl,
                        wNotifyCode);
    }
    return 0;
}
//----------------------------------------------------------------------
// DoSizeMain - Process WM_SIZE message for window.
//
LRESULT DoSizeMain (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam){
    RECT rect;

    // Adjust the size of the client rect to take into account
    // the command bar height.
    GetClientRect (hWnd, &rect);
    rect.top += CommandBar_Height (GetDlgItem (hWnd, IDC_CMDBAR));

    SetWindowPos (GetDlgItem (hWnd, ID_RCVTEXT), NULL, rect.left,
                  rect.top, (rect.right - rect.left),
                  rect.bottom - rect.top - 25, SWP_NOZORDER);
    SetWindowPos (GetDlgItem (hWnd, ID_SENDTEXT), NULL, rect.left,
                  rect.bottom - 25, (rect.right - rect.left) - 50,
                  25, SWP_NOZORDER);
    SetWindowPos (GetDlgItem (hWnd, ID_SENDBTN), NULL,
                  (rect.right - rect.left) - 50, rect.bottom - 25,
                  50, 25, SWP_NOZORDER);
    return 0;
}
//----------------------------------------------------------------------
// DoDestroyMain - Process WM_DESTROY message for window.
//
LRESULT DoDestroyMain (HWND hWnd, UINT wMsg, WPARAM wParam, 
                       LPARAM lParam) {
    PostQuitMessage (0);
    return 0;
}
//======================================================================
// Command handler routines
//----------------------------------------------------------------------
// DoMainCommandExit - Process Program Exit command.
//
LPARAM DoMainCommandExit (HWND hWnd, WORD idItem, HWND hwndCtl,
                          WORD wNotifyCode) {
    SendMessage (hWnd, WM_CLOSE, 0, 0);
    return 0;
}

LPARAM DoMainCommandSetting (HWND hWnd, WORD idItem, HWND hwndCtl,
                          WORD wNotifyCode) {
    DialogBox(hInst, (LPCTSTR)MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DialogBoxProc);
    return 0;
}
//----------------------------------------------------------------------
// DoMainCommandSendText - Process the Send text button.
//
LPARAM DoMainCommandSendText (HWND hWnd, WORD idItem, HWND hwndCtl,
                              WORD wNotifyCode) {
		HWND hwndSText; 
		WCHAR szText[256];
		hwndSText = GetDlgItem (hWnd, ID_SENDTEXT);
		GetWindowText (hwndSText, szText, dim(szText));
		StringCchCat (szText, dim(szText), TEXT ("\r\n")); 

		SendDlgItemMessage (hWnd, ID_RCVTEXT, EM_REPLACESEL, 0, (LPARAM)szText);
		
		SetWindowText (hwndSText, TEXT (""));
		return 0;
}
LPARAM DoMainCommandClear	(HWND hWnd, WORD idItem, HWND hwndCtl,
					 WORD wNotifyCode)	{
	// Clear receive text window.
	SendDlgItemMessage (hWnd, ID_RCVTEXT, WM_SETTEXT, 0,
                            (LPARAM)"");
	return 0;
}
BOOL CALLBACK DialogBoxProc (HWND hWnd, UINT wMsg, WPARAM wParam,
                                 LPARAM lParam) {
   switch (wMsg) {
        case WM_COMMAND:
            switch (LOWORD (wParam)) {
                case IDOK:
                case IDCANCEL:
                    EndDialog (hWnd, 0);
                    return TRUE;

				default:
				{
					TCHAR com1[] = TEXT("COM1");
					TCHAR com2[] = TEXT("COM2");

					TCHAR br1[] = TEXT("9600");
					TCHAR br2[] = TEXT("13200");

					TCHAR databit1[] = TEXT("8");
					TCHAR databit2[] = TEXT("16");

					TCHAR parity1[] = TEXT("ODD");
					TCHAR parity2[] = TEXT("EVEN");

					TCHAR stopbit1[] = TEXT("0");
					TCHAR stopbit2[] = TEXT("1");

					TCHAR fc1[] = TEXT("NONE");
					TCHAR fc2[] = TEXT("YES");

					SendDlgItemMessage(hWnd,IDC_COMBO1,CB_INSERTSTRING,-1,(LPARAM)com1);
				    SendDlgItemMessage(hWnd,IDC_COMBO1,CB_INSERTSTRING,-1,(LPARAM)com2);
				    SendDlgItemMessage(hWnd,IDC_COMBO2,CB_INSERTSTRING,-1,(LPARAM)br1);
				    SendDlgItemMessage(hWnd,IDC_COMBO2,CB_INSERTSTRING,-1,(LPARAM)br2);
				    SendDlgItemMessage(hWnd,IDC_COMBO3,CB_INSERTSTRING,-1,(LPARAM)databit1);
				    SendDlgItemMessage(hWnd,IDC_COMBO3,CB_INSERTSTRING,-1,(LPARAM)databit2);
				    SendDlgItemMessage(hWnd,IDC_COMBO4,CB_INSERTSTRING,-1,(LPARAM)parity1);
				    SendDlgItemMessage(hWnd,IDC_COMBO4,CB_INSERTSTRING,-1,(LPARAM)parity2);
				    SendDlgItemMessage(hWnd,IDC_COMBO5,CB_INSERTSTRING,-1,(LPARAM)stopbit1);
				    SendDlgItemMessage(hWnd,IDC_COMBO5,CB_INSERTSTRING,-1,(LPARAM)stopbit2);
				    SendDlgItemMessage(hWnd,IDC_COMBO6,CB_INSERTSTRING,-1,(LPARAM)fc1);
				    SendDlgItemMessage(hWnd,IDC_COMBO6,CB_INSERTSTRING,-1,(LPARAM)fc2);
   return 0;
				}
            }
        break;
    }
    return FALSE;
   
}
