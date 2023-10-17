#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };

POINT moveDistance = { 0 };

POINT beforeStartPoint = { 0 };
POINT beforeEndPoint = { 0 };

POINT rStartPoint = { 0 };
POINT rEndPoint = { 0 };

RECT rect;
RECT rectSave;

HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성
HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 255, 255)); //흰색 브러시 생성

int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_GETMINMAXINFO: //창 크기 고정
	{
		MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
		lpMMI->ptMinTrackSize.x = 800;
		lpMMI->ptMinTrackSize.y = 600;
		lpMMI->ptMaxTrackSize.x = 800;
		lpMMI->ptMaxTrackSize.y = 600;
	}
	break;

	case WM_LBUTTONDOWN:
	{
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);

		beforeStartPoint.x = LOWORD(lParam);
		beforeStartPoint.y = LOWORD(lParam);

		isMouseLButtonPressed = 1;
	}
	break;

	case WM_LBUTTONUP:
	{
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);

		beforeEndPoint.x = LOWORD(lParam);
		beforeEndPoint.y = LOWORD(lParam);

		isMouseLButtonPressed = 0;

		// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;

	//강의에 안나왔지만 마우스가 움직일때의 이벤트를 뜻합니다.
	case WM_MOUSEMOVE:
	{
		// 마우스 이동 중
		if (isMouseLButtonPressed)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			InvalidateRect(hwnd, NULL, TRUE);
		}

		if (isMouseRButtonPressed)
		{
			rEndPoint.x = LOWORD(lParam);
			rEndPoint.y = HIWORD(lParam);

			moveDistance.x = rEndPoint.x - rStartPoint.x;
			moveDistance.y = rEndPoint.y - rStartPoint.y;

			startPoint.x = beforeStartPoint.x + moveDistance.x;
			startPoint.y = beforeStartPoint.y + moveDistance.y;
			endPoint.x = beforeEndPoint.x + moveDistance.x;
			endPoint.y = beforeEndPoint.y + moveDistance.y;

			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_RBUTTONDOWN:
		rStartPoint.x = LOWORD(lParam);
		rStartPoint.y = HIWORD(lParam);

		if (rStartPoint.y <= rect.bottom && rStartPoint.y >= rect.top && rStartPoint.x >= rect.left && rStartPoint.x <= rect.right) {
			isMouseRButtonPressed = 1;


		}
	

		break;

	case WM_RBUTTONUP:
		isMouseRButtonPressed = 0;
		break;

	case WM_PAINT:
	{
		HDC hdc = GetDC(hwnd);

		if (isMouseLButtonPressed || isMouseRButtonPressed)
		{
			FillRect(hdc, &rect, hBrush_eraser);
			rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y }; // 사각형 그리는데 시작지점과 끝점 (startPoint.x와 y, endPoint.x, y ) 기준으로 그리기

			//// 그리기
			FillRect(hdc, &rect, hBrush);
		}
		


		ReleaseDC(hwnd, hdc);

	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202207016 임완희"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//종료 메시지 보내기
	return (int)msg.wParam;

}