#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 }; //��Ŭ�� �簢�� �׸��� �� ����
POINT endPoint = { 0 };  //��Ŭ�� �簢�� �׸��� �� ����

POINT beforeStartPoint = { 0 }; //�簢�� ���� �����ϱ� ���� ����
POINT beforeEndPoint = { 0 }; //�簢�� ���� �����ϱ� ���� ����

POINT rStartPoint = { 0 }; //�̵� �Ÿ��� ��Ŭ�� ��ǥ�� ���ϱ� ���� ����
POINT rEndPoint = { 0 }; //�̵� �Ÿ��� ��Ŭ�� ��ǥ�� ���ϱ� ���� ����

POINT moveDistance = { 0 }; //�̵� �Ÿ��� ���� �� ����

RECT rect; //�簢�� ����

HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ũ �귯�� ����
HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 255, 255)); // ��� �귯�� ����

int isMouseLButtonPressed = 0; //��Ŭ�� �������� Ȯ�� ���� 1 : ����, 0 : ��
int isMouseRButtonPressed = 0; //��Ŭ�� �������� Ȯ�� ���� 1 : ����, 0 : ��

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_GETMINMAXINFO: // â ũ�� ����
    {
        MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
        lpMMI->ptMinTrackSize.x = 800;
        lpMMI->ptMinTrackSize.y = 600;
        lpMMI->ptMaxTrackSize.x = 800;
        lpMMI->ptMaxTrackSize.y = 600;
    }
    break;

    case WM_LBUTTONDOWN: //���콺 ���ʹ�ư ��������
    {
        startPoint.x = LOWORD(lParam); //���� ����
        startPoint.y = HIWORD(lParam);

        beforeStartPoint.x = LOWORD(lParam); //���� ���� ���� (��Ŭ�� �� �簢�� �̵� ��Ű�� ����)
        beforeStartPoint.y = HIWORD(lParam);

        isMouseLButtonPressed = 1; //��Ŭ�� �� ǥ��
    }
    break;

    case WM_LBUTTONUP:
    {
        endPoint.x = LOWORD(lParam); //�� ����
        endPoint.y = HIWORD(lParam);

        beforeEndPoint.x = LOWORD(lParam); //�� ���� ���� (�뵵�� ���� ����)
        beforeEndPoint.y = HIWORD(lParam);

        isMouseLButtonPressed = 0; //��Ŭ�� �� ǥ��

        // WM_PAINT �޽����� �����Ͽ� �簢���� ȭ�鿡 �׸��ϴ�.
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;

    // ���ǿ� �ȳ������� ���콺�� �����϶��� �̺�Ʈ�� ���մϴ�.
    case WM_MOUSEMOVE:
    {
        // ���콺 �̵� ��
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
    }
    break;

    case WM_RBUTTONDOWN: // ���콺 ��Ŭ�� ���� ��
        rStartPoint.x = LOWORD(lParam);  // ��Ŭ�� ���� ���� ���ϱ�
        rStartPoint.y = HIWORD(lParam);

        if (rStartPoint.y <= rect.bottom && rStartPoint.y >= rect.top && rStartPoint.x >= rect.left && rStartPoint.x <= rect.right) { // ���콺�� �簢�� ���� �ȿ� �� ������ 
            isMouseRButtonPressed = 1; // ��Ŭ�� Ȱ��ȭ
        } // �� �������� ���� �簢�� �̵��� �簢�� ���� �ȿ� �������� ����
        break;

    case WM_RBUTTONUP:// ���콺 ��Ŭ���� ���� ��
        isMouseRButtonPressed = 0; // ��Ŭ�� ��Ȱ��ȭ
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps); //BeginPaint �� EndPaint �Լ��� ����Ͽ� ������ ��ü�� �׸��� �ʰ� �ʿ��� �κи� �׷��� ������ ����

        if (isMouseLButtonPressed || isMouseRButtonPressed)
        {
            FillRect(hdc, &rect, hBrush_eraser); 
            rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y }; // �簢�� �׸��µ� ���������� ���� (startPoint.x�� y, endPoint.x, y ) �������� �׸���

            // �׸���
            FillRect(hdc, &rect, hBrush);
        }

        EndPaint(hwnd, &ps);
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
    /* ������ Ŭ���� ����.*/
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));    // ��� 0���� �ʱ�ȭ.

    // ������ Ŭ���� �� ����
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;

    // ������ Ŭ���� ���.
    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);    //����
    }

    // Window viewport ���� ����
    RECT rect = { 150, 100, 800, 600 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // ������ ����
    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202207016 �ӿ���"),
        WS_OVERLAPPEDWINDOW,
        0, 0,
        width, height,
        NULL, NULL,
        hInstance,
        NULL
    );

    // ���� �˻�.
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }

    // â ���̱�.
    ShowWindow(hwnd, SW_SHOW); // â ����
    UpdateWindow(hwnd); // ������Ʈ�ؾ� ����. �� ������ ���ٰ� ���� ��.

    // �޽��� ó�� ����.
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        // �޽��� ó��.
        if (GetMessage(&msg, hwnd, 0, 0))
        {
            // �޽��� �ؼ�����.
            TranslateMessage(&msg);
            // �޽����� ó���ؾ��� ���� ��������.
            DispatchMessage(&msg);
        }
    }

    // ���� �޽��� ������
    return (int)msg.wParam;
}
