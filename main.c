#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <windows.h>
#include < time.h > 
#include <stdio.h>
#include "resource.h"
int M[11][21], F1[3][3], FP[4][4];
char str[100];
int pright();
int pleft();
int rotate();
int rotateP();
void Udal();
int otpravkaP();
int otpravka();
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);
void down();
void right();
void left();
void timer0();
void fig();
int g = 1, GlobalVar = 0,konec=0, GlobalC = 0, secunda1 = 0, secunda2 = 0, peredacha = 0, Vnast1 = 0, lin = 0, MatriX, TIME = 1000, MatriY, PatriX, PatriY, polog, Zapret = 0, KAL, linii = 0, vremia = 0, ochki = 0;
double Vnast = 0;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;

	// Создаем класс окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowsProc;
	wc.hInstance = hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = "MainMenu";
	wc.lpszClassName = "SimpleApplication";

	// Регистрируем класс окна.
	RegisterClass(&wc);

	// Создаем окно
	hWnd = CreateWindow("SimpleApplication", // Класс окна
		"Окно", // Заголовок
		WS_OVERLAPPED | WS_TABSTOP | WS_SYSMENU, // Стиль
		CW_USEDEFAULT, // Координата X верхнего угла
		CW_USEDEFAULT, // Координата Y верхнего угла
		550, // Ширина окна
		660, // Высота окна
		NULL, // Дескриптор родительского окна
		NULL, // Дескрипрот меню
		hInstance, // Дескриптор экземпляра окна
		NULL); // lParam

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, hWnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HFONT  newFont;
	RECT r;
	static HPEN hpenGrid;
	static HBRUSH hpenG0;
	static HBRUSH hpenG1;
	static char strFile[MAX_PATH];
	switch (uMsg)
	{
	case WM_CREATE:
		hpenGrid = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		hpenG0 = CreateSolidBrush(RGB(100, 100, 100));
		hpenG1 = CreateSolidBrush(RGB(255, 255, 255));
		int i, j, k = 0;
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &r);
		SelectObject(hdc, hpenGrid);
		Rectangle(hdc, 0, 0, r.right - 384, r.bottom);
		for (j = 0; j < 20; j++)
			for (i = 0; i < 10; i++)
			{
				if (M[i + 1][j + 1] == 0)
				{
					SelectObject(hdc, hpenG1);
					Rectangle(hdc, i * 30, j * 30, i * 30 + 30, j * 30 + 30);
				}
				if (M[i + 1][j + 1] != 0)
				{
					SelectObject(hdc, hpenG0);
					Rectangle(hdc, i * 30, j * 30, i * 30 + 30, j * 30 + 30);
				}
			}
		newFont = CreateFont(30, 20, 0, 0, 700, 0, 0, 0, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, ("Arial"));
		SelectObject(hdc, newFont);
		if (konec == 1)
		{
			TextOut(hdc, 90, 250, "ВЫ проиграли", 13);
			KillTimer(hWnd, 1);
		}
		TextOut(hdc, 350, 50, str, sprintf(str, "%d", linii));
		TextOut(hdc, 350, 10, "Линия", 6);
		TextOut(hdc, 350, 90, "Очки", 5);
		TextOut(hdc, 350, 130, str, sprintf(str, "%d", ochki));
		TextOut(hdc, 350, 170, "Время", 6);
		TextOut(hdc, 350, 210, str, sprintf(str, "%.2f сек", Vnast));
		
		return 0;
	case WM_TIMER:
	{
		if (konec != 1)
		{
		
		timer0();
		if (lin == linii)
		{
			KillTimer(hWnd, 1);
			SetTimer(hWnd, 1, TIME, NULL);
		}
		}
		GlobalVar++;
		down();
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			left();
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			return 0;;
		case VK_RIGHT:
			right();
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			return 0;
		case VK_UP:
			if (KAL == 1)
			{
				rotateP();
				otpravkaP();
			}
			else
			{
				rotate();
				otpravka();
			}

			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			return 0;
		case VK_DOWN:
			down();
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			return 0;
		}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_ABOUT:
			MessageBox(hWnd, "Тестовая программа.\n\nv1.0 2019", "О программе", MB_OK);
			break;
			break;
		case IDM_START:
			konec = 0;
			for (j = 0; j < 21; j++)
				for (i = 0; i < 11; i++)
					M[i][j] = 0;
			for (i = 0; i < 11; i++)
				M[i][21] = 9;
			SetTimer(hWnd, 1, TIME, NULL);
			secunda1 = GetCurrentTime();
			fig();
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			break;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void fig()
{
	int i, j;
	polog = 1;
	KAL = 0;
	if (GlobalC == 7)
		GlobalC = 0;
	for (j = 0; j < 3; j++)
		for (i = 0; i < 3; i++)
			F1[i][j] = 0;
	if (GlobalC == 6)
		for (j = 0; j < 4; j++)
			for (i = 0; i < 4; i++)
				FP[i][j] = 0;
	for(i=4;i<8;i++)
		for(j=1;j<4;j++)
			if (M[i][j] == 1)
			{
				konec = 1;
				break;
			}
	switch (GlobalC) {
	case 0:
	{
		MatriX = 5;
		MatriY = 1;
		F1[0][1] = 2;
		F1[1][1] = 2;
		F1[2][1] = 2;
		F1[2][0] = 2;

		otpravka();
		break;
	}
	case 1:
	{
		MatriX = 5;
		MatriY = 1;
		F1[0][1] = 2;
		F1[1][1] = 2;
		F1[2][1] = 2;
		F1[0][0] = 2;

		otpravka();
		break;
	}
	case 2:
	{
		MatriX = 5;
		MatriY = 1;
		F1[0][1] = 2;
		F1[1][1] = 2;
		F1[2][1] = 2;
		F1[1][0] = 2;
		otpravka();

		break;
	}
	case 3:
	{
		MatriX = 5;
		MatriY = 1;
		F1[0][0] = 2;
		F1[1][0] = 2;
		F1[1][1] = 2;
		F1[2][1] = 2;
		otpravka();

		break;
	}
	case 4:
	{
		MatriX = 5;
		MatriY = 1;
		F1[0][1] = 2;
		F1[1][1] = 2;
		F1[1][0] = 2;
		F1[2][0] = 2;
		otpravka();

		break;
	}
	case 5:
	{
		M[5][1] = 2;
		M[6][1] = 2;
		M[5][2] = 2;
		M[6][2] = 2;

		break;
	}
	case 6:
		PatriX = 4;
		PatriY = 0;
		FP[0][1] = 2;
		FP[1][1] = 2;
		FP[2][1] = 2;
		FP[3][1] = 2;
		KAL = 1;
		otpravkaP();
		break;

	}
	GlobalC++;

}

void down()
{
	int  j, i, o, p = 0;
	for (o = 0; o < 20; o++)
		for (p = 0; p < 10; p++)
		{
			if (M[10 - p][20 - o] == 2)
			{
				if (M[10 - p][21 - o] == 1 || M[10 - p][21 - o] == 9)
				{
					peredacha = 1;
					for (j = 0; j < 20; j++)
						for (i = 0; i < 10; i++)

							if (M[10 - i][20 - j] == 2)
								M[10 - i][20 - j] = 1;
					break;

				}

			}

		}
	if (MatriY != 20)
	{
		MatriY++;
	}
	if (PatriY != 20)
	{
		PatriY++;
	}
	for (j = 0; j < 20; j++)
		for (i = 0; i < 10; i++)
		{

			if (M[10 - i][20 - j] == 2)
			{

				M[10 - i][21 - j] = 2;
				M[10 - i][20 - j] = 0;
			}
		}
	if (peredacha == 1)
	{
		Udal();

		fig();
		peredacha = 0;
	}

}
void right()
{
	int i, j;

	if (pright() != 1)
	{
		if (MatriX != 8)
			MatriX++;
		if (PatriX != 7)
			PatriX++;
		for (i = 0; i < 10; i++)
			for (j = 0; j < 21; j++)
			{
				if (M[10 - i][j] == 0)
				{
					for (i = 1; i < 10; i++)
						for (j = 0; j < 21; j++)
						{
							if (M[10 - i][j] == 2)
							{
								if (M[11 - i][j] != 1)
									if (M[11 - i][j] != 2)
									{

										M[11 - i][j] = M[10 - i][j];
										M[10 - i][j] = 0;
									}

							}
						}
				}
			}
	}
}
int pright()
{
	int i, j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 21; j++)
		{
			if (i == 0)
				if (M[10 - i][j] == 2)
					return 1;
			if (M[10 - i][j] == 2 && M[11 - i][j] == 1)
				return 1;
		}
	return 0;
}
void left()
{
	int i, j;
	if (pleft() != 1)
	{
		if (MatriX != 1)
			MatriX--;
		if (PatriX != 1)
			PatriX--;
		for (i = 0; i < 10; i++)
			for (j = 0; j < 20; j++)
			{

				if (M[i - 1][20 - j] == 0)
				{
					for (i = 1; i < 11; i++)
						for (j = 0; j < 20; j++)
						{
							if (M[i][20 - j] == 2)
								if (M[i - 1][20 - j] != 2)
								{

									M[i - 1][20 - j] = M[i][20 - j];
									M[i][20 - j] = 0;
								}
						}
				}
			}
	}
}
int pleft()
{
	int i, j;
	for (i = 1; i < 10; i++)
		for (j = 0; j < 20; j++)
		{
			if (i == 1)
				if (M[i][j] == 2)
					return 1;
			if (M[i][j] == 2 && M[i - 1][j] == 1)
				return 1;
		}
	return 0;
}
int rotate()
{
	if (polog == 5)
		polog = 1;
	int i, j, F2[3][3];
	switch (polog) {
	case 1: {
		for (i = 1; i < 3; i++)
		{
			if (M[MatriX + i][MatriY + 2] == 1)
			{
				Zapret = 1;
				break;
			}
			if (M[MatriX + i][MatriY + 2] == 9)
			{
				Zapret = 1;
				break;
			}
		}
	}
	}

	if (Zapret == 0)
	{
		for (j = 0; j < 3; j++)
			for (i = 0; i < 3; i++)
			{
				F2[i][j] = F1[i][j];
			}

		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
			{
				if (M[MatriX + i][MatriY + j] != 1)
					F1[i][j] = F2[j][2 - i];
				else
				{
					for (i = 0; i < 3; i++)
						for (j = 0; j < 3; j++)
							F1[i][j] = F2[i][j];
				}
			}
		polog++;
	}
	return 0;
}
int otpravka()
{
	int i, j;
	if (Zapret == 0)
	{
		for (j = 0; j < 3; j++)//
			for (i = 0; i < 3; i++)//здесь была 2 а не 3
				if (M[MatriX + i][MatriY + j] == 1)
				{
					return 1;
				}
		for (j = 0; j < 3; j++)
			for (i = 0; i < 3; i++)
			{
				if (M[MatriX + i][MatriY + j] != 9)
					if (M[MatriX + i][MatriY + j] != 1)
					{
						M[MatriX + i][MatriY + j] = F1[i][j];
					}
			}
	}
	Zapret = 0;
	return 0;
}
void Udal()
{
	int i, j, p, o, k = 0, ochk = 0;
	for (j = 1; j < 21; j++)
	{
		k = 0;
		for (i = 1; i < 11; i++)
		{
			if (M[i][21 - j] == 1)
				k++;

		}
		if (k == 10)
		{
			ochk++;
			linii++;

			for (p = 21 - j; p > 2; p--)
				for (o = 1; o < 11; o++)
				{
					M[o][p] = M[o][p - 1];
				}
			j--;

		}
	}
	switch (ochk) {
	case 1:
		ochki += 100;
		break;
	case 2:
		ochki += 300;
		break;
	case 3:
		ochki += 700;
		break;
	case 4:
		ochki += 1500;
	}
	if (linii - lin >= 9)
	{
		lin = linii;
		TIME -= 200;
	}
}
int otpravkaP()
{
	int i, j;
	if (Zapret == 0)
		for (j = 0; j < 4; j++)
			for (i = 0; i < 4; i++)
				if (M[PatriX + i][PatriY + j] == 1)
				{
					return 1;
				}
	for (j = 0; j < 4; j++)
		for (i = 0; i < 4; i++)
		{
			if (M[PatriX + i][PatriY + j] != 9)
				if (M[PatriX + i][PatriY + j] != 1)
					M[PatriX + i][PatriY + j] = FP[i][j];
		}
	Zapret = 0;
	return 0;
}
int rotateP()
{
	if (polog == 5)
		polog = 1;
	int i, j, F2[4][4];
	switch (polog) {
	case 1: {
		for (i = 1; i < 4; i++)
		{
			if (M[PatriX + i][PatriY + 2] == 1)
			{
				Zapret = 1;
				break;
			}
			if (M[PatriX + i][PatriY + 2] == 9)
			{
				Zapret = 1;
				break;
			}
		}
	}
	}
	if (Zapret == 0)
	{
		for (j = 0; j < 4; j++)
			for (i = 0; i < 4; i++)
			{
				F2[i][j] = FP[i][j];
			}

		for (j = 0; j < 4; j++)
			for (i = 0; i < 4; i++)
			{
				if (M[PatriX + i][PatriY + j] != 1)
					FP[i][j] = F2[j][3 - i];
				else
				{
					for (j = 0; j < 4; j++)
						for (i = 0; i < 4; i++)
						{
							FP[i][j] = F2[i][j];
							return 0;
						}
				}
			}
		polog++;
	}
	return 0;
}
void timer0()
{
	double t = 0;
	Vnast1 = GetCurrentTime(hWnd) - secunda1;
	t = Vnast1 / 1000;
	Vnast = t;
}
