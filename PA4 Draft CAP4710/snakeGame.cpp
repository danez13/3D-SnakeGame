// PA4 Draft CAP4710.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "snakeGame.h"
#include "openGLPart.h"
#include <sstream>

#define MAX_LOADSTRING 100
HBITMAP g_hbmBall = NULL;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PA4DRAFTCAP4710, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PA4DRAFTCAP4710));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PA4DRAFTCAP4710));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PA4DRAFTCAP4710);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//  
//       In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 830, 870, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   bunnyColor = DEFAULT_BUNNY_COLOR;
   bunnyCount = DEFAULT_NUMBER_OF_BUNNIES;
   bunnySize = DEFAULT_BUNNY_SIZE;

   snakeColor = DEFAULT_SNAKE_COLOR;
   snakeSpeed = DEFAULT_SPEED;
   snakeSize = DEFAULT_THICKNESS;

   return TRUE;
}

INT_PTR CALLBACK PickNumberOfBunnies(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int bc = DEFAULT_NUMBER_OF_BUNNIES;
    std::stringstream ss;
    {
        TCHAR buffer[MAX_PATH];
        switch (message)
        {
        case WM_COMMAND:
            int x = LOWORD(wParam);
            switch (x)
            {
            case IDOK:
                GetDlgItemText(hDlg, IDC_EDIT1, buffer, sizeof(buffer));
                try {
                    bunnyCount = stoi(buffer);
                    if (bunnyCount < 1 || bunnyCount>=50) {
                        break;
                    }
                }
                catch(...){
                    break;
                }
            case IDCANCEL:
                EndDialog(hDlg, wParam);
                return TRUE;
            }
        }
    }
    return (INT_PTR)FALSE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        g_hbmBall = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_FILE_NEWGAME:
                openGLMain();
                break;

            case ID_BUNNYCOLOR_RED:
                bunnyColor = SOLID_RED;
                break;
            case ID_BUNNYCOLOR_WHITE:
                bunnyColor = SOLID_WHITE;
                break;
            case ID_BUNNYCOLOR_GOLD:
                bunnyColor = SOLID_GOLD;
                break;
            case ID_BUNNYCOLOR_BROWN:
                bunnyColor = SOLID_BROWN;
                break;

            case ID_NUMBEROFAPPLES_5:
                bunnyCount = 5;
                break;
            case ID_NUMBEROFAPPLES_10:
                bunnyCount = 10;
                break;
            case ID_NUMBEROFAPPLES_20:
                bunnyCount = 20;
                break;
            case ID_NUMBEROFAPPLES_CUSTOM:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, PickNumberOfBunnies);
                break;

            case ID_APPLESIZE_SMALL:
                bunnySize = 0.05;
                break;
            case ID_APPLESIZE_MEDIUM:
                bunnySize = 0.1;
                break;
            case ID_APPLESIZE_LARGE:
                bunnySize = 0.2;
                break;

            case ID_SNAKECOLOR_SOLID:
                snakeColor = SOLID;
                break;
            case ID_SNAKECOLOR_CHECKERED:
                snakeColor = CHECKERED;
                break;
            case ID_SNAKECOLOR_HORIZONTALSTRIPPED:
                snakeColor = H_STRIPPED;
                break;
            case ID_SNAKECOLOR_VERTICALSTRIPPED:
                snakeColor = V_STRIPPED;
                break;

            case ID_SNAKESPEED_SLOW:
                snakeSpeed = 0.004;
                break;
            case ID_SNAKESPEED_MEDIUM: 
                snakeSpeed = 0.008;
                break;
            case ID_SNAKESPEED_FAST: 
                snakeSpeed = 0.016;
                break;

            case ID_SNAKESIZE_SMALL:
                snakeSize = 0.015;
                break;
            case ID_SNAKESIZE_MEDIUM:
                snakeSize = 0.03;
                break;
            case ID_SNAKESIZE_LARGE:
                snakeSize = 0.06;
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            BITMAP bm;
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, g_hbmBall);

            GetObject(g_hbmBall, sizeof(bm), &bm);

            BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem, hbmOld);
            DeleteDC(hdcMem);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
