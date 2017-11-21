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
  //code
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
  //code
}

// Ghi nhat ky, goi den `#get_current_time`, `#get_ip_addr` de lay ket qua,
//   noi xau lai, roi ghi vao file log.txt
//
// @param client_addr [SOCKADDR_IN] struct dia chi nguoi dung can phan giai
// @return [void]
//
// @example
//   log_request(client_addr)
//   => "log.txt": "2017/11/21 10:25AM 127.0.0.1"
void log_request(SOCKADDR_IN& client_addr) {
  char current_time[128], ip_addr[128], result[256];

  get_current_time(current_time);
  get_ip_addr(client_addr, ip_addr);
  strcat(result, current_time);
  strcat(result, ip_addr);
  
  // ghi result vao file log.txt
  //code
}
