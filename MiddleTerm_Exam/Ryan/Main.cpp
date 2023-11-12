#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>
#include "yuhanCG.h"

POINT startPoint = { 0 }; //��Ŭ�� �簢�� �׸��� �� ����
POINT endPoint = { 0 };  //��Ŭ�� �簢�� �׸��� �� ����

POINT beforeStartPoint = { 0 }; //�簢�� ���� �����ϱ� ���� ����
POINT beforeEndPoint = { 0 }; //�簢�� ���� �����ϱ� ���� ����

POINT rStartPoint = { 0 }; //�̵� �Ÿ��� ��Ŭ�� ��ǥ�� ���ϱ� ���� ����
POINT rEndPoint = { 0 }; //�̵� �Ÿ��� ��Ŭ�� ��ǥ�� ���ϱ� ���� ����

POINT moveDistance = { 0 }; //�̵� �Ÿ��� ���� �� ����

RECT boxRect; //box��ư ������ ��������� �� �簢��

int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;
int spacebarPressed = 0;

HBRUSH hBackgroundBrush = CreateSolidBrush(RGB(255, 240, 200)); //���� �귯��
HBRUSH BoxBrush = CreateSolidBrush(RGB(0, 0, 0));   //�ڽ� �귯��
HBRUSH DrawingBrush = CreateSolidBrush(RGB(255, 255, 255));   //����� ���� �귯��
HBRUSH hRectBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ũ �귯�� ����

POINT mouseLocation = { 0 }; // ���콺 ��ġ�� ���� ����

int isBoxButtonPressed = 0;     //�ڽ� ��ư �������� Ȯ�� �� ����
int isCicleButtonPressed = 0;   // �� ��ư              ""
int isBonobonoButtonPressed = 0;// ���뺸�� ��ư        ""
int isRyanButtonPressed = 0;    // ���̾� ��ư          ""
int isCubeButtonPressed = 0;    // ť�� ��ư            ""

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    RECT clientRect; //Ŭ���̾�Ʈ ���� �������� ���� �簢�� ����
    RECT rect; //����� ������ �簢��

    GetClientRect(hwnd, &clientRect); // Ŭ���̾�Ʈ ������ �������� �簢���� �׸��ϴ�. (�̰� �ϰڴٰ� 2�ð� ~ 3�ð� ���� �ФФФФ�)

    clientRect.left += 8; // padding, margin 8px�� �ֱ� 
    clientRect.top += 8;
    clientRect.right -= 8;
    clientRect.bottom -= 8;

    rect.left = clientRect.left + 8; // Box ������ ���� ����
    rect.top = clientRect.top + 88; // ��ư + Box ������ ���� ����
    rect.right = clientRect.right - 8;
    rect.bottom = clientRect.bottom - 8;

    switch (uMsg)
    {

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1:
            isBoxButtonPressed = 1; //�ڽ� ��ư ���� ǥ��
            isCicleButtonPressed = 0; //�ٸ� ��ư���� false�� �ٲ�
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;
            InvalidateRect(hwnd, NULL, TRUE); //������ �ڵ��� �ٽ� �׸��� �ϴ� ����(����� ������ �ʱ�ȭ �ϱ� ���� ����)
            break;

        case 2:
            isBoxButtonPressed = 0; //�ٸ� ��ư���� false�� �ٲ�
            isCicleButtonPressed = 1;  //�� ��ư�� ���� ǥ��
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;
            InvalidateRect(hwnd, NULL, TRUE); //������ �ڵ��� �ٽ� �׸��� �ϴ� ����(����� ������ �ʱ�ȭ �ϱ� ���� ����)
            break;

        case 3:
            isBoxButtonPressed = 0; //�ٸ� ��ư���� false�� �ٲ�
            isCicleButtonPressed = 0;
            isBonobonoButtonPressed = 1; //���뺸�� ��ư�� ���� ǥ��
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;
            SetFocus(hwnd); // ������ â�� ��Ŀ���� �ؼ� ��ư ������ �����̽��ٸ� ������ �� ��ư�� �����°� ����
            InvalidateRect(hwnd, NULL, TRUE); //������ �ڵ��� �ٽ� �׸��� �ϴ� ����(����� ������ �ʱ�ȭ �ϱ� ���� ����)
            break;

        case 4:
            isBoxButtonPressed = 0;
            isCicleButtonPressed = 0; //�ٸ� ��ư���� false�� �ٲ�
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 1; //���̾� ��ư�� ���� ǥ��
            isCubeButtonPressed = 0;
            InvalidateRect(hwnd, NULL, TRUE); //������ �ڵ��� �ٽ� �׸��� �ϴ� ����(����� ������ �ʱ�ȭ �ϱ� ���� ����)
            break;

        case 5:
            isBoxButtonPressed = 0;
            isCicleButtonPressed = 0; //�ٸ� ��ư���� false�� �ٲ�
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 1; //ť�� ��ư�� ���� ǥ��
            InvalidateRect(hwnd, NULL, TRUE); //������ �ڵ��� �ٽ� �׸��� �ϴ� ����(����� ������ �ʱ�ȭ �ϱ� ���� ����)
            break;


        }
        break;


    case WM_GETMINMAXINFO: // â ũ�� ����
    {
        MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
        lpMMI->ptMinTrackSize.x = 800;
        lpMMI->ptMinTrackSize.y = 480;
        lpMMI->ptMaxTrackSize.x = 800;
        lpMMI->ptMaxTrackSize.y = 480;
        break;
    }

    case WM_KEYDOWN: //Ű�� ������ ��
    {
        if (wParam == VK_SPACE && isBonobonoButtonPressed == 1) { //�����̽��ٸ� ������ ���뺸�� ��ư�� ���ȴٸ�
            DrawCloseEyeBonobono(hwnd, hdc); // ���׸� ���뺸�븦 �׷���
        }
    }
    break;

    case WM_KEYUP:
    {
        if (wParam == VK_SPACE && isBonobonoButtonPressed == 1) { //�����̽��ٸ� ���� ���뺸�� ��ư�� ���ȴٸ�
            DrawBonobono(hwnd, hdc); //�׳� ���뺸�븦 �׷���
        }
    }
    break;

    case WM_LBUTTONDOWN: //���콺 ���ʹ�ư ��������
    {
        startPoint.x = LOWORD(lParam); //���� ����
        startPoint.y = HIWORD(lParam);

        beforeStartPoint.x = LOWORD(lParam); //���� ���� ���� (��Ŭ�� �� �簢�� �̵� ��Ű�� ����)
        beforeStartPoint.y = HIWORD(lParam);

        isMouseLButtonPressed = 1; //��Ŭ�� �� ǥ��
        break;
    }

    case WM_LBUTTONUP: //���콺 ���ʹ�ư�� ������
    {
        endPoint.x = LOWORD(lParam); //�� ����
        endPoint.y = HIWORD(lParam);

        beforeEndPoint.x = LOWORD(lParam); //�� ���� ���� (�뵵�� ���� ����)
        beforeEndPoint.y = HIWORD(lParam);

        isMouseLButtonPressed = 0; //��Ŭ�� �� ǥ��
        break;
    }

    case WM_MOUSEMOVE: //���콺�� ������ ��
    {
        mouseLocation.x = LOWORD(lParam);// ���콺 ��ǥ�� ���
        mouseLocation.y = HIWORD(lParam);

        if (isMouseLButtonPressed) // ��Ŭ�� ������ ��
        {
            endPoint.x = LOWORD(lParam); // �� ���� ��� ����
            endPoint.y = HIWORD(lParam);

            InvalidateRect(hwnd, NULL, TRUE);
        }

        if (isMouseRButtonPressed) //��Ŭ�� ������ ��
        {
            rEndPoint.x = LOWORD(lParam); // �� ���� ��� ����
            rEndPoint.y = HIWORD(lParam);

            moveDistance.x = rEndPoint.x - rStartPoint.x; //�̵� �Ÿ� ���ϱ� x, y��ǥ �Ѵ�
            moveDistance.y = rEndPoint.y - rStartPoint.y;

            startPoint.x = beforeStartPoint.x + moveDistance.x; //���� �簢�� ũ�⿡ x, y��ǥ ���۰� ���� ���ؼ� �����̰� �����
            startPoint.y = beforeStartPoint.y + moveDistance.y;
            endPoint.x = beforeEndPoint.x + moveDistance.x;
            endPoint.y = beforeEndPoint.y + moveDistance.y;

            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    }

    case WM_RBUTTONDOWN: // ���콺 ��Ŭ�� ���� ��
    {
        rStartPoint.x = LOWORD(lParam);  // ��Ŭ�� ���� ���� ���ϱ�
        rStartPoint.y = HIWORD(lParam);

        if (rStartPoint.y <= boxRect.bottom && rStartPoint.y >= boxRect.top && rStartPoint.x >= boxRect.left && rStartPoint.x <= boxRect.right) { // ���콺�� �簢�� ���� �ȿ� �� ������ 
            isMouseRButtonPressed = 1; // ��Ŭ�� Ȱ��ȭ

        } // �� �������� ���� �簢�� �̵��� �簢�� ���� �ȿ� �������� ����
        break;
    }

    case WM_RBUTTONUP:// ���콺 ��Ŭ���� ���� ��
        isMouseRButtonPressed = 0; // ��Ŭ�� ��Ȱ��ȭ
        break;

    case WM_SETCURSOR:
    {
        if (mouseLocation.x >= rect.left && mouseLocation.x <= rect.right && mouseLocation.y >= rect.top && mouseLocation.y <= rect.bottom) { //���콺�� ��ġ�� ����� ���� ���� ��
            SetCursor(LoadCursor(NULL, IDC_CROSS)); //Ŀ���� CROSS�� �ٲ۴�
        }
        else { //���콺�� ��ġ�� ����� ���� ���� ��
            SetCursor(LoadCursor(NULL, IDC_ARROW)); // Ŀ���� �⺻���� �ٲ۴�
        }
        break;
    }

    case WM_PAINT:
    {
        POINT finishStartPoint, finishEndPoint; // �簢���� ������ �Ʒ����� �������� ��� ��ǥ ���� start ����Ʈ ��ǥ�� end ��ǥ���� �� ũ�⿡ �񱳸� ���� ������ ����
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        FrameRect(hdc, &clientRect, BoxBrush);  // View�� Box �׸���
        FrameRect(hdc, &rect, DrawingBrush); //����� ���� �׸���

        if ((isMouseLButtonPressed || isMouseRButtonPressed) && (startPoint.x >= rect.left && endPoint.x <= rect.right && startPoint.y >= rect.top && endPoint.y <= rect.bottom) && isBoxButtonPressed == 1) //�簢�� �׸� �� ���콺 ���� �Ǵ� ������ ������ ����� ���� �ȿ� �ְ� �ڽ� ��ư�� �������� 
        {
            finishStartPoint.x = min(startPoint.x, endPoint.x); // ���� ������ �� ������ min, max �Լ��� ���ؼ� ������ ���� (�簢���� ������ �Ʒ����� ���� �׸��� ���� ��)
            finishStartPoint.y = min(startPoint.y, endPoint.y);
            finishEndPoint.x = max(startPoint.x, endPoint.x); // ���� ������ �� ������ max �Լ��� ���ؼ� �� ū ���� ������ ����
            finishEndPoint.y = max(startPoint.y, endPoint.y);

            FillRect(hdc, &boxRect, hBackgroundBrush);
            boxRect = { finishStartPoint.x, finishStartPoint.y, finishEndPoint.x, finishEndPoint.y };

            // �׸���
            FillRect(hdc, &boxRect, hRectBrush);
        }

        if (isMouseLButtonPressed && (startPoint.x >= rect.left && endPoint.x <= rect.right && startPoint.y >= rect.top && endPoint.y <= rect.bottom) && isRyanButtonPressed) { //���̾��� �׸� �� ���콺 ������ ������ ����� ���� �ȿ� �ְ� �ڽ� ��ư�� ��������
            DrawRyan(hwnd, hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y); //���̾��� �׷���
        }

        if (isBonobonoButtonPressed == 1) { // ���뺸�� ��ư�� �����ٸ�
            DrawBonobono(hwnd, hdc); //���뺸�븦 �׷���
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
    HWND hButton1, hButton2, hButton3, hButton4, hButton5; // ��ư ���� ���� ���� 1, 2, 3, 4, 5����

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
        L"ButtonWindowClass", L"202207016 �ӿ���", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 480, NULL, NULL, hInstance, NULL);

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        1 + 16, 1 + 16, 130 - 16, 80 - 16, hwnd, (HMENU)1, hInstance, NULL); //+16�� -16���� margin ���� 80�� ũ�� ������ ��ġ �����ϴٺ��� ������ �ƽ��ϴ� ��������� (64px ũ��)

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