#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include<stdio.h>
#include<stdlib.h>
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
	int retval;

	//�����ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;
	//MessageBox(NULL, "���� �ʱ�ȭ ����", "�˸�", MB_OK);

	while (true)
	{
		//socket()
		SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
		if (listen_sock == INVALID_SOCKET) err_quit("socket()");
		printf("������ �����Ǿ����ϴ�\n");
		//MessageBox(NULL, "TCP ���ϼ���", "�˸�", MB_OK);

		//bind()
		SOCKADDR_IN serveraddr;
		ZeroMemory(&serveraddr, sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
		serveraddr.sin_port = htons(9000);

		bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
		printf("Bind �Ϸ� �Ǿ����ϴ�.\n");

		//listen()
		listen(listen_sock, SOMAXCONN);
		printf("connect ������ ��ٸ��� ��..\n");

		//��ſ� ����� ����
		SOCKET client_sock;
		SOCKADDR_IN clientaddr;
		int addrlen;
		char buf[BUFSIZE + 1];

		//accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		printf("��û�� �޾ҽ��ϴ�.\n");

		//recv()
		retval = recv(client_sock, buf, BUFSIZE, 0);
		printf("�޼����� �����Ͽ����ϴ�.\n");

		//�޴� ������ ���
		buf[retval] = '\0';
		printf("[TCP/%s:%d] %s\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), buf);

		//closesocket
		closesocket(listen_sock);
	}

	//���� ����
	WSACleanup();
	return 0;

}