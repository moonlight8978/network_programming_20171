// TODO: Huy

int isPost(char *b)  // ham xem co phai phuong thuc post ko 
{
  for(int i=0; i<strlen(b); i++)
  {
    if(b[i]=='?'){
      return 0;
      break;
    }
  }
  return 1;
}

// ham nay luu params va tra ve totals_params
int getParams(char *par, REQUEST_INFO& request_info) 
{
  char *key[100];
  char *value[100];
  char *split = strtok(par, "&=");
  int i = 0;
  while( split != NULL ) 
  {
    if(i%2==0)
      key[i/2] = split;
    else
      value[i/2] = split;
    i++;
    split = strtok(NULL, "&=");
  }
  for(int j=0; j<i/2; j++)
  {
    strcpy(request_info.params[j].key, key[j]);
    strcpy(request_info.params[j].value, value[j]); 
  }
  return i/2;  
}

// Ham tach method, path, params cua request
//
// @param request_line [String] can tach ra thanh method, path, http_version
// @param body [String, NULL] body can tach thanh params
// @param request_info [REQUEST_INFO] luu ket qua tach'
// @return [void]
//
// @example
//   REQUEST_INFO request_info
//   get_request_info("GET /?q=2&r=3&c= HTTP/1.1", "a=2&b=3", request_info)
//   => request_info.method: "GET"
//      request_info.path: "/"
//      request_info.http_version: "HTTP/1.1"
//		  request_info.params: [{ key: "q", value: 2 }, { key: "r", value: 3 }]
//      ("a=2&b=3" bi bo qua vi GET khong ho tro body, key c bi bo vi ko co gia tri)
//
//   get_request_info("POST /?a=2&b=3 HTTP/1.1", "c=&q=2&r=3", request_info)
//   => request_info.method: "POST"
//      request_info.path: "/"
//      request_info.http_version: "HTTP/1.1"
//      request_info.params: [ 
//        { key: "a", value: 2 }, 
//        { key: "b", value: 3 }, 
//        { key: "q", value: 2 }, 
//        { key: "r", value: 3 }
//      ]
//      (key c bi bo? vi khong co gia tri)
//
//   get_request_info("POST /?a=2&b=3 HTTP/1.1", NULL, request_info)
//   get_request_info("POST / HTTP/1.1", NULL, request_info)
//   get_request_info("POST / HTTP/1.1", NULL, request_info)
//   get_request_info("GET /?a=2&b=3 HTTP/1.1", NULL, request_info)
//   get_request_info("GET /?a=2&b=3 HTTP/1.1", NULL, request_info)
//   get_request_info("GET / HTTP/1.1", NULL, request_info)
void get_request_info(char* request_line, char* body, REQUEST_INFO& request_info) {
  char a[10],b[100],c[100];  // deo nghi ra cai loz gi nen dat la a,b,c :v
  sscanf(request_line,"%s %s %s", a,b,c);
  strcpy(request_info.method, a);
  strcpy(request_info.http_version, c);

  if(isPost(b)){ // POST
    strcpy(request_info.path, b);
    request_info.total_params = getParams(body, request_info);  
  }
  else{ // GET
    char *token = strtok(b, "?");
    strcpy(request_info.path, token);
    token = strtok(NULL, "");
    strcpy(body, token);

    request_info.total_params = getParams(body, request_info);
  }
}

char *deleteLast(char *a)  // ham xoa dau :
{
  int len = strlen(a);
  a[len-1] = '\0';
  return a;
}

// Ham lay gia tri header theo ten field
//
// @param headers [Array<String>] mang cac truong header
// @param total_headers [int] tong so luong cac truong header
// @param header_field [String] ten truong` header can lay gia tri
// @param header_value [String] bien' luu gia tri header tim duoc
// @return [void]
//
// @example
//    headers[20][1024] = ["Content-Type: application/x-www-form-urlencoded"]
//    total_headers = 1
//    char header_value[128]
//    get_header(headers, total_headers, "AAAA", header_value)
//    => header_value: NULL
//    get_header(headers, total_headers, "Content-Type", header_value)
//    => header_value: "application/x-www-form-urlencoded"
void get_header(char headers[20][1024], int total_headers, char* header_field, char* header_value) {
  char * object[20]; // mang luu object , vi du: luu "Host, User-Agent, ..... "
  char * content[20]; // mang luu content
  for(int i=0; i<total_headers; i++){
    char *split = strtok(strdup(headers[i]), " ");  // phai co strdup() moi' stocking dc!
    object[i] = split; // Host:
    deleteLast(object[i]);  // Host
    split = strtok(NULL, ""); // localhost:8080
    content[i] = split;
  }
  for(int i=0; i<total_headers; i++){
    if(strcmp(object[i], header_field)==0){
      strcpy(header_value, content[i]);
      break;  
    }
  }
}
