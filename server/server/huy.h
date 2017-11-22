// TODO: Huy

// Ham tach method, path, params cua request
//
// @param request_line [String] can tach ra thanh method, path, http_version
// @param body [String, NULL] body POST (params) can tach, neu la GET thi body NULL
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
//		  request_info.params: [{ key: "q", value: 2 }, { key: "r", value: 3 }]
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
//    char* header_value
//    get_header(headers, total_headers, "AAAA", header_value)
//    => header_value: NULL
//    get_header(headers, total_headers, "Content-Type", header_value)
//    => header_value: "application/x-www-form-urlencoded"
void get_header(char** headers, int total_headers, char* header_value) {
  // code
}
