// TODO: Bich

// Ham fix %20, %40
void decode_urlencoded(char str[]) {
  int len = strlen(str);
  int j = 0, i = 0;
  char fixed[len];

  while (i < len) {
    if (str[i] == '%' && str[i+1] == '2' && str[i+2] == '0') {
      fixed[j] = ' ';
      i += 3;
    } else if (str[i] == '%' && str[i+1] == '4' && str[i+2] == '0') {
      fixed[j] = '@';
      i += 3;
    } else {
      fixed[j] = str[i];
      i += 1;
    }
    
    j += 1;
  }
  
  strcpy(str, fixed);
}

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
    decode_urlencoded(request.body);
  }
}

// 
void create_table(PERSON* results, int total_results, char* body) {
  char line[256];
  if (total_results > 0 ) {
    strcpy(body, "<table><tr><td>Ho</td><td>Ten</td><td>Nam sinh</td><td>Email</td></tr>");
    for (int i = 0; i < total_results; i += 1) {
      sprintf(
        line,
        "<tr><td>%s</td><td>%s</td><td>%d</td><td>%s</td></tr>",
        results[i].last_name, results[i].first_name, results[i].year_of_birth, results[i].email
      );
      strcat(body, line);
    }
    strcat(body, "</table>");
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
void create_response(char* header, char* body, char* response) {
  strcpy(response, header);
  strcat(response, "\n\n");
  strcat(response, "<html><body>");
  strcat(response, body);
  strcat(response, "</body></html>");
}

// Doc 1 dong tu file, fix \n khi fgets
char* get_line(FILE* file, char* des, int des_size) {
  char* pnt = fgets(des, des_size, file);
  des[strlen(des) - 1] = 0;
  return pnt;
}

// Kiem tra xem mot `PERSON` co thoa man dieu kien hay khong
bool is_matched_conditions(PERSON& idol, PERSON& condition) {
  if (
    (strlen(condition.last_name) > 0)
    && (strcmp(condition.last_name, idol.last_name) != 0)
  ) {
//    printf("Tach last_name");
    return false;
  }

  if (
    (strlen(condition.first_name) > 0)
    && (strcmp(condition.first_name, idol.first_name) != 0)
  ) {
//    printf("Tach first_name");
    return false;
  }

  if (
    (strlen(condition.email) > 0)
    && (strcmp(condition.email, idol.email) != 0)
  ) {
//    printf("Tach email");
    return false;
  }

  if (
    (condition.year_of_birth != 0)
    && (condition.year_of_birth != idol.year_of_birth)
  ) {
//    printf("Tach last_name");
    return false;
  }

  return true;
}

// Ham truy van file theo cac dieu kien
//
// @param file_path [String] path file can truy van tinh tu thu muc goc
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
int query_file(char* file_path, PARAM* conditions, int total_conditions, PERSON* results) {
	int total_results = 0;
  PERSON condition;

  for (int i = 0; i < total_conditions; i += 1) {
    if (strcmp(conditions[i].key, "first_name") == 0) {
      strcpy(condition.first_name, conditions[i].value);
    } else if (strcmp(conditions[i].key, "last_name") == 0) {
      strcpy(condition.last_name, conditions[i].value);
    } else if (strcmp(conditions[i].key, "year_of_birth") == 0) {
      condition.year_of_birth = atoi(conditions[i].value);
    } else if (strcmp(conditions[i].key, "email") == 0) {
      strcpy(condition.email, conditions[i].value);
    }
  }

  char file_name[64];
  sprintf(file_name, ".%s.txt", file_path);

  FILE* file;
  file = fopen(file_name, "r");
  char line[256];
  while (!feof(file)) {
    PERSON p;
    if (get_line(file, p.last_name, sizeof(p.last_name)) == NULL) {
      break;
    }
    get_line(file, p.first_name, sizeof(p.first_name));
    get_line(file, line, sizeof(line));
    p.year_of_birth = atoi(line);
    get_line(file, p.email, sizeof(p.email));

    if (is_matched_conditions(p, condition)) {
      results[total_results] = p;
      total_results += 1;
    }
  }

  fclose(file);
  return total_results;
}

// Ham ghi 1 xau vao file, 
//   ghi vao line moi', khong duoc ghi cung line du lieu cu~
//
// @param file_path [String] path cua file can ghi tinh tu thu muc goc
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
void write_file(char* file_path, char* content) {
  char file_name[64];
  sprintf(file_name, ".%s", file_path);

	FILE* file;
	file = fopen(file_name, "a");
	fprintf(file, "%s\n", content);
	fclose(file);
}

// Ham luu mot person moi
bool create_person(char* path, PARAM* params, int total_params) {
  bool created = false;
  PERSON new_idol;

  for (int i = 0; i < total_params; i += 1) {
    if (strcmp(params[i].key, "first_name") == 0) {
      strcpy(new_idol.first_name, params[i].value);
    } else if (strcmp(params[i].key, "last_name") == 0) {
      strcpy(new_idol.last_name, params[i].value);
    } else if (strcmp(params[i].key, "year_of_birth") == 0) {
      new_idol.year_of_birth = atoi(params[i].value);
    } else if (strcmp(params[i].key, "email") == 0) {
      strcpy(new_idol.email, params[i].value);
    }
  }

  if (
    (strlen(new_idol.last_name) > 0)
    && (strlen(new_idol.first_name) > 0)
    && (new_idol.year_of_birth != 0)
    && (strlen(new_idol.email) > 0)
  ) {
    created = true;
    char write_data[256];
    sprintf(
      write_data, 
      "%s\n%s\n%d\n%s",
      new_idol.last_name, new_idol.first_name, new_idol.year_of_birth, new_idol.email
    );

    char file_name[64];
    sprintf(file_name, "%s.txt", path);
    write_file(file_name, write_data);
  }

  return created;
}

// Xu ly route "/"
void route_index(REQUEST_INFO& request_info, char* response) {
  char body[2048] = "";

  if (strcmp(request_info.method, "GET") == 0) {
    strcpy(body, "<h1>Hello</h1>");
    create_response(HEADER_OK, body, response);
  }
}

// Xy ly route "/idols"
void route_idols(REQUEST_INFO& request_info, char* response) {
  char body[2048] = "";
  
  if (strcmp(request_info.method, "GET") == 0) {
    // GET request
    PERSON results[20];
    int total_results;
    total_results = query_file(
      request_info.path, 
      request_info.params, 
      request_info.total_params, 
      results
    );

    if (total_results != SEARCH_NO_RESULT) {
      create_table(results, total_results, body);
      create_response(HEADER_OK, body, response);
    } else {
      create_response(HEADER_NOT_FOUND, BODY_NOT_FOUND, response);
    }
  } else if (strcmp(request_info.method, "POST") == 0) {
    // POST request
    bool created = create_person(
      request_info.path, 
      request_info.params, 
      request_info.total_params
    );

    if (created) {
      create_response(HEADER_CREATED, BODY_CREATED, response);
    } else {
      create_response(HEADER_BAD_REQUEST, BODY_BAD_REQUEST, response);
    }
  }
}
