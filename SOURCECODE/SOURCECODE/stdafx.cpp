// stdafx.cpp : source file that includes just the standard includes
// demolinkedlist.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

// hàm đọc file dữ liệu 
int readBook (LIST &l)
{
	FILE *fn = fopen("Data.txt", "rt"); // mở file
	if(fn == NULL) 
		return 0;

	char a[10];
	BOOK s;
	int n = 0; // số lượng sách
	
	for(int i = 0; fgets(a, 10, fn) ; i++) // điều kiện đọc là có dấu xuống dòng
	{
		n++; // cập nhật số lượng sách
		// đọc từng dòng và gán lần lượt vào các thành phần ID, Name, Author, Year, PH của BOOK s
		fgets(s.ID, 50, fn);   
		fgets(s.Name, 50, fn); 
		fgets(s.Author, 50, fn);
		fgets(s.Year, 10, fn);
		fgets(s.PH, 50, fn);

		NODE *p = getNode(s); // tạo node mới với thành phần info là BOOK s
		if(p == NULL)
			return 0;
		else
			addTail(l,p); // thêm node vừa tạo vào đuôi danh sách
	}

	printf("\n\n So luong sach hien co trong thu vien la: %d quyen\n", n);
	// đóng file
	fclose (fn);
	Output(l); // in ra màn hình danh sách mới đọc được
	return n;
}
// hàm ghi tiếp file dữ liệu
void saveBook (LIST l, int n) 
{
	// mở file
	FILE * fn = fopen("Data.txt","a");	 // mở file theo kiểu ghi tiếp

	// duyệt tuần tự danh sách liên kết, đến phần tử cuối từ file ban đầu thì ghi tiếp
	NODE *p = l.pHead; 
	for(int i = 1; i < n + 1; i++) 
		p = p->pNext; 
	
	while(p != NULL) // duyệt tuần tự cho hết danh sách sách mới thêm
	{
		// ghi lần lượt các thành phần ID, Name, Author, Year, PH của từng node mới
		
		fputs("\n\n", fn); // xuống dòng từ file cũ
		fputs(p->info.ID, fn);
		fputs("\n", fn); // mỗi thành phần ghi trên 1 dòng riêng biệt
		fputs(p->info.Name, fn);
		fputs("\n", fn);
		fputs(p->info.Author, fn);
		fputs("\n", fn);
		fputs(p->info.Year, fn);
		fputs("\n", fn);
		fputs(p->info.PH, fn);
		p = p->pNext;
	}
	// đóng file
	fclose (fn);
}

// hàm ghi lại từ đầu file dữ liệu
void saveBook2 (LIST l)
{
	FILE * fn = fopen("Data.txt","wt");	// mở file theo kiểu ghi lại từ đầu

	// duyệt tuần tự từng node, và ghi lần lượt từng thành phần của info vào từng hàng riêng lẻ
	// mỗi thành phần có chứa "\n" rồi nên không cần xuống dòng
	NODE *p = l.pHead;
	while(p != NULL) 
	{
		fputs("\n", fn);
		fputs(p->info.ID, fn);
		fputs(p->info.Name, fn);
		fputs(p->info.Author, fn);
		fputs(p->info.Year, fn);
		fputs(p->info.PH, fn);
		p = p->pNext;
	}
	// đóng file
	fclose (fn);
}

// hàm nhập thông tin 1 quyển sách
void imBook (BOOK &x)
{
	fflush (stdin);
	printf("\n     Nhap ID: ");
	gets(x.ID);

	fflush (stdin);
	printf("     Nhap ten sach: ");
	gets(x.Name);

	fflush (stdin);
	printf("     Nhap ten tac gia: ");
	gets(x.Author);

	fflush (stdin);
	printf("     Nhap nam xuat ban: ");
	gets(x.Year);

	fflush (stdin);
	printf("     Nhap ten nha xuat ban: ");
	gets(x.PH);

}

// hàm xuất thông tin 1 quyển sách
void exBook(BOOK x)
{
	printf("     %s",x.ID);
	printf("\n     %s",x.Name);
	printf("\n     %s",x.Author);
	printf("\n     %s",x.Year);
	printf("\n     %s\n",x.PH);
}

//hàm khởi tạo danh sách rỗng
void Init (LIST &l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}

// hàm tạo 1 NODE BOOK
NODE* getNode (BOOK x)
{
	NODE *p =  new NODE; // xin cấp phát 1 node mới
	if(p == NULL) // cấp phát thất bại thì return NULL
		return NULL;
	p->info = x; // thành phần info là thông tin 1 quyển sách
	p->pNext = NULL; // node chưa gắn vào danh sách nào nên gán thành phần pNext = NULL
	return p;
}

// hàm thêm NODE cuối
void addTail (LIST &l, NODE *p)
{
	if(l.pHead == NULL) // khi danh sách rỗng
		l.pHead = l.pTail = p; // node mới vừa là node đầu vừa là node cuối
	else //ngược lại
	{
		l.pTail->pNext = p; // gắn đuôi node cuối của danh sách cũ vào node mới
		l.pTail = p; // cập nhật lại địa chỉ đuôi danh sách là địa chỉ node mới
	}
}

// hàm tạo một danh sách liên kết
void Input (LIST &l)
{
	int n;
	printf("\n Nhap so luong sach muon them vao:");
	scanf("%d", &n);

	for(int i = 1; i <= n; i++) // thêm bao nhiêu quyển sách mới sẽ chạy bấy nhiêu vòng lặp
	{
		BOOK x;
		imBook(x); // nhập thông tin sách muốn thêm vào
		NODE *p = getNode(x); // khởi tạo node mới với phần info là thông tin vừa nhập
		if(p != NULL) // cấp phát thành công
			addTail(l,p); // thêm node mới vào cuối danh sách.
		
	}
	// in ra màn hình danh sách sau khi thêm
	printf("\n  Danh sach sach hien co trong thu vien la:\n"); 
    Output(l);
}

// hàm xuất ra màn hình danh sách liên kết
void Output (LIST l)
{
	int count = 0; // khởi tạo số thứ tự sách xuất ra màn hình
	NODE *p = l.pHead; // duyệt tuần tự từng node và in ra phần info
	while(p != NULL)
	{   
		count ++;
		printf("\n  %d/\n",count);
		exBook(p->info);
		p = p->pNext;
	}
}

// hàm hoán đổi quyển sách
void swapBook (BOOK &a, BOOK &b)
{
	BOOK x = a;
	a = b;
	b = x;
}

// hàm sắp xếp danh sách, Interchange Sort
void sortYear(LIST l)
{
	for(NODE * p = l.pHead; p; p = p->pNext) // node p chạy từ node đầu đến node kế cuối
		for(NODE * k = p->pNext; k; k = k->pNext) // node k chạy từ node thứ hai đến node cuối
			if(strcmp(p->info.Year, k->info.Year) > 0) // so sánh thông tin năm xuất bản của 2 node liền nhau
				swapBook(p->info,k->info); // đổi chỗ hai quyển sách

	printf("\n Danh sach cac quyen sach theo thu tu nam xuat ban tang dan:\n");
	Output(l); // in ra màn hình danh sách theo thứ tự năm xuất bản tăng dần
}

// xóa node vị trí k
void delBook (LIST &l) 
{
	int k;
	printf("\n Nhap so thu tu sach muon xoa: ");
	scanf("%d", &k);

	if (k == 1) // khi muốn xóa node đầu, hoặc khi danh sách chỉ có 1 node thì đương nhiên xóa node đầu
		delHead(l);

	else 
	{
		NODE *p = l.pHead;

		if (p->pNext == l.pTail) // khi danh sách có 2 node
		{
			NODE *r = p->pNext;
			l.pTail = p;
			l.pTail->pNext = NULL;
			delete r;
		} 

		else // khi danh sách có nhiều hơn 2 node
		{
			NODE *r, *a;
			for(int i = 2; i <= k; i++)
			{
				a = p; // node trước node cần xóa
				r = p->pNext; // node cần xóa
				p = p->pNext; // duyệt tuần tự danh sách liên kết
			}
			a->pNext = r->pNext; // cập nhật để khi xóa node r thì những node sau node r không bị mất đi
			delete r;
		}
	}
	// in ra màn hình danh sách sau khi xóa
	printf("\n  So sach hien co trong thu vien la:\n"); 
    Output(l);
}

// hàm xóa node đầu
void delHead (LIST &l) 
{
	if (l.pHead == NULL) // danh sách lk rỗng
		return;
	else 
	{
		NODE *p = l.pHead;

		if (l.pHead == l.pTail) // danh sách lk chỉ có 1 node
			Init(l);
		else // danh sách lk có nhiều hơn 1 node
			l.pHead = l.pHead->pNext;

		delete p;

	}

}

// hàm xóa hết danh sách
void delAll(NODE* &p) 
{
	NODE *temp;
	while (p != NULL)  // duyệt và xóa tuần tự từng node trong danh sách
	{
		temp = p;
		p = p->pNext;
		delete temp;
	}
	p = NULL; // cập nhật lại danh sách rỗng
}

// tìm kiếm theo ID
void lookID (LIST l)
{
	int i = 0; // số thứ tự sách
	char a[50];

	fflush(stdin);
	printf("\n Nhap ID:");
	gets(a);
	int la = strlen(a); // nối thêm vào chuỗi a ký tự xuống dòng.
	a[la] = '\n';
	a[la+1] = '\0';

	NODE *p = l.pHead; // duyệt tuần tự và so sánh từng thành phần ID có trùng với ID cần tìm
	while(p != NULL)
	{ 
		i++;
		if(strcmp(a, p->info.ID) == 0)
		{
			printf("\n Sach ban muon tim la quyen thu %d\n", i);
			printf("\n");
			exBook(p->info); // nếu trùng thì in ra thông tin và thoát hàm
			return;
		}
		p = p->pNext;
	}
	printf("\n Khong co sach ban can tim trong thu vien."); // không tìm thấy ID nào trùng thì in ra thông báo
}

// đếm số lượng sách của một tác giả
void lookAuthor (LIST l)
{
	char a[50];
	fflush(stdin);
	printf(" Nhap ten tac gia: ");
	gets(a);
	// vì khi đọc Author luôn có dấu
	// xuống dòng. nên gắn thêm "\n" vào chuỗi a để khớp định dạng.
	int la = strlen(a);
	a[la] = '\n';
	a[la+1] = '\0';
	int count = 0;

	NODE *p = l.pHead; // duyệt tuần tự và so sánh từng thành phần Author có trùng với Author cần tìm
	while(p != NULL)
	{ 
		if(strcmp(a, p->info.Author) == 0)
			count ++; // nếu trùng thì cộng thêm 1 lần đếm
		p = p->pNext;
	}
	printf("\n Trong thu vien co tat ca %d quyen sach cua tac gia %s", count, a); // in kết quả

}

// xuất danh sách cùng năm và nhà xuất bản do người dùng nhập
void lookBook (LIST l)
{
	int i = 0, k = 0;
	char a[50], n [10];

	fflush(stdin);
	printf("\n Nhap nam xuat ban:");
	gets(n);
	int ln = strlen(n); // nối thêm vào chuỗi n ký tự xuống dòng.
	n[ln] = '\n';
	n[ln+1] = '\0';

	fflush(stdin);
	printf(" Nhap ten nha xuat ban:");
	gets(a);
	int la = strlen(a); // nối thêm vào chuỗi a ký tự xuống dòng.
	a[la] = '\n';
	a[la+1] = '\0';

	int lx = strlen(l.pTail->info.PH); // nối thêm vào chuỗi Author của phần tử cuối cùng dấu xuống dòng
	l.pTail->info.PH[lx] = '\n';
	l.pTail->info.PH[lx+1] = '\0';

	NODE *p = l.pHead; // // duyệt tuần tự và so sánh từng thành phần Year và PH có trùng với Year và PH cần tìm
	while(p != NULL)
	{ 
		k++;
		if( (strcmp(n,p->info.Year) == 0) && (strcmp(a, p->info.PH) == 0))
		{
			i++;
			printf("\n Sach ban muon tim la quyen thu %d\n", k);
			printf("\n");
			exBook(p->info); // mỗi lần tìm được thì in ra thông tin
		}
		p = p->pNext;
	}
	if(i == 0)
		printf("\n Khong co sach ban can tim trong thu vien."); // không tìm được thì in thông báo
}

// hàm tiếp tục sử dụng ứng dụng
void contApp (LIST l)
{
	char yes[] = "Y";
	char cont [2];
	fflush(stdin);
	printf("\n\n De tiep tuc su dung ung dung nhap Y, nhap phim bat ky (khac Y) de thoat.\n\n Nhap: ");
	gets(cont);
	if(strcmp(cont,yes) == 0) // nhập "Y" sẽ gọi lại hàm Menu và chạy lại từ đầu các chức năng
	{
		// xóa danh sách để khi đọc lại file (khi gọi lại hàm menu) sẽ không ghi tiếp vào danh sách cũ
		delAll(l.pHead); 
		Menu(l);
	}
	else
		printf("\n Cam on ban da su dung ung dung. Hen gap lai !\n"); // nhập một ký tự bất kỳ thì in thông báo xin chào.
}
// hàm menu
void Menu(LIST l)
{
	int n = readBook(l); // số node được tạo sau khi đọc file dữ liệu

	int menu; // chọn chức năng menu
	printf("\n Nhap:\n\n  - 1: de them sach.\n  - 2: de xoa sach.\n  - 3: de xuat danh sach theo thu tu nam xuat ban tang dan.\n  - 4: de tim kiem sach theo ID.\n  - 5: de dem so luong sach trong thu vien cua cung mot tac giac.\n  - 6: de xuat danh sach nhung quyen xuat ban cung mot nam cua mot nha xuat ban.\n Nhap: ");
	scanf("%d", &menu);

	switch(menu)
	{
	case 1: // thêm sách
		{
			Input(l); // thêm sách
			saveBook(l, n); // ghi tiếp file 
			contApp(l); // gọi hàm sử dụng tiếp
			break;
		}
	case 2: // xóa sách
		{   
			delBook(l); // xóa sách
			saveBook2(l); // ghi lại từ đầu
			contApp(l); // gọi hàm sử dụng tiếp
			break;
		}
	case 3: // xuất mảng theo thứ tự
		{
			sortYear(l); // gọi hàm xuất mảng sau khi sắp xếp
			contApp(l); // gọi hàm sử dụng tiếp
			break;
		}
	case 4: // tìm sách theo ID
		{
			lookID(l); // gọi hàm tìm sách theo ID
			contApp(l); // gọi hàm sử dụng tiếp
			break;
		}
	case 5: // đếm số lượng sách của 1 tác giả
		{
			lookAuthor(l); // gọi hàm đếm số sách theo tên tác giả
			contApp(l); // gọi hàm sử dụng tiếp
			break;
		}
	case 6: // xuất danh sách những quyển xuất bản cùng năm YYYY cùng một nhà xuất bản
		{
			lookBook(l); // gọi hàm tìm sách theo yêu cầu trên
			contApp(l); // gọi hàm sử dụng tiếp
			break;
		}
		// trường hợp người dùng nhập 1 số khác 1, 2, 3, 4, 5, 6 thì cho người dùng nhập lại
	default:
		{
			delAll(l.pHead); // xóa danh sách cũ để khi đọc lại file (khi gọi lại hàm menu) sẽ không ghi tiếp vào danh sách cũ
			printf("\n\n\n     BAN DA NHAP SAI HUONG DAN. XIN VUI LONG NHAP LAI: ");
			Menu(l);
		}
	}
}