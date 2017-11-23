// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "maya.h"

DWORD WINAPI Thread(LPVOID lpParams);

CLIENT clients[64];
int total_clients = 0;

void remove_client(CLIENT* clients, int& total_clients, SOCKET client) {
  for (int i = 0; i < total_clients; i++) {
    if (clients[i].socket == client) {
      clients[i] = clients[total_clients - 1];
      total_clients--;
    }
  }
}

// @note: KHONG DUOC SUA HAM MAIN
int main() {
  int PORT = 8888;
  define_routes();

  WSADATA wsa_data;
  WSAStartup(MAKEWORD(2, 2), &wsa_data);
  SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  SOCKADDR_IN addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(PORT);

  bind(listener, (SOCKADDR*)&addr, sizeof(addr));
  listen(listener, 5);
  printf("Listening on port %d...\n", PORT);

  while (true) {
    SOCKADDR_IN client_addr;
    int len = sizeof(client_addr);
    SOCKET client_socket = accept(listener, (SOCKADDR*)&client_addr, &len);

    CLIENT client;
    client.addr = client_addr;
    client.socket = client_socket;

    clients[total_clients] = client;
    total_clients += 1;

    CreateThread(0, 0, Thread, &client, 0, 0);
  }

  closesocket(listener);
  WSACleanup();

  return 0;
}

// @note: CODE LOGIC, TEST cho vao ham nay
DWORD WINAPI Thread(LPVOID lpParams) {
  CLIENT client = *((CLIENT*)lpParams);
  //log_request(client.addr);

  char buff[2048];
  int res;
  res = recv(client.socket, buff, sizeof(buff), 0);
  if (res == 0 || res == SOCKET_ERROR) {
    return 0;
  }
  buff[res] = 0;
  printf("Buffer: %s", buff);

  REQUEST request;
  REQUEST_INFO request_info;
  split_request(buff, request);
  // @debug
  printf("Request line: %s\n", request.request_line);
  if (request.body != NULL) {
    printf("Request body: %s\n", request.body);
  }
  printf("Headers: (total %d)\n", request.total_headers);
  for (int i = 0; i < request.total_headers; i += 1) {
    printf(
      "No.%d (%d): %s\n",
      i + 1, strlen(request.headers[i]), request.headers[i]
    );
  }
  std::cout << is_valid_route("GET", "/people");
  std::cout << is_valid_route("GET", "/loz");
  PERSON** results;
  char response[2048];
  create_response(HEADER_CREATED, results, 5, response);

  //get_request_info(request.request_line, request.body, request_info);
  //query_file(request_info.path, request_info.params, request_info.total_params);

  send(client.socket, response, strlen(response), 0);
  closesocket(client.socket);
  remove_client(clients, total_clients, client.socket);

  return 0;
}
