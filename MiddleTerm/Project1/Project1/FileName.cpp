#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isKeyPressed = 0;

RECT rect = { 50 + 8, 50 + 8, 150 - 8, 150 - 8 }; // 왼쪽 상단 좌표 (50, 50)에서 오른쪽 하단 좌표 (150, 150)까지의 사각형

HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200));

bool isBoxVisible = false;

void DrawBox(HWND hWnd, HDC hdc) {
	RECT rect;
	GetClientRect(hWnd, &rect);

	if (isBoxVisible) {
		// 박스 그리기
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 박스
		SelectObject(hdc, hBrush);
		Rectangle(hdc, 300, 50, 500, 200);
		DeleteObject(hBrush);
	}
}

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hwnd);

	HBRUSH hBrush_user = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 0, 0));



	const wchar_t* text = L"Crash!!!";

	switch (uMsg)
	{
	case WM_GETMINMAXINFO: // 창 크기 고정
	{
		MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
		lpMMI->ptMinTrackSize.x = 800;
		lpMMI->ptMinTrackSize.y = 480;
		lpMMI->ptMaxTrackSize.x = 800;
		lpMMI->ptMaxTrackSize.y = 480;
	}
	break;

	case WM_PAINT: 
	{
		FillRect(hdc, &rect, hBackgroundBrush);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		DrawBox(hwnd, hdc);
		EndPaint(hwnd, &ps);
		break;
	}
	break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	DeleteObject(hBrush_user);
	DeleteObject(hBrush_eraser);
	ReleaseDC(hwnd, hdc);

	return S_OK;
}
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	HWND hWnd;
	HWND hButton1, hButton2, hButton3, hButton4, hButton5;

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = hBackgroundBrush;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"ButtonWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) {
		return 1;
	}

	hWnd = CreateWindow(
		L"ButtonWindowClass", L"Win32 Button Example", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd) {
		return FALSE;
	}

	hButton1 = CreateWindow(
		L"BUTTON", L"1 Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		160 + 16, 64, 160, 64, hWnd, (HMENU)1, hInstance, NULL); //plus 값 margin 설정
		
	hButton2 = CreateWindow(
		L"BUTTON", L"2 Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		320 + 16, 64, 160, 64, hWnd, (HMENU)2, hInstance, NULL);

	hButton3 = CreateWindow(
		L"BUTTON", L"3 Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		480 + 16, 64, 160, 64, hWnd, (HMENU)3, hInstance, NULL);

	hButton4 = CreateWindow(
		L"BUTTON", L"4 Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		640 + 16, 64, 160, 64, hWnd, (HMENU)4, hInstance, NULL);

	hButton5 = CreateWindow(
		L"BUTTON", L"5 Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		800 + 16, 64, 160, 64, hWnd, (HMENU)5, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}