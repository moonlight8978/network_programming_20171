// TODO: Thang
// Viet ham truy van file, ghi file

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
	//code
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
//   write_file("log.txt", "cccccc")
//   => "/log.txt": (sai)
//     aaaaaaaaaa
//     bbbbbbbbbbcccccc
//   => "/log.txt": (dung)
//     aaaaaaaaaa
//     bbbbbbbbbb
//     cccccc
void write_file(char* file_name, char* content) {
	//code
}
