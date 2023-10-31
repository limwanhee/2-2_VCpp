#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

HBRUSH bonobonoSkin = CreateSolidBrush(RGB(127, 200, 255)); // ���뺸�� �Ǻ� ���� �귯�� ����
HBRUSH bonobonoMouth = CreateSolidBrush(RGB(255, 150, 255)); // ���뺸�� �� ���� �귯�� ����
HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0)); // ���뺸�� ��, ��, ���� �귯�� ����
HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255)); // ���뺸�� ��� �κ� �귯�� ����

void DrawBox(HWND hwnd, HDC hdc) {

    SelectObject(hdc, bonobonoSkin); // ���뺸�� �Ǻλ� 

    Ellipse(hdc, 285, 110, 475, 295); // ���뺸�� �� �Ķ��� �� ����


    SelectObject(hdc, hBrushBlack); // ���뺸�� ������ 

    Ellipse(hdc, 305, 190, 310, 200); // �� ���� ����
    Ellipse(hdc, 450, 190, 455, 200); // �� ������ ����
    Ellipse(hdc, 370, 195, 390, 215); // ��

    MoveToEx(hdc, 360, 210, NULL); //���� ����
    LineTo(hdc, 340, 190);
    MoveToEx(hdc, 360, 215, NULL);
    LineTo(hdc, 340, 230);

    MoveToEx(hdc, 410, 190, NULL); //���� ����
    LineTo(hdc, 395, 210);
    MoveToEx(hdc, 410, 230, NULL);
    LineTo(hdc, 395, 215);

    SelectObject(hdc, hBrushWhite); // ���뺸�� ��� 

    Ellipse(hdc, 305, 190, 310, 196); // �� ���� ���� ����
    Ellipse(hdc, 450, 193, 455, 198); // �� ������ ���� ����

    Ellipse(hdc, 350, 200, 380, 225); // ���� ����
    Ellipse(hdc, 380, 200, 410, 225); // ������ ����

    SelectObject(hdc, bonobonoMouth); // ���뺸�� �� 

    Ellipse(hdc, 367, 215, 397, 255);

    ReleaseDC(hwnd, hdc); // ����̽� ���ؽ�Ʈ ����

}

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_GETMINMAXINFO: // â ũ�� ����
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
        HDC hdc = GetDC(hwnd); // ����̽� ���ؽ�Ʈ ���
        
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