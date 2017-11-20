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
		}
		else {
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