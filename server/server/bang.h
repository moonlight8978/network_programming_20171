// TODO: Bang
// Viet ham lay thoi gian hien tai, dia chi IP cua request

// Ham lay thoi gian hien tai
//
// @param current_time [String] xau luu ket qua
// @return [void]
//
// @example
//   char current_time[128]
//   get_current_time(current_time)
//   => current_time: "2017/11/21 10:25AM" (vi du, thuc te co the khac)
void get_current_time(char* current_time) {
  time_t time_now = time(0);
  strcpy(current_time, ctime(&time_now));
  current_time[strlen(current_time) - 1] = 0;
}

// Ham phan giai dia chi IP
//
// @param client_addr [SOCKADDR_IN] struct dia chi nguoi dung can phan giai
// @param ip_addr [String] xau luu IP nguoi dung
// @return [void]
//
// @example
//   char ip_addr[128]
//   get_ip_addr(client_addr, ip_addr)
//   => ip_addr: "127.0.0.1" (vi du, thuc te co the khac)
void get_ip_addr(SOCKADDR_IN& client_addr, char* ip_addr) {
  if (client_addr.sin_family == AF_INET) 
  {
    strcpy(ip_addr, inet_ntoa(client_addr.sin_addr));
  }
}

// Ghi nhat ky, goi den `#get_current_time`, `#get_ip_addr` de lay ket qua,
//   noi xau lai, roi ghi vao file log.txt
//
// @param client_addr [SOCKADDR_IN] struct dia chi nguoi dung can phan giai
// @return [void]
//
// @example
//   log_request(client_addr)
//   => "log.txt": "127.0.0.1 2017/11/21 10:25AM"
void log_request(SOCKADDR_IN& client_addr) {
  char current_time[128], ip_addr[128], result[256];

  get_current_time(current_time);
  get_ip_addr(client_addr, ip_addr);
  strcpy(result, ip_addr);
  strcat(result, " ");
  strcat(result, current_time);
  // @debug
  printf("Log: %s\n", result);
  
  // write_file("log.txt", result);
}
