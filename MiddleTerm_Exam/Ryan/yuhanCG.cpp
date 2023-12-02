#include <Windows.h>
#include "yuhanCG.h"

HBRUSH bonobonoSkin = CreateSolidBrush(RGB(127, 200, 255)); // 보노보노 피부 색깔 브러쉬 생성 (피부색)
HBRUSH ryanSkin = CreateSolidBrush(RGB(255, 200, 15)); //라이언 피부 색깔 브러쉬 생성
HBRUSH bonobonoMouth = CreateSolidBrush(RGB(255, 150, 255)); // 보노보노 입 색깔 브러쉬 생성 (입 색깔)
HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0)); // 보노보노, 라이언 검은색 부분 브러쉬 생성
HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255)); // 보노보노, 라이언 흰색 부분 브러쉬 생성



void DrawCircle(HDC hdc, int startX, int startY, int endX, int endY) {
    SelectObject(hdc, ryanSkin);
    Ellipse(hdc, startX, startY, endX, endY);
}

void DrawBonobono(HWND hwnd, HDC hdc) { //보노보노 그리는 함수
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

void DrawCloseEyeBonobono(HWND hwnd, HDC hdc) { //눈 찡그린 보노보노 그리는 변수
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

void DrawRyan(HDC hdc, int left, int top, int right, int bottom) { //라이언을 그리는 변수

    int ryanX = abs(left - right); //시작 지점과 끝 지점의 X좌표를 빼면 가로의 길이를 알 수 있음 abs 함수를 사용해 절대값으로 뺀 값이 음수이면 양수로 바꿈 
    int ryanY = abs(top - bottom); //시작 지점과 끝 지점의 Y좌표를 빼면 가로의 길이를 알 수 있음 abs 함수를 사용해 절대값으로 뺀 값이 음수이면 양수로 바꿈
    POINT ryanCenter = { left + ryanX / 2, top + ryanY / 2 }; //라이언의 그리게 할 기준과 비율이 될 중간 
    /*
    left = 내가 그리기 시작한 부분에서 부터 중간을 해야하기에 넣음 없으면 아마도 내가 원하지 않은 부분의 좌표 값이 들어감
    ryanX / 2 = 가로의 길이에서 2를 나누고 y도 똑같이 2를 나눠서 내가 드래그 한 크기에 맞게 정중앙을 구함
    */

    SelectObject(hdc, ryanSkin); //라이언 피부 색깔

    POINT startToCenter = { ryanCenter.x - left, ryanCenter.y - top };

    Ellipse(hdc, left, top + startToCenter.y * 0.2, ryanCenter.x - startToCenter.x * 0.3, ryanCenter.y); //왼쪽 귀
    Ellipse(hdc, ryanCenter.x + startToCenter.x * 0.3, top + startToCenter.y * 0.2, right, ryanCenter.y); //오른쪽 귀
    Ellipse(hdc, left, top + startToCenter.y * 0.3, right, bottom); //얼굴 크기는 위에만 줄임

    SelectObject(hdc, hBrushBlack); //검은색 브러쉬 
    Ellipse(hdc, left + startToCenter.x / 2, top + startToCenter.y / 0.9, ryanCenter.x - startToCenter.x / 3, ryanCenter.y - startToCenter.y / 30); //왼쪽 눈
    Ellipse(hdc, ryanCenter.x + startToCenter.x / 3, top + startToCenter.y / 0.9, right - startToCenter.x / 2, ryanCenter.y - startToCenter.y / 30); //오른쪽 눈

    SelectObject(hdc, hBrushWhite);//하얀색 브러쉬
    Ellipse(hdc, left + startToCenter.x / 1.3, ryanCenter.y + startToCenter.y / 4, ryanCenter.x, bottom - startToCenter.y / 2); //아마도 입? 왼쪽
    Ellipse(hdc, ryanCenter.x, ryanCenter.y + startToCenter.y / 4, right - startToCenter.x / 1.3, bottom - startToCenter.y / 2); //아마도 입? 오른쪽

    MoveToEx(hdc, left + startToCenter.x * 0.7, top + startToCenter.y * 0.9, NULL); //왼쪽 눈썹
    LineTo(hdc, ryanCenter.x - startToCenter.x * 0.6, top + startToCenter.y * 0.9);
    MoveToEx(hdc, left + startToCenter.x * 0.7, top + startToCenter.y * 0.88, NULL);
    LineTo(hdc, ryanCenter.x - startToCenter.x * 0.6, top + startToCenter.y * 0.88);
    MoveToEx(hdc, left + startToCenter.x * 0.7, top + startToCenter.y * 0.86, NULL);
    LineTo(hdc, ryanCenter.x - startToCenter.x * 0.6, top + startToCenter.y * 0.86);

    MoveToEx(hdc, ryanCenter.x + startToCenter.x * 0.6, top + startToCenter.y * 0.9, NULL); //오른쪽 눈썹
    LineTo(hdc, right - startToCenter.x * 0.7, top + startToCenter.y * 0.9);
    MoveToEx(hdc, ryanCenter.x + startToCenter.x * 0.6, top + startToCenter.y * 0.88, NULL);
    LineTo(hdc, right - startToCenter.x * 0.7, top + startToCenter.y * 0.88);
    MoveToEx(hdc, ryanCenter.x + startToCenter.x * 0.6, top + startToCenter.y * 0.86, NULL);
    LineTo(hdc, right - startToCenter.x * 0.7, top + startToCenter.y * 0.86);
}


