#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

HBRUSH bonobonoSkin = CreateSolidBrush(RGB(127, 200, 255)); // 보노보노 피부 색깔 브러쉬 생성
HBRUSH bonobonoMouth = CreateSolidBrush(RGB(255, 150, 255)); // 보노보노 입 색깔 브러쉬 생성
HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0)); // 보노보노 눈, 코, 수염 브러쉬 생성
HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255)); // 보노보노 흰색 부분 브러쉬 생성

void DrawBox(HWND hwnd, HDC hdc) {

    SelectObject(hdc, bonobonoSkin); // 보노보노 피부색 

    Ellipse(hdc, 285, 110, 475, 295); // 보노보노 얼굴 파랑색 원 생성


    SelectObject(hdc, hBrushBlack); // 보노보노 검은색 

    Ellipse(hdc, 305, 190, 310, 200); // 눈 왼쪽 생성
    Ellipse(hdc, 450, 190, 455, 200); // 눈 오른쪽 생성
    Ellipse(hdc, 370, 195, 390, 215); // 코

    MoveToEx(hdc, 360, 210, NULL); //수염 왼쪽
    LineTo(hdc, 340, 190);
    MoveToEx(hdc, 360, 215, NULL);
    LineTo(hdc, 340, 230);

    MoveToEx(hdc, 410, 190, NULL); //수염 왼쪽
    LineTo(hdc, 395, 210);
    MoveToEx(hdc, 410, 230, NULL);
    LineTo(hdc, 395, 215);

    SelectObject(hdc, hBrushWhite); // 보노보노 흰색 

    Ellipse(hdc, 305, 190, 310, 196); // 눈 왼쪽 흰자 생성
    Ellipse(hdc, 450, 193, 455, 198); // 눈 오른쪽 흰자 생성

    Ellipse(hdc, 350, 200, 380, 225); // 왼쪽 생성
    Ellipse(hdc, 380, 200, 410, 225); // 오른쪽 생성

    SelectObject(hdc, bonobonoMouth); // 보노보노 입 

    Ellipse(hdc, 367, 215, 397, 255);

    ReleaseDC(hwnd, hdc); // 디바이스 컨텍스트 해제

}

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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
        HDC hdc = GetDC(hwnd); // 디바이스 컨텍스트 얻기
        
        DrawBox(hwnd, hdc);

    }

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
    ZeroMemory(&wc, sizeof(wc));    // 모두 0으로 초기화.

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
        exit(-1);    //예외
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
        {
            // 메시지 해석해줘.
            TranslateMessage(&msg);
            // 메시지를 처리해야할 곳에 전달해줘.
            DispatchMessage(&msg);
        }
    }

    // 종료 메시지 보내기
    return (int)msg.wParam;
}