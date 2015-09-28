#include "Dialog.h"
#include <commctrl.h>
//Project for Fun

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR pCmdLine, int nCmdShow)
{
	//AllocConsole();
	//freopen("CONOUT$", "wt", stdout);
	MSG  msg;
	HWND hwnd;
	WNDCLASSW wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Winder";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassW(&wc);
	hwnd = CreateWindowW(wc.lpszClassName, L"Spam Central",
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
		500, 500, 800, 400, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartSpam, 0, 0, 0);

	return (int)msg.wParam;
}

HWND MessageOne;
HWND MessageTwo;
HWND Button_Start;
HWND Button_Stop;
HWND TrackBar;
HWND About;

HWND MinTrackBar;
HWND MaxTrackBar;
HWND TrackVal;
HWND CountDown;

HANDLE Thread;


void StartSpam(int SpamCount);

#pragma region Controls
void UpdateLabel()
{
	int pos = SendMessage(TrackBar, TBM_GETPOS, 0, 0);
	char buf[124];
	sprintf(buf, "Spam Count: %i", pos);
	SetWindowText(TrackVal, buf);
}

void UpdateCountDown(int cnt)
{
	char buf[64];
	sprintf(buf, "Spam in: %i", cnt);
	SetWindowText(CountDown, buf);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		 HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		 Button_Start = CreateWindowW(L"button", L"Start Spam", WS_VISIBLE | WS_CHILD, 325, 250, 100, 25, hwnd, (HMENU)ID_START, NULL, NULL);
		 Button_Stop = CreateWindowW(L"button", L"Stop Spam", WS_VISIBLE | WS_CHILD, 325, 300, 100, 25, hwnd, (HMENU)ID_STOP, NULL, NULL);
		 About = CreateWindowW(L"button", L"About", WS_VISIBLE | WS_CHILD, 680, 330, 100, 25, hwnd, (HMENU)ID_ABT, NULL, NULL);


		 MessageOne = CreateWindowW(L"Edit", L"Message One", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 280, 150, 200, 25, hwnd, (HMENU)ID_MESSAGEONE, NULL, NULL);
		 MessageTwo = CreateWindowW(L"Edit", L"Message Two", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 280, 200, 200, 25, hwnd, (HMENU)ID_MESSAGETWO, NULL, NULL);

		 MinTrackBar = CreateWindowW(L"Static", L"0", WS_VISIBLE | WS_CHILD, 215, 75, 10, 30, hwnd, (HMENU)55, 0, 0);
		 MaxTrackBar = CreateWindowW(L"Static", L"1000", WS_VISIBLE | WS_CHILD, 215, 75, 50, 30, hwnd, (HMENU)56, 0, 0);
		 CountDown = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD, 330, 40, 100, 30, hwnd, (HMENU)57, 0, 0);
		 TrackBar = CreateWindowW(L"msctls_trackbar32", L"TrackBar", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, 225, 75, 300, 50, hwnd, (HMENU)ID_TRACKBAR, 0, 0);
		 TrackVal = CreateWindowW(L"Static", L"Spam Count: 0", WS_VISIBLE | WS_CHILD, 600, 75, 150, 30, hwnd, (HMENU)ID_TRACKVAL, 0, 0);


		 SendMessage(TrackBar, TBM_SETRANGE, TRUE, MAKELONG(0, 1000));
		 SendMessage(TrackBar, TBM_SETPAGESIZE, 0, 100);
		 SendMessage(TrackBar, TBM_SETTICFREQ, 100, 0);
		 SendMessage(TrackBar, TBM_SETPOS, FALSE, 0);
		 SendMessage(TrackBar, TBM_SETBUDDY, TRUE, reinterpret_cast<LPARAM>(MinTrackBar));
		 SendMessage(TrackBar, TBM_SETBUDDY, FALSE, reinterpret_cast<LPARAM>(MaxTrackBar));

		 SendMessage(MessageOne, WM_SETFONT, (WPARAM)hFont, NULL);
		 SendMessage(MessageTwo, WM_SETFONT, (WPARAM)hFont, NULL);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_START:
			Thread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(StartSpam), (LPVOID)SendMessage(TrackBar, TBM_GETPOS, 0, 0), 0, 0);
			break;
		case ID_ABT:
			MessageBox(hwnd, "About:\nFast C++ Spambot\nF8: Quick Stop\nCoded by 007jet -2015", "About", MB_ICONINFORMATION | MB_OK);
			break;
		case ID_STOP:
			INPUT ipp;
			ipp.type = INPUT_KEYBOARD;
			ipp.ki.wScan = 0;
			ipp.ki.time = 0;
			ipp.ki.dwExtraInfo = 0;
			ipp.ki.wVk = VK_F8;
			ipp.ki.dwFlags = 0;
			SendInput(1, &ipp, sizeof(INPUT));
			ipp.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ipp, sizeof(INPUT));
			break;
		}
	case WM_HSCROLL:
		UpdateLabel();
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}
#pragma endregion Controls

#pragma region SpamBot
INPUT ip;
void ShiftDown();
void ShiftUp();
void CapsToggle();

void EvaluateText(const char* text) //Capital Letter Handling
{
	for (int i = 0; i < strlen(text); i++)
	{
		if (isalpha(text[i]))
		{
			if (isupper(text[i]))
			{
				ShiftDown();
				ip.ki.wVk = text[i];
				ip.ki.dwFlags = 0;
				SendInput(1, &ip, sizeof(INPUT));
				ip.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &ip, sizeof(INPUT));
				ShiftUp();
			}
			else
			{
				if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
					CapsToggle();
				ip.ki.wVk = toupper(text[i]);
				ip.ki.dwFlags = 0;
				SendInput(1, &ip, sizeof(INPUT));
				ip.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &ip, sizeof(INPUT));
			}
		}
		else
		{
			ip.ki.wVk = text[i];
			ip.ki.dwFlags = 0;
			SendInput(1, &ip, sizeof(INPUT));
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));
		}
		Sleep(1);
	}
	ip.ki.wVk = 0x0D;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void CapsToggle()
{
	ip.ki.wVk = VK_LSHIFT;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void ShiftDown()
{
	ip.ki.wVk = VK_LSHIFT;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
}

void ShiftUp()
{
	ip.ki.wVk = VK_LSHIFT;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void StartSpam(int SpamCount)
{
	for (int i = 5; i > 0; i--)
	{
		UpdateCountDown(i);
		Sleep(1000);
	}
	char left[32];
	SetWindowText(CountDown, "");
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	char Textt[1024];
	char Text2[1024];
	int len = SendMessage(MessageOne, WM_GETTEXTLENGTH, 0, 0);
	SendMessage(MessageOne, WM_GETTEXT, (WPARAM)len + 1, (LPARAM)Textt);

	int len2 = SendMessage(MessageTwo, WM_GETTEXTLENGTH, 0, 0);
	SendMessage(MessageTwo, WM_GETTEXT, (WPARAM)len2 + 1, (LPARAM)Text2);
	for (int i = 0; i < SpamCount; i++)
	{
		if (GetAsyncKeyState(VK_F8))
			i = SpamCount;
		sprintf(left, "Spams Left: %i", SpamCount-i);
		SetWindowText(CountDown, left);
		EvaluateText(Textt);
		EvaluateText(Text2);
	}
	SetWindowText(CountDown, "Spam Complete!");
	Sleep(2000);
	SetWindowText(CountDown, "");
}
#pragma endregion SpamBot

