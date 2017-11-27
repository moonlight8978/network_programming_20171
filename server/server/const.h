#include "stdafx.h"

const int SEARCH_FAIL = -1;
const int SEARCH_SUCCESS = 0;
const int SEARCH_NO_RESULT = 0;
ROUTE ROUTES[20];
int TOTAL_ROUTES;

char* HEADER_NOT_FOUND = "HTTP/1.1 404 Not Found\nContent-Type: text/html; charset=utf-8";
char* HEADER_OK = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=utf-8";
char* HEADER_CREATED = "HTTP/1.1 201 Created\nContent-Type: text/html; charset=utf-8";
char* HEADER_BAD_REQUEST = "HTTP/1.1 400 Bad Request\nContent-Type: text/html; charset=utf-8";
char* BODY_NOT_FOUND = "<h1 style='color: red;'>404 Not found</h1>";
char* BODY_BAD_REQUEST = "<h1 style='color: red;'>Bad request</h1>";
char* BODY_CREATED = "<h1 style='color: green;'>Created</h1>";
char* METHOD_NOT_SUPPORT = "<h1 style='color: red;'>Method not support</h1>";