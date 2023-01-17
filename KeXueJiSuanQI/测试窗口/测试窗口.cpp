
#include "stdafx.h"
#include "���Դ���.h"


//�ַ����鳤��
#define MAX_LOADSTRING 100

//ȫ�ֱ���
HINSTANCE hInst;                                            // ��ǰʵ��
TCHAR g_szTitle[MAX_LOADSTRING] = TEXT("Message process");  // ���ڱ���
TCHAR g_szWindowClass[MAX_LOADSTRING] = TEXT("AppTest");    // �����������
HWND g_hWnd;                                                // ���ھ��
bool g_bWhite = false;                                      // �Ƿ�Ϊ��ɫ����

															//WinMain��ں���
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	// ע�ᴰ����
	if (!AppRegisterClass(hInstance))
	{
		return (FALSE);
	}
	// ��ʼ��Ӧ�ó��򴰿�
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// ��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}



// ע�ᴰ����
ATOM AppRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = g_szWindowClass;
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex);
}



// ����ʵ�������������������
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // ����handle��ȫ�ֱ���
	g_hWnd = CreateWindow(g_szWindowClass, g_szTitle, WS_OVERLAPPEDWINDOW, 100, 100, 400, 300, NULL, NULL, hInstance, NULL);
	// ������ť
	//HWND hBtWhite = CreateWindowEx(0, L"Button", L"��ɫ", WS_CHILD | WS_VISIBLE | BS_TEXT, 100, 100, 50, 20, g_hWnd, (HMENU)ID_BUTTON_DRAW, hInst, NULL);
	//HWND hBtGray = CreateWindowEx(0, L"Button", L"��ɫ", WS_CHILD | WS_VISIBLE | BS_CENTER, 250, 100, 50, 20, g_hWnd, (HMENU)ID_BUTTON_SWEEP, hInst, NULL);

	if (!g_hWnd)
	{
		return FALSE;
	}
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}



// (����)��Ϣ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		//wmEvent = HIWORD(wParam);

		switch (wmId)
		{
		case ID_BUTTON_DRAW:
			OnButtonWhite();
			break;
		case ID_BUTTON_SWEEP:
			OnButtonGray();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//OnDraw(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



//�¼�����

//����hBtWhiteʱ���¼�
void OnButtonWhite()
{
	g_bWhite = true;
	InvalidateRect(g_hWnd, NULL, FALSE);    //ˢ�´���
}

//����hBtGrayʱ���¼�
void OnButtonGray()
{
	g_bWhite = false;
	InvalidateRect(g_hWnd, NULL, FALSE);    //ˢ�´���
}

//�����¼�(ÿ��ˢ��ʱ���»���ͼ��)
//void OnDraw(HDC hdc)
//{
//	POINT oldPoint;
//	//SetViewportOrgEx(hdc,0, 0, &oldPoint);
//	RECT rcView;
//	GetWindowRect(g_hWnd, &rcView); // ��þ���Ļ�����С
//	HBRUSH hbrWhite = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	HBRUSH hbrGray = (HBRUSH)GetStockObject(GRAY_BRUSH);
//	if (g_bWhite)
//	{
//		FillRect(hdc, &rcView, hbrWhite);
//	}
//	else
//	{
//		FillRect(hdc, &rcView, hbrGray);
//	}
//	//SetViewportOrgEx(hdc, oldPoint.x, oldPoint.y, NULL);
//}
