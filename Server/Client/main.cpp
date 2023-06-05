#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <winsock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32");

#define BUFSIZE 512

void err_quit(const char* msg) {
	LPVOID IpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&IpMsgBuf, 0, NULL);
	exit(-1);
}

int main(int argc, char* argv[]) {
	//���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;
	//MessageBox(NULL, "���� �ʱ�ȭ ����", "�˸�", MB_OK);

	while (true)
	{
		//socket()
		SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET) err_quit("socket()");
		printf("������ �����Ǿ����ϴ�.\n");
		//MessageBox(NULL, "TCP ���ϼ���", "�˸�", MB_OK);

		//connect()
		SOCKADDR_IN serveraddr;
		ZeroMemory(&serveraddr, sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		serveraddr.sin_port = htons(9000);

		connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
		printf("connect �����û!!\n");

		//������ ���� ��Ʈ�� ����
		char buf[BUFSIZE + 1];

		std::cin >> buf;

		if (buf == "")
		{
			break;
		}
		
		//send()
		send(sock, buf, strlen(buf), 0);
		std::cout << ("�޼����� �����ϴ�.\n");

		//closesocket()
		closesocket(sock);
	}

	//���� ����
	WSACleanup();
	return 0;
}