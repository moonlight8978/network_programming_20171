// TODO: Bich

// Routing, kiem tra yeu cau hop le hay khong
//
// @param method [String] phuong thuc HTTP
// @param path [String] path yeu cau
// @return [true, false]
//
// @example
//   is_valid_route("GET", "/")      # => true
//   is_valid_route("POST", "/clgt") # => false
bool is_valid_route(char* method, char* path) {
  bool matched = false;
  for (int i = 0; i < TOTAL_ROUTES; i += 1) {
    if (strcmp(path, ROUTES[i].path) == 0) {
      matched =
        (strcmp(method, "GET") == 0 && ROUTES[i].get)
        || (strcmp(method, "POST") == 0 && ROUTES[i].post);

      if (matched) {
        return true;
      }
    }
  }

  return false;
}

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
//      request.body: NULL (vi la GET)
//      request.headers: ["Host: localhost:8888", "Connection: keep-alive"]
//      request.total_headers: 2
void split_request(char* buffer, REQUEST& request) {
  char* pointer;
  int i = 0;

  pointer = strtok(buffer, "\n");
  while (pointer != NULL) {
    if (i == 0) {
      strcpy(request.request_line, pointer);
    } else {
      strcpy(request.headers[request.total_headers], pointer);
      request.total_headers += 1;
    }
    i += 1;
    pointer = strtok(NULL, "\n");
    if ((strlen(pointer) == 1) && (int(*pointer) == 13)) // \r\n, ASCII code: 13
    break;
  }

  pointer = strtok(NULL, "\0");
  // Kiem tra request body
  if (pointer != NULL) {
    request.body = new char[strlen(pointer)];
    strcpy(request.body, pointer);
  }
}

// Ham tao phan hoi cho client
//
// @todo vong lap dung ket qua tu ham `#query_file`
//
// @param header [String] header phan hoi
// @param results [Array<PERSON>] mang ket qua
// @param total_results [int] so luong ket qua
// @param resposne [String] luu ket qua
// @return [void]
void create_response(char* header, PERSON** results, int total_results, char* response) {
  strcpy(response, header);
  char body[1024];
  char line[128];

  strcpy(body, "<html><body><table><tr><td>Ten</td><td>Tuoi</td><td>Email</td></tr>");
  for (int i = 0; i < total_results; i += 1) {
    sprintf(
      line,
      "<tr><td>%s</td><td>%s</td><td>%s</td></tr>",
      "Bach", "20", "depzai@gmail.com"
    );
    strcat(body, line);
  }
  strcat(body, "</table></body></html>");

  strcat(response, body);
}

// Ham truy van file theo cac dieu kien
//
// @param file_name [String] ten file can truy van
// @param conditions [Array<PARAM>] mang cac dieu kien truy van
// @param total_conditions [int] so luong dieu kien
// @param results [Array<PERSON>] mang ket qua tim duoc sau khi doc file
// @return [int] so luong ket qua tim duoc
//
// @example
//	 PERSON results[20] (cau truc file txt doc "/README.html")
//   conditions = [{ first_name: "Bach" }, { year_of_birth: 1997 }]
//	 int res
//   res = query_file("file.txt", conditions, 2, results)
//   => res: 0 (khong tim thay)
//   => res: n, results: [person1, person2 ....] (tim duoc n ket qua)
int query_file(char* file_name, PARAM* conditions, int total_conditions, PERSON* results) {
	int total_results = 0;
	results = new PERSON[20];
	
	FILE* file;
	file = fopen(file_name, "r");
	char line[256];
	while (fgets(line, sizeof(line), file) != NULL) {
		// read file, save to results
	}

	fclose(file);
	return total_results;
}

// Ham ghi 1 xau vao file, 
//   ghi vao line moi', khong duoc ghi cung line du lieu cu~
//
// @param file_name [String] ten file can ghi
// @param content [String] du lieu can ghi
// @return [void]
// 
// @example
//   "/log.txt": 
//     aaaaaaaaaa
//     bbbbbbbbbb
//     new_line (\n)
//   write_file("log.txt", "cccccc")
//   => "/log.txt": (sai)
//     aaaaaaaaaa
//     bbbbbbbbbb
//     cccccc
//   => "/log.txt": (dung)
//     aaaaaaaaaa
//     bbbbbbbbbb
//     cccccc
//     new_line (\n)
void write_file(char* file_name, char* content) {
	FILE* file;
	file = fopen(file_name, "a");
	fprintf(file, "%s\n", content);
	fclose(file);
}