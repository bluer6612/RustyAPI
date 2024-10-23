#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>
#include <iostream>
#include <Windows.h>
#include <string>
//#ifdef _WINDOWS
//#include <Windows.h>
//#elseif _������
//#include <Windows.h>
//#elseif �ȵ���̵�
//#endif 

HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasss;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "Default";
    wcex.hIconSm = nullptr;

    CreateWindowClass(wcex);

    hInstance = _Instance;
}

int UEngineWindow::WindowMessageLoop()
{
    // ����Ű �ε� ����
// HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
    MSG msg;

    // �⺻ �޽��� �����Դϴ�:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // ����Ű�� �ƿ� �Ȼ���ϹǷ� ����Ű�� ó���Ѵٴ� �� ������ �����Ƿ� �ǹ̰� ���� �ڵ尡 �Ǿ���.
        if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
    // �Ϲ����� ���� ����

    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClasss.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClasss.find(std::string(_Class.lpszClassName));

    // ckw
    if (EndIter != FindIter)
    {
        // std::string ErrorText = "���� �̸��� ������ Ŭ������ 2�� ����߽��ϴ�" + std::string(_Class.lpszClassName);

        // std::string ���ο� ��� �ִ� �ɹ����� => std::string => std::vector<char>
        // std::vector<char> char* = new char[100];
        // ErrorText const char* �������ִ� �Լ��� c_str()
        // const char* Text = ErrorText.c_str();
        MSGASSERT("���� �̸��� ������ Ŭ������ 2�� ����߽��ϴ�" + std::string(_Class.lpszClassName));
        return;
    }

    RegisterClassExA(&_Class);

    WindowClasss.insert(std::pair{ _Class.lpszClassName, _Class });
}

UEngineWindow::UEngineWindow() 
{

    
}

UEngineWindow::~UEngineWindow()
{
}

void UEngineWindow::Create(std::string_view _ClassName /*= "Default"*/)
{
    Create("Window", _ClassName);
}

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    if (false == WindowClasss.contains(_ClassName.data()))
    {
        MSGASSERT("������� ���� Ŭ������ ������â�� ������� �߽��ϴ�" + std::string(_ClassName));
        return;
    }

    WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW,
        0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!WindowHandle)
    {
        MSGASSERT("������ ������ �����߽��ϴ�." + std::string(_TitleName));
        return;
    }

}

void UEngineWindow::Open(std::string_view _TitleName /*= "Window"*/)
{
    // �� window �ȸ���� ������ �ϳ�?
    if (nullptr == WindowHandle)
    {
        // �����
        Create();
    }

	// �ܼ��� ����â�� �����ִ� �͸��� �ƴ϶�
	ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
	// ShowWindow(WindowHandle, SW_HIDE);
}

void UEngineWindow::SetWindowTopMost()
{
    SetForegroundWindow(WindowHandle);
    SetWindowPos(WindowHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}