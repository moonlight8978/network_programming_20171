#include "struct.h"

// NOTE: STRUCT xem tai "Header Files/struct.h"
// NOTE: HANG SO xem tai "Header Files/const.h"

// TODO: Bich
// Xu ly tho request, tach thanh request_line, headers[], body
//
// @param buffer [String] chuoi request nhan duoc
// @param request [REQUEST] luu ket qua tach'
// @return [void]
//
// @example
//   REQUEST request
//   split_request(buff, request)
//   => request.request_line: "GET /?q=2&r=3 HTTP/1.1"
//		request.body: NULL (vi la GET)
//		request.headers: ["Host: localhost:8888", "Connection: keep-alive"]
//		request.total_headers: 2
void split_request(char* buffer, REQUEST& request) {
	char* pointer;
	int len;
	int i = 0;
	request.headers = new char*[20];

	pointer = strtok(buffer, "\n");
	while (pointer != NULL) {
		len = strlen(pointer);
		if (i == 0) {
			request.request_line = new char[len];
			strcpy(request.request_line, pointer);
		} else {
			request.headers[request.total_headers] = new char[len];
			strcpy(request.headers[request.total_headers], pointer);
			request.total_headers++;
		}
		i++;
		pointer = strtok(NULL, "\n");
		if ((strlen(pointer) == 1) && (int(*pointer) == 13)) // \r\n, ASCII code: 13
			break;
	}

	pointer = strtok(NULL, "\0");
	// Kiem tra request body
	if (pointer != NULL) {
		len = strlen(pointer);
		request.body = new char[len];
		strcpy(request.body, pointer);
	}
}

// TODO: Huy

// Ham tach method, path, params cua request
//
// @param request_line [String] can tach ra thanh method, path, http_version
// @param body [String] body POST (params) can tach, neu la GET thi body NULL
// @param request_info [REQUEST_INFO] luu ket qua tach'
// @return [void]
// 
// @example
//   request_line = GET /?q=2&r=3 HTTP/1.1
//   body = NULL
//   REQUEST_INFO request_info
//   get_request_info(request_line, body, request_info)
//   => request_info.method: "GET"
//      request_info.path: "/"
//      request_info.http_version: "HTTP/1.1"
//		request_info.params: [{ key: "q", value: 2 }, { key: "r", value: 3 }]
void get_request_info(char* request_line, char* params, REQUEST_INFO& request_info) {
	// code
}

// Ham lay gia tri header theo ten field
//
// @param headers [Array<String>] mang cac truong header
// @param total_headers [int] tong so luong cac truong header
// @param header_value [String, NULL] bien' luu gia tri header tim duoc,
//    ko tim duoc thi gan' bang NULL
// @return [void]
//
// @example
//    headers = ["Content-Type: application/x-www-form-urlencoded"]
//    total_headers = 1
//    get_header(headers, total_headers, "AAAA", header_value)
//    => header_value: NULL
//    get_header(headers, total_headers, "Content-Type", header_value) 
//    => header_value: "application/x-www-form-urlencoded"
void get_header(char** headers, char* header_value) {
	// code
}

// TODO: Bang

// Viet ham lay thoi gian hien tai, dia chi IP cua request

// TODO: Thang

// Viet ham truy van file, ghi file
