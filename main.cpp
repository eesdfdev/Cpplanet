#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "ServerSock.h"
#include <locale.h>
#include <Windows.h>
#include <Shlwapi.h>
int main() {
	_wsetlocale(LC_ALL, L"");
	wchar_t Path[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, Path);
	wchar_t* filePath = wcsncat(Path, L"/RunnedBefore", 14);
	if (!PathFileExistsW(filePath) ) {
		HANDLE file = CreateFileW(filePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
		if ( file == NULL ) {
			std::cout << GetLastError() << std::endl;
		}
		CloseHandle(file);
		ShellExecute(NULL, "open", "https://discord.gg/bw67XNE2EH", NULL, NULL, SW_SHOWNORMAL);
	}
	std::cout << "\x1b[94m" << "에버플래닛 서버 by 이시프" << "\x1b[39m" << std::endl;
	ServerSock* socket = new ServerSock();
	socket->Run();
	return 0;
}