// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <conio.h>

// TODO: reference additional headers your program requires here
// cấu trúc BOOK
struct book
{
	char ID [50];
	char Name [50];
	char Author [50];
	char Year [10];
	char PH [50];
};
typedef book BOOK;

// cấu trúc NODE
struct node
{
	BOOK info;
	struct node*pNext;
};
typedef node NODE;

// cấu trúc LIST
struct list
{
	NODE *pHead;
	NODE *pTail;
};
typedef list LIST;

// khai báo các hàm 
void Menu (LIST);
void contApp(LIST);

int readBook (LIST &);
void saveBook (LIST, int);
void saveBook2 (LIST);

void imBook (BOOK &);
void exBook (BOOK);

void Init (LIST &);
NODE* getNode (BOOK);
void addTail (LIST &, NODE*);
void Input (LIST &);
void Output (LIST);

void swapBook (BOOK &, BOOK &);
void sortYear (LIST);

void delHead (LIST &);
void delBook (LIST &);
void delAll (NODE *&);

void lookID(LIST);
void lookAuthor(LIST);
void lookBook(LIST);