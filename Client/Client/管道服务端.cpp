#include "iostream"
#include "windows.h"
using namespace std;
#define PIPE_NAME "\\\\.\\Pipe\\test" 
void main()
{
	char buffer[1024];
	DWORD ReadNum;
	DWORD WriteNum;
	HANDLE hPipe = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0, 0, 1000, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		cout << "创建命名管道失败！" << endl;
		CloseHandle(hPipe);
		return;
	}

	if (ConnectNamedPipe(hPipe, NULL) == FALSE)
	{
		cout << "与客户机连接失败！" << endl;
		CloseHandle(hPipe);
		return;
	}
	cout << "与客户机连接成功！" << endl;

	while (1)
	{
		if (ReadFile(hPipe, buffer, 1024, &ReadNum, NULL) == FALSE)
		{
			cout << "读取数据失败！" << endl;
			break;
		}

		buffer[ReadNum] = 0;
		cout << "读取数据:" << buffer << endl;
		if (WriteFile(hPipe, buffer, strlen(buffer), &WriteNum, NULL) == FALSE)
		{
			cout << "数据写入管道失败！" << endl;
			break;
		}
	}

	cout << "关闭管道！" << endl;
	CloseHandle(hPipe);
	system("pause");
}