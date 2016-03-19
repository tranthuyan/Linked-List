// demolinkedlist.cpp : Defines the entry point for the console application.
/* Tôi cam đoa mã nguồn này là do tôi tự thực hiện, không sao chép từ người khác.
Những đoạn mã tham khảo sẽ có chú thích nguồn tham khảo đính kèm.*/

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// khai báo và khởi tạo danh sách liên kết
	LIST l;
	Init(l);
	
	// gọi hàm menu thực hiện các chức năng
	Menu(l);

	//dừng màn hình
	getch();
	return 0;
}