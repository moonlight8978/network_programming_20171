// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winsock2.h"
#include "iostream"

DWORD WINAPI Thread(LPVOID lpParams);

SOCKET clients[64];
int total_clients = 0;

void remove_client(SOCKET* clients, int& total_clients, SOCKET client) {
	for (int i = 0; i < total_clients; i++) {
		if (clients[i] == client) {
			clients[i] = clients[total_clients - 1];
			clients[total_clients - 1] = NULL;
			total_clients--;
		}
	}
}

int main() {
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(2, 2), &wsa_data);
	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8000);

	bind(listener, (SOCKADDR*)&addr, sizeof(addr));
	listen(listener, 5);
	std::cout << "Listening...";
	SOCKET client;

	while (true) {
		client = accept(listener, NULL, NULL);
		CreateThread(0, 0, Thread, &client, 0, 0);
	}

	closesocket(client);
	closesocket(listener);
	WSACleanup();

	return 0;
}

DWORD WINAPI Thread(LPVOID lpParams) {
	SOCKET client = *((SOCKET*)lpParams);
	clients[total_clients] = client;
	total_clients += 1;

	char buff[2048];
	int res;

	res = recv(client, buff, sizeof(buff), 0);

	if (res == 0 || res == SOCKET_ERROR) {
		return 0;
	}

	buff[res - 1] = 0;

	std::cout << res << std::endl;
	std::cout << strlen(buff) << std::endl;
	std::cout << buff;

	char* msg = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\n\n<html><b>Temp</b><br><i>log.txt</i><br></html>";
	send(client, msg, strlen(msg), 0);
	closesocket(client);
	remove_client(clients, total_clients, client);

	return 0;
}


