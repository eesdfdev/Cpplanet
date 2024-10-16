#include "ServerSock.h"
#include "ClientSession.h"
#include <iostream>
#include "Config.h"
#include <ip2string.h>

ServerSock::ServerSock() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr = {};
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons((u_short)Config::BindingPort);
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
}
void ServerSock::Run() {
	if (SOCKET_ERROR == bind(sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr))) {
		std::wcout << "소켓 바인딩 실패" << std::endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	std::wcout << "서버 소켓이 바인딩 됐습니다.\n 포트 : " << (u_short)Config::BindingPort << std::endl;
	listen(sock, SOMAXCONN);
	while (1) {
		sockaddr_in ClientAddress;
		int len = sizeof(ClientAddress);
		SOCKET client = accept(sock, (SOCKADDR*)&ClientAddress, &len);
		wchar_t ClientIP[16];
		RtlIpv4AddressToStringW((in_addr*) & ClientAddress.sin_addr.S_un.S_addr, ClientIP);
		std::wcout << "새로운 요청\n 클라이언트 IP : " << ClientIP << " Port : " << ClientAddress.sin_port << std::endl;

		ClientSession* clientSession = new ClientSession(client);
	}
}