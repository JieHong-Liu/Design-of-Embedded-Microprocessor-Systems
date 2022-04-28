//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by Lab3.rc
//
//======================================================================
// Returns number of elements
#define dim(x) (sizeof(x) / sizeof(x[0]))

//----------------------------------------------------------------------
// Generic defines and data types
//
struct decodeUINT {                             // Structure associates
    UINT Code;                                  // messages
                                                // with a function.
    LRESULT (*Fxn)(HWND, UINT, WPARAM, LPARAM);
};
struct decodeCMD {                              // Structure associates
    UINT Code;                                  // menu IDs with a
    LRESULT (*Fxn)(HWND, WORD, HWND, WORD);     // function.
};

#define IDC_CMDBAR                      1
#define ID_RCVTEXT                      5
#define ID_SENDTEXT                     6
#define ID_SENDBTN                      7
#define IDR_MENU1                       101
#define IDD_DIALOG1                     103
#define IDI_ICON1                       104
#define IDC_COMBO1                      1001
#define IDC_COMBO2                      1002
#define IDC_COMBO3                      1003
#define IDC_COMBO4                      1004
#define IDC_COMBO5                      1005
#define IDC_COMBO6                      1006
#define ID_FILE_EXIT                    40001
#define ID_OPTION_OPEN                  40002
#define ID_OPTION_CLOSE                 40003
#define ID_OPTION_SETTING               40004
#define ID_EDIT_CLEAR40005              40005

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        105
#define _APS_NEXT_COMMAND_VALUE         40006
#define _APS_NEXT_CONTROL_VALUE         1002
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
//----------------------------------------------------------------------
// Function prototypes
//
HWND InitInstance (HINSTANCE, LPWSTR, int);
int TermInstance (HINSTANCE, int);

// Window procedures
LRESULT CALLBACK MainWndProc (HWND, UINT, WPARAM, LPARAM);
// Message handlers
LRESULT DoCreateMain (HWND, UINT, WPARAM, LPARAM);
LRESULT DoSizeMain (HWND, UINT, WPARAM, LPARAM);
LRESULT DoCommandMain (HWND, UINT, WPARAM, LPARAM);
LRESULT DoDestroyMain (HWND, UINT, WPARAM, LPARAM);
// Command functions
LPARAM DoMainCommandSetting (HWND, WORD, HWND, WORD);
LPARAM DoMainCommandClear (HWND, WORD, HWND, WORD);
LPARAM DoMainCommandExit (HWND, WORD, HWND, WORD);
LPARAM DoMainCommandSendText (HWND, WORD, HWND, WORD);
// Dialog box procedures
BOOL CALLBACK DialogBoxProc (HWND hWnd, UINT wMsg, WPARAM wParam,LPARAM lParam);