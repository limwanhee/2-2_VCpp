#include <windows.h>
#pragma once

void DrawRect(HDC hdc, int startX, int startY, int endX, int endY);

void DrawCircle(HDC hdc, int startX, int startY, int endX, int endY);

void DrawBonobono(HWND hWnd, HDC hdc);

void DrawCloseEyeBonobono(HWND hwnd, HDC hdc);

void DrawRyan(HDC hdc, int left, int top, int right, int bottom);

