#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 }; //왼클릭 사각형 그릴때 쓸 변수
POINT endPoint = { 0 };  //왼클릭 사각형 그릴때 쓸 변수

POINT beforeStartPoint = { 0 }; //사각형 범위 저장하기 위한 변수
POINT beforeEndPoint = { 0 }; //사각형 범위 저장하기 위한 변수

POINT rStartPoint = { 0 }; //이동 거리와 우클릭 좌표를 구하기 위한 변수
POINT rEndPoint = { 0 }; //이동 거리와 우클릭 좌표를 구하기 위한 변수

POINT moveDistance = { 0 }; //이동 거리를 저장 할 변수

RECT boxRect; //box버튼 누르면 만들어지게 할 사각형

int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;
int spacebarPressed = 0;

HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200)); //배경색 브러쉬
HBRUSH BoxBrush = CreateSolidBrush(RGB(0, 0, 0));   //박스 브러쉬
HBRUSH DrawingBrush = CreateSolidBrush(RGB(255, 255, 255));   //드로잉 영역 브러쉬
HBRUSH hRectBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성

HBRUSH bonobonoSkin = CreateSolidBrush(RGB(127, 200, 255)); // 보노보노 피부 색깔 브러쉬 생성 (피부색)
HBRUSH bonobonoMouth = CreateSolidBrush(RGB(255, 150, 255)); // 보노보노 입 색깔 브러쉬 생성 (입 색깔)
HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0)); // 보노보노 눈, 코, 수염 브러쉬 생성 (검은색)
HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255)); // 보노보노 흰색 부분 브러쉬 생성 (흰색)

POINT mouseLocation = { 0 }; // 마우스 위치를 받을 변수

void DrawCloseEyeBonobono(HWND hwnd, HDC hdc) {

    SelectObject(hdc, bonobonoSkin); // 보노보노 피부색 

    Ellipse(hdc, 285, 110, 475, 295); // 보노보노 얼굴 파랑색 원 생성

    SelectObject(hdc, bonobonoMouth); // 보노보노 입 

    Ellipse(hdc, 365, 215, 395, 255);

    SelectObject(hdc, hBrushBlack); // 보노보노 검은색 
    
    MoveToEx(hdc, 310, 180, NULL); //보노보노 눈 왼쪽
    LineTo(hdc, 300, 170);
    MoveToEx(hdc, 310, 180, NULL);
    LineTo(hdc, 300, 190);

    MoveToEx(hdc, 450, 170, NULL); //보노보노 눈 오른쪽
    LineTo(hdc, 440, 180);
    MoveToEx(hdc, 450, 190, NULL);
    LineTo(hdc, 440, 180);

    SelectObject(hdc, hBrushWhite); // 보노보노 흰색 

    Ellipse(hdc, 350, 200, 380, 225); //입쪽 왼쪽 생성
    Ellipse(hdc, 380, 200, 410, 225); //입쪽 오른쪽 생성

    SelectObject(hdc, hBrushBlack); // 보노보노 검은색 
    Ellipse(hdc, 370, 195, 390, 215); // 코

    MoveToEx(hdc, 360, 210, NULL); //수염 왼쪽
    LineTo(hdc, 340, 190);
    MoveToEx(hdc, 360, 215, NULL);
    LineTo(hdc, 340, 230);

    MoveToEx(hdc, 410, 190, NULL); //수염 왼쪽
    LineTo(hdc, 395, 210);
    MoveToEx(hdc, 410, 230, NULL);
    LineTo(hdc, 395, 215);

    ReleaseDC(hwnd, hdc); // 디바이스 컨텍스트 해제

}

void DrawBonobono(HWND hwnd, HDC hdc) {

    SelectObject(hdc, bonobonoSkin); // 보노보노 피부색 

    Ellipse(hdc, 285, 110, 475, 295); // 보노보노 얼굴 파랑색 원 생성

    SelectObject(hdc, bonobonoMouth); // 보노보노 입 

    Ellipse(hdc, 365, 215, 395, 255);

    SelectObject(hdc, hBrushBlack); // 보노보노 검은색 

    Ellipse(hdc, 305, 190, 310, 200); // 눈 왼쪽 생성
    Ellipse(hdc, 450, 190, 455, 200); // 눈 오른쪽 생성

    SelectObject(hdc, hBrushWhite); // 보노보노 흰색 
    
    Ellipse(hdc, 305, 190, 310, 196); // 눈 왼쪽 흰자 생성
    Ellipse(hdc, 450, 190, 455, 196); // 눈 오른쪽 흰자 생성

    Ellipse(hdc, 350, 200, 380, 225); //입쪽 왼쪽 생성
    Ellipse(hdc, 380, 200, 410, 225); //입쪽 오른쪽 생성

    SelectObject(hdc, hBrushBlack); // 보노보노 검은색 

    Ellipse(hdc, 370, 195, 390, 215); // 코

    MoveToEx(hdc, 360, 210, NULL); //수염 왼쪽
    LineTo(hdc, 340, 190);
    MoveToEx(hdc, 360, 215, NULL);
    LineTo(hdc, 340, 230);

    MoveToEx(hdc, 410, 190, NULL); //수염 왼쪽
    LineTo(hdc, 395, 210);
    MoveToEx(hdc, 410, 230, NULL);
    LineTo(hdc, 395, 215);

    ReleaseDC(hwnd, hdc); // 디바이스 컨텍스트 해제

}

int isBoxButtonPressed = 0;     //박스 버튼 눌렀는지 확인 할 변수
int isCicleButtonPressed = 0;   // 원 버튼              ""
int isBonobonoButtonPressed = 0;// 보노보노 버튼        ""
int isRyanButtonPressed = 0;    // 라이언 버튼          ""
int isCubeButtonPressed = 0;    // 큐브 버튼            ""

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    RECT clientRect; //클라이언트 영역 기준으로 받을 사각형 변수
    RECT rect; //드로잉 영역의 사각형

    GetClientRect(hwnd, &clientRect); // 클라이언트 영역을 기준으로 사각형을 그립니다. (이거 하겠다고 2시간 ~ 3시간 썼어요 ㅠㅠㅠㅠㅠ)

    clientRect.left += 8; // padding, margin 8px씩 주기 
    clientRect.top += 8;
    clientRect.right -= 8;
    clientRect.bottom -= 8;

    rect.left = clientRect.left + 8; // Box 때문에 생긴 여백
    rect.top = clientRect.top + 88; // 버튼 + Box 때문에 생긴 여백
    rect.right = clientRect.right - 8;
    rect.bottom = clientRect.bottom - 8;

    switch (uMsg)
    {

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1:
            isBoxButtonPressed = 1; //박스 버튼 누름 표시
            isCicleButtonPressed = 0; //다른 버튼들은 false로 바꿈
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;
            InvalidateRect(hwnd, NULL, TRUE); //윈도우 핸들을 다시 그리게 하는 문장(드로잉 영역을 초기화 하기 위한 문장)
            break;

        case 2:
            isBoxButtonPressed = 0; //다른 버튼들은 false로 바꿈
            isCicleButtonPressed = 1;  //원 버튼을 누름 표시
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;
            InvalidateRect(hwnd, NULL, TRUE); //윈도우 핸들을 다시 그리게 하는 문장(드로잉 영역을 초기화 하기 위한 문장)
            break;

        case 3:
            isBonobonoButtonPressed = 1;
            DrawBonobono(hwnd, hdc);

            break;

        case 4:
            isBoxButtonPressed = 0;
            isCicleButtonPressed = 0; //다른 버튼들은 false로 바꿈
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 1; //라이언 버튼을 누름 표시
            isCubeButtonPressed = 0;
            InvalidateRect(hwnd, NULL, TRUE); //윈도우 핸들을 다시 그리게 하는 문장(드로잉 영역을 초기화 하기 위한 문장)
            break;

        case 5:
            isBoxButtonPressed = 0;
            isCicleButtonPressed = 0; //다른 버튼들은 false로 바꿈
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 1; //큐브 버튼을 누름 표시
            InvalidateRect(hwnd, NULL, TRUE); //윈도우 핸들을 다시 그리게 하는 문장(드로잉 영역을 초기화 하기 위한 문장)
            break;


        }
        break;


    case WM_GETMINMAXINFO: // 창 크기 고정
    {
        MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
        lpMMI->ptMinTrackSize.x = 800;
        lpMMI->ptMinTrackSize.y = 480;
        lpMMI->ptMaxTrackSize.x = 800;
        lpMMI->ptMaxTrackSize.y = 480;
        break;
    }

    case WM_KEYDOWN: //보노보노 버튼 안 누르고 스페이스바 누르면 그려지긴 합니다
    {
        if (wParam == VK_SPACE) { //스페이스바를 누르면
            DrawCloseEyeBonobono(hwnd, hdc);
        }
    }
    break;
    
    case WM_KEYUP:
    {
        if (wParam == VK_SPACE) { //스페이스바를 땠을 때
            DrawBonobono(hwnd, hdc);
        }
    }
    break;

    case WM_LBUTTONDOWN: //마우스 왼쪽버튼 눌렀을때
    {
        startPoint.x = LOWORD(lParam); //시작 지점
        startPoint.y = HIWORD(lParam);

        beforeStartPoint.x = LOWORD(lParam); //시작 지점 저장 (우클릭 시 사각형 이동 시키기 위해)
        beforeStartPoint.y = HIWORD(lParam);

        isMouseLButtonPressed = 1; //왼클릭 함 표시
        break;
    }

    case WM_LBUTTONUP:
    {
        endPoint.x = LOWORD(lParam); //끝 지점
        endPoint.y = HIWORD(lParam);

        beforeEndPoint.x = LOWORD(lParam); //끝 지점 저장 (용도는 위랑 동일)
        beforeEndPoint.y = HIWORD(lParam);

        isMouseLButtonPressed = 0; //왼클릭 땜 표시
        break;
    }

    case WM_MOUSEMOVE:
    {
        mouseLocation.x = LOWORD(lParam);// 마우스 좌표를 얻기
        mouseLocation.y = HIWORD(lParam);

        if (isMouseLButtonPressed) // 왼클릭 눌렀을 때
        {
            endPoint.x = LOWORD(lParam); // 끝 지점 계속 갱신
            endPoint.y = HIWORD(lParam);

            InvalidateRect(hwnd, NULL, TRUE);
        }

        if (isMouseRButtonPressed) //우클릭 눌렀을 때
        {
            rEndPoint.x = LOWORD(lParam); // 끝 지점 계속 갱신
            rEndPoint.y = HIWORD(lParam);

            moveDistance.x = rEndPoint.x - rStartPoint.x; //이동 거리 구하기 x, y좌표 둘다
            moveDistance.y = rEndPoint.y - rStartPoint.y;

            startPoint.x = beforeStartPoint.x + moveDistance.x; //기존 사각형 크기에 x, y좌표 시작과 끝을 더해서 움직이게 만들기
            startPoint.y = beforeStartPoint.y + moveDistance.y;
            endPoint.x = beforeEndPoint.x + moveDistance.x;
            endPoint.y = beforeEndPoint.y + moveDistance.y;

            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    }

    case WM_RBUTTONDOWN: // 마우스 우클릭 했을 때
    {
        rStartPoint.x = LOWORD(lParam);  // 우클릭 시작 지점 구하기
        rStartPoint.y = HIWORD(lParam);
        
        if (rStartPoint.y <= boxRect.bottom && rStartPoint.y >= boxRect.top && rStartPoint.x >= boxRect.left && rStartPoint.x <= boxRect.right) { // 마우스가 사각형 범위 안에 들어가 있으면 
            isMouseRButtonPressed = 1; // 우클릭 활성화

        } // 이 문장으로 인해 사각형 이동이 사각형 범위 안에 있을때만 가능
        break;
    }

    case WM_RBUTTONUP:// 마우스 우클릭을 땠을 때
        isMouseRButtonPressed = 0; // 우클릭 비활성화
        break;

    case WM_SETCURSOR:
    {
        if (mouseLocation.x >= rect.left && mouseLocation.x <= rect.right && mouseLocation.y >= rect.top && mouseLocation.y <= rect.bottom) { //마우스의 위치가 드로잉 영역 안일 때
            SetCursor(LoadCursor(NULL, IDC_CROSS)); //커서를 CROSS로 바꾼다
        }
        else { //마우스의 위치가 드로잉 영역 밖일 때
            SetCursor(LoadCursor(NULL, IDC_ARROW)); // 커서를 기본으로 바꾼다
        }
        break;
    }

    case WM_PAINT:
    {
        POINT finishStartPoint, finishEndPoint; // 사각형을 오른쪽 아래에서 시작했을 경우 좌표 값이 start 포인트 좌표가 end 좌표보다 더 크기에 비교를 위해 마지막 변수
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FrameRect(hdc, &clientRect, BoxBrush);  // View에 Box 그리기
        FrameRect(hdc, &rect, DrawingBrush); //드로잉 영역 그리기

        finishStartPoint.x = min(startPoint.x, endPoint.x); // 시작 지점과 끝 지점을 min, max 함수로 비교해서 변수에 저장 (사각형을 오른쪽 아래에서 부터 그릴때 위한 것)
        finishStartPoint.y = min(startPoint.y, endPoint.y);
        finishEndPoint.x = max(startPoint.x, endPoint.x);
        finishEndPoint.y = max(startPoint.y, endPoint.y);

        if ((isMouseLButtonPressed || isMouseRButtonPressed) && (startPoint.x >= rect.left && endPoint.x <= rect.right && startPoint.y >= rect.top && endPoint.y <= rect.bottom) && isBoxButtonPressed == 1) //사각형 그릴 때 마우스 왼쪽 또는 오른쪽 눌르고 드로잉 영역 안에 있고 박스 버튼을 눌렀으면 
        {
            FillRect(hdc, &boxRect, hBackgroundBrush);
            boxRect = { finishStartPoint.x, finishStartPoint.y, finishEndPoint.x, finishEndPoint.y };

            // 그리기
            FillRect(hdc, &boxRect, hRectBrush);
        }

        EndPaint(hwnd, &ps);
        break;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    ReleaseDC(hwnd, hdc);

    return S_OK;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

    HWND hwnd;
    HWND hButton1, hButton2, hButton3, hButton4, hButton5; // 버튼 정보 넣을 변수 1, 2, 3, 4, 5까지

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


    hwnd = CreateWindow(
        L"ButtonWindowClass", L"202207016 임완희", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 480, NULL, NULL, hInstance, NULL);

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        1 + 16, 1 + 16, 130 - 16, 80 - 16, hwnd, (HMENU)1, hInstance, NULL); //+16과 -16으로 margin 설정 80은 크기 조절과 위치 조절하다보니 저렇게 됐습니다 결과적으론 (64px 크기)

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        130 + 16, 1 + 16, 130 - 16, 80 - 16, hwnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        260 + 16, 1 + 16, 130 - 16, 80 - 16, hwnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        390 + 16, 1 + 16, 130 - 16, 80 - 16, hwnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        520 + 16, 1 + 16, 130 - 16, 80 - 16, hwnd, (HMENU)5, hInstance, NULL);

    if (!hwnd) {
        return FALSE;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}