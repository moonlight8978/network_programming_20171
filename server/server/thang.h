// TODO: Thang
// Viet ham truy van file, ghi file

// Ham truy van file theo cac dieu kien
//
// @param file_name [String] ten file can truy van
// @param params [Array<PARAM>] mang cac dieu kien truy van
// @param total_param [int] so luong params
// @param results [Array<PERSON>] mang ket qua tim duoc
// @return [int] so luong ket qua tim duoc
//
// @example
//	 RESULT results[20]
//   params = [{ name: "Bach" }, { age: 14 }]
//	 int res = query_file("file.txt", params, results)
//   => res: 0 (khong tim thay)
//   => res: 1, results: ["Bach 20 depzaivl@gmail.com"] (tim duoc 1 ket qua)
int query_file(char* file_name, PARAM* params, int total_params, PERSON* results) {
	int total_results = 0;
	results = new PERSON[20];
	//code
	return total_results;
}

// Ham ghi 1 xau vao file
//
// @param file_name [String] ten file can ghi
// @param content [String] du lieu can ghi
// @return [void]
void write_file(char* file_name, char* content) {
	//code
}
