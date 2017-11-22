#include "stdafx.h"

struct ROUTE {
	char* path;
	bool get;
	bool post;
};

struct CLIENT {
	SOCKET socket;
	SOCKADDR_IN addr;
};

struct PARAM {
	char key[128];
	char value[128];
};

struct REQUEST_INFO {
	char method[10];       // vd: "GET" hoac "POST"
	char path[128];        // vd: "/" hoac "/abc" ....
	char http_version[20]; // vd: "HTTP/1.1"
	PARAM params[20];      // mang params
	int total_params = 0;  // so luong params
};

struct REQUEST {
	char request_line[128]; // "GET / HTTP/1.1"
	char headers[20][1024]; // mang headers
	int total_headers = 0;  // so luong header
	char* body = NULL;      // Phan than request
};

struct PERSON {
	char last_name[64];
	char first_name[64];
	int age;
	char email[64];
};
