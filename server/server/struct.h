#include "stdafx.h"

struct PARAM {
	char key[128];
	char value[128];
};

struct REQUEST_INFO {
	char method[10];       // vd: "GET" hoac "POST"
	char path[128];        // vd: "/" hoac "/abc" .... 
	char http_version[20]; // vd: "HTTP/1.1"
	PARAM* params;         // mang params
	int total_params;      // so luong params
};

struct REQUEST {
	char* request_line;     // "GET / HTTP/1.1"
	char** headers;         // mang headers
	int total_headers = 0;  // so luong header
	char* body = NULL;      // Phan than request
};
