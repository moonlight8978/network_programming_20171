## Bài tập lớn Lập trình mạng - 20171

##### Team Maya - Nhóm 14

### Đề tài 3: HTTP Server

Viết chương trình HTTP Server (HTTP/1.1) thực hiện được ít nhất các công việc sau:

* Tìm hiểu giao thức HTTP
* Xử lý được các lệnh: GET và POST
* Đáp ứng được nhiều kết nối đồng thời
* Thống kê và ghi nhật ký (IP nào kết nối đến, thời gian nào…)
* Ngôn ngữ: C/C++
* Sử dụng TCP Socket


### Định dạng dữ liệu

Là file text `.txt` lưu dữ liệu dưới dạng

> Họ<br>
> Tên<br>
> Năm sinh<br>
> Email

Tương ứng `PERSON` có dạng sau

```c
struct PERSON {
  char last_name[64];
  char first_name[64];
  int year_of_birth;
  char email[64];
}
```
