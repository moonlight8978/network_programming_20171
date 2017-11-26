#include "stdafx.h"

const int SEARCH_FAIL = -1;
const int SEARCH_SUCCESS = 0;
const int SEARCH_NO_RESULT = 0;
ROUTE ROUTES[20];
int TOTAL_ROUTES;

char* HEADER_NOT_FOUND = "HTTP/1.1 404 Not Found\nContent-Type: text/html; charset=utf-8\n\n";
char* HEADER_OK = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8\n\n";
char* HEADER_CREATED = "HTTP/1.1 201 Created\nContent-Type: text/html; charset=utf-8\n\n";
