#include <Windows.h>
#include "yuhanCG.h"

HBRUSH bonobonoSkin = CreateSolidBrush(RGB(127, 200, 255)); // ���뺸�� �Ǻ� ���� �귯�� ���� (�Ǻλ�)
HBRUSH ryanSkin = CreateSolidBrush(RGB(255, 200, 15)); //���̾� �Ǻ� ���� �귯�� ����
HBRUSH bonobonoMouth = CreateSolidBrush(RGB(255, 150, 255)); // ���뺸�� �� ���� �귯�� ���� (�� ����)
HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0)); // ���뺸��, ���̾� ������ �κ� �귯�� ����
HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255)); // ���뺸��, ���̾� ��� �κ� �귯�� ����



void DrawCircle(HDC hdc, int startX, int startY, int endX, int endY) {
    SelectObject(hdc, ryanSkin);
    Ellipse(hdc, startX, startY, endX, endY);
}

void DrawBonobono(HWND hwnd, HDC hdc) { //���뺸�� �׸��� �Լ�
    SelectObject(hdc, bonobonoSkin); // ���뺸�� �Ǻλ� 

    Ellipse(hdc, 285, 110, 475, 295); // ���뺸�� �� �Ķ��� �� ����

    SelectObject(hdc, bonobonoMouth); // ���뺸�� �� 

    Ellipse(hdc, 365, 215, 395, 255);

    SelectObject(hdc, hBrushBlack); // ���뺸�� ������ 

    Ellipse(hdc, 305, 190, 310, 200); // �� ���� ����
    Ellipse(hdc, 450, 190, 455, 200); // �� ������ ����

    SelectObject(hdc, hBrushWhite); // ���뺸�� ��� 

    Ellipse(hdc, 305, 190, 310, 196); // �� ���� ���� ����
    Ellipse(hdc, 450, 190, 455, 196); // �� ������ ���� ����

    Ellipse(hdc, 350, 200, 380, 225); //���� ���� ����
    Ellipse(hdc, 380, 200, 410, 225); //���� ������ ����

    SelectObject(hdc, hBrushBlack); // ���뺸�� ������ 

    Ellipse(hdc, 370, 195, 390, 215); // ��

    MoveToEx(hdc, 360, 210, NULL); //���� ����
    LineTo(hdc, 340, 190);
    MoveToEx(hdc, 360, 215, NULL);
    LineTo(hdc, 340, 230);

    MoveToEx(hdc, 410, 190, NULL); //���� ����
    LineTo(hdc, 395, 210);
    MoveToEx(hdc, 410, 230, NULL);
    LineTo(hdc, 395, 215);

    ReleaseDC(hwnd, hdc); // ����̽� ���ؽ�Ʈ ����
}

void DrawCloseEyeBonobono(HWND hwnd, HDC hdc) { //�� ���׸� ���뺸�� �׸��� ����
    SelectObject(hdc, bonobonoSkin); // ���뺸�� �Ǻλ� 

    Ellipse(hdc, 285, 110, 475, 295); // ���뺸�� �� �Ķ��� �� ����

    SelectObject(hdc, bonobonoMouth); // ���뺸�� �� 

    Ellipse(hdc, 365, 215, 395, 255);

    SelectObject(hdc, hBrushBlack); // ���뺸�� ������ 

    MoveToEx(hdc, 310, 180, NULL); //���뺸�� �� ����
    LineTo(hdc, 300, 170);
    MoveToEx(hdc, 310, 180, NULL);
    LineTo(hdc, 300, 190);

    MoveToEx(hdc, 450, 170, NULL); //���뺸�� �� ������
    LineTo(hdc, 440, 180);
    MoveToEx(hdc, 450, 190, NULL);
    LineTo(hdc, 440, 180);

    SelectObject(hdc, hBrushWhite); // ���뺸�� ��� 

    Ellipse(hdc, 350, 200, 380, 225); //���� ���� ����
    Ellipse(hdc, 380, 200, 410, 225); //���� ������ ����

    SelectObject(hdc, hBrushBlack); // ���뺸�� ������ 
    Ellipse(hdc, 370, 195, 390, 215); // ��

    MoveToEx(hdc, 360, 210, NULL); //���� ����
    LineTo(hdc, 340, 190);
    MoveToEx(hdc, 360, 215, NULL);
    LineTo(hdc, 340, 230);

    MoveToEx(hdc, 410, 190, NULL); //���� ����
    LineTo(hdc, 395, 210);
    MoveToEx(hdc, 410, 230, NULL);
    LineTo(hdc, 395, 215);

    ReleaseDC(hwnd, hdc); // ����̽� ���ؽ�Ʈ ����
}

void DrawRyan(HDC hdc, int left, int top, int right, int bottom) { //���̾��� �׸��� ����

    int ryanX = abs(left - right); //���� ������ �� ������ X��ǥ�� ���� ������ ���̸� �� �� ���� abs �Լ��� ����� ���밪���� �� ���� �����̸� ����� �ٲ� 
    int ryanY = abs(top - bottom); //���� ������ �� ������ Y��ǥ�� ���� ������ ���̸� �� �� ���� abs �Լ��� ����� ���밪���� �� ���� �����̸� ����� �ٲ�
    POINT ryanCenter = { left + ryanX / 2, top + ryanY / 2 }; //���̾��� �׸��� �� ���ذ� ������ �� �߰� 
    /*
    left = ���� �׸��� ������ �κп��� ���� �߰��� �ؾ��ϱ⿡ ���� ������ �Ƹ��� ���� ������ ���� �κ��� ��ǥ ���� ��
    ryanX / 2 = ������ ���̿��� 2�� ������ y�� �Ȱ��� 2�� ������ ���� �巡�� �� ũ�⿡ �°� ���߾��� ����
    */

    SelectObject(hdc, ryanSkin); //���̾� �Ǻ� ����

    POINT startToCenter = { ryanCenter.x - left, ryanCenter.y - top };

    Ellipse(hdc, left, top + startToCenter.y * 0.2, ryanCenter.x - startToCenter.x * 0.3, ryanCenter.y); //���� ��
    Ellipse(hdc, ryanCenter.x + startToCenter.x * 0.3, top + startToCenter.y * 0.2, right, ryanCenter.y); //������ ��
    Ellipse(hdc, left, top + startToCenter.y * 0.3, right, bottom); //�� ũ��� ������ ����

    SelectObject(hdc, hBrushBlack); //������ �귯�� 
    Ellipse(hdc, left + startToCenter.x / 2, top + startToCenter.y / 0.9, ryanCenter.x - startToCenter.x / 3, ryanCenter.y - startToCenter.y / 30); //���� ��
    Ellipse(hdc, ryanCenter.x + startToCenter.x / 3, top + startToCenter.y / 0.9, right - startToCenter.x / 2, ryanCenter.y - startToCenter.y / 30); //������ ��

    SelectObject(hdc, hBrushWhite);//�Ͼ�� �귯��
    Ellipse(hdc, left + startToCenter.x / 1.3, ryanCenter.y + startToCenter.y / 4, ryanCenter.x, bottom - startToCenter.y / 2); //�Ƹ��� ��? ����
    Ellipse(hdc, ryanCenter.x, ryanCenter.y + startToCenter.y / 4, right - startToCenter.x / 1.3, bottom - startToCenter.y / 2); //�Ƹ��� ��? ������

    MoveToEx(hdc, left + startToCenter.x * 0.7, top + startToCenter.y * 0.9, NULL); //���� ����
    LineTo(hdc, ryanCenter.x - startToCenter.x * 0.6, top + startToCenter.y * 0.9);
    MoveToEx(hdc, left + startToCenter.x * 0.7, top + startToCenter.y * 0.88, NULL);
    LineTo(hdc, ryanCenter.x - startToCenter.x * 0.6, top + startToCenter.y * 0.88);
    MoveToEx(hdc, left + startToCenter.x * 0.7, top + startToCenter.y * 0.86, NULL);
    LineTo(hdc, ryanCenter.x - startToCenter.x * 0.6, top + startToCenter.y * 0.86);

    MoveToEx(hdc, ryanCenter.x + startToCenter.x * 0.6, top + startToCenter.y * 0.9, NULL); //������ ����
    LineTo(hdc, right - startToCenter.x * 0.7, top + startToCenter.y * 0.9);
    MoveToEx(hdc, ryanCenter.x + startToCenter.x * 0.6, top + startToCenter.y * 0.88, NULL);
    LineTo(hdc, right - startToCenter.x * 0.7, top + startToCenter.y * 0.88);
    MoveToEx(hdc, ryanCenter.x + startToCenter.x * 0.6, top + startToCenter.y * 0.86, NULL);
    LineTo(hdc, right - startToCenter.x * 0.7, top + startToCenter.y * 0.86);
}


