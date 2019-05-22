#include "pch.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <windows.h>

using namespace std;

const short SPEC_KEY = 224;
const short UP_ARROW_KEY = 72;
const short DOWN_ARROW_KEY = 80;
const short LEFT_ARROW_KEY = 75;
const short RIGHT_ARROW_KEY = 77;
const short ENTER_KEY = 13;
const short ESC_KEY = 27;
const short SPACE_KEY = 32;
const short BACKSPACE_KEY = 8;
const short NUM_0_KEY = 48;
const short NUM_1_KEY = 49;
const short NUM_2_KEY = 50;
const short NUM_3_KEY = 51;
const short NUM_4_KEY = 52;
const short NUM_5_KEY = 53;
const short NUM_6_KEY = 54;
const short NUM_7_KEY = 55;
const short NUM_8_KEY = 56;
const short NUM_9_KEY = 57;
const short BLACK = 0;
const short BLUE = 1;
const short LIGHT_GRAY = 7;
const short WHITE = 15;

using namespace std;

struct ObjList
{
	int index;
	WCHAR objName[MAX_PATH];
	ObjList* next;
};

void setcur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

short objCounter(ObjList List)
{
	ObjList *p;
	short counter = 0;
	p = &List;
	while (p != NULL)
	{
		p = p->next;
		counter++;
	}
	counter-=2;
	return counter;
}

short int menu(short int num1, short int num2, short int arrow, short counter)
{
	if (num1 == SPEC_KEY)
	{
		if (num2 == UP_ARROW_KEY)
		{
			if (arrow > 0)
				arrow--;
		}
		else if ((num2 == RIGHT_ARROW_KEY) && (counter > 58))
		{
			if (counter < arrow + 58)
				arrow = counter;
			arrow += 58;
		}
		else if ((num2 == LEFT_ARROW_KEY) && (arrow > 58))
		{
			arrow -= 58;
		} else if (num2 == DOWN_ARROW_KEY)
		{
			if (arrow < counter)
				arrow++;
		}
		else
			return arrow;
	}
	return arrow;
}

void printScreen(ObjList obj, char disk, char dir, short ptr)
{
	//system("cls");
	
	setcur(0, 0);
	hidecursor();
	ObjList* p = &obj;
	string nameDisk, nameDir, path;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	nameDisk = disk;
	nameDir = dir;
	path = nameDisk + ":" + "\\" + nameDir;
	{
		SetConsoleTextAttribute(hConsole, (WORD)((/*фон*/BLACK << 4) |/*текст*/ BLUE));
		cout << '\xC9';
		for (short i = 0; i < 40; i++)
			cout << "\xCD";
		SetConsoleTextAttribute(hConsole, (WORD)((BLUE << 4) | LIGHT_GRAY));
		cout << path;
		for (int i = 30 - size(path); i > 0; i--)
			cout << " ";
		if (size(path) > 30)
		{
			setcur(67, 0);
			cout << "..";
		}
		SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | BLUE));
		for (short i = 0; i < 40; i++)
			cout << "\xCD";
		cout << '\xBB';
		cout << '\xC9';
		for (short i = 0; i < 40; i++)
			cout << "\xCD";
		SetConsoleTextAttribute(hConsole, (WORD)((BLUE << 4) | LIGHT_GRAY));
		cout << path;
		for (int i = 30 - size(path); i > 0; i--)
			cout << " ";
		if (size(path) > 30)
		{
			setcur(67, 0);
			cout << "..";
		}
		SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | BLUE));
		for (short i = 0; i < 40; i++)
			cout << "\xCD";
		cout << '\xBB';
	}
	SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | BLUE));
	for (int i = 0; i < 58; i++)
	{
		cout << "\xBA";
		if (p != NULL)
		{
			if (ptr == p->index)
				SetConsoleTextAttribute(hConsole, (WORD)((LIGHT_GRAY << 4) | BLACK));
			else
				SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | WHITE));
			setlocale(LC_ALL, "Russian");
			wcout << p->objName;
			wcout.clear();
			p = p->next;
			setlocale(LC_ALL, "C");
		}
		else
			for (int i = 0; i < 110; i++)
				cout << " ";
		SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | BLUE));
		cout << endl;
	}
	for (int i = 0; i < 58; i++)
	{
		setcur(111, i + 1);
		cout << "\xBA\xBA";
		if (p != NULL)
		{
			if (ptr == p->index)
				SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | LIGHT_GRAY));
			else
				SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | WHITE));
			setlocale(LC_ALL, "Russian");
			wcout << p->objName;
			wcout.clear();
			setlocale(LC_ALL, "C");
			p = p->next;
		}
		else
			for (int i = 0; i < 110; i++)
				cout << " ";
		SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | BLUE));
	}
	for (int i = 0; i < 58; i++)
	{
		setcur(223, i + 1);
		cout << "\xBA";
	}
	cout << "\xC8";
	for (int i = 0; i < 110; i++)
		cout << "\xCD";
	cout << "\xBC\xC8";
	for (int i = 0; i < 110; i++)
		cout << "\xCD";
	cout << "\xBC";
}

ObjList objNames(ObjList obj, char disk, char dir)
{
	//WIN32_FIND_DATAW wfd;
	ObjList* p;

	
	//HANDLE hFind;
	WIN32_FIND_DATAW wfd; //WIN32_FIND_DATA find_data;
	string nameDisk, nameDir, path;
	wchar_t ansi[400];
	nameDisk = disk;
	nameDir = dir;
	path = nameDisk + ":" + "\\" + nameDir + "*";

	int num = MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, ansi, 400);
	LPCTSTR lpDir = ansi;
	//hFind = FindFirstFile(lpDir, &find_data);


	HANDLE const hFind = FindFirstFileW(lpDir, &wfd);
	short i = 0;
	p = &obj;
	while (wfd.cFileName[i - 1] != 0)
	{
		p->objName[i] = wfd.cFileName[i];
		i++;
	}

	p->next= NULL;
	//setlocale(LC_ALL, "");
	

	if (INVALID_HANDLE_VALUE != hFind)
	{
		p->next - new ObjList;
		while (NULL != FindNextFileW(hFind, &wfd))
		{
			short i = 0;
			//wcout << &wfd.cFileName[0] << endl;
			while (wfd.cFileName[i-1] != 0)
			{
				p->objName[i] = wfd.cFileName[i];
				i++;
			}

			p->next = new ObjList;
			p->next->next = NULL;
			p->next->index = p->index + 1;
			p = p->next;
			
		} 
		p->next = NULL;
		FindClose(hFind);
	}
	return obj;
}

int main()
{
	ObjList head;
	ObjList* p = &head;
	short choose = 0, tempChoose = 0, arrowControl = 0;
	head.index = 0;
	head.next = NULL;
	system("mode con cols=224 lines=60");
	char disk = 'C';
	char dir = '*';

	system("color 08");

	head = objNames(head, 'C', '*');
	printScreen(head, 'C', '*', arrowControl);
	while(choose != ESC_KEY)
	{
		do
		{
			choose = _getch();
			if (choose == SPEC_KEY)
				tempChoose = _getch();
		} while ((choose != ESC_KEY) && (choose != SPEC_KEY) && (choose != ENTER_KEY));
		/*if (choose == ENTER_KEY)
			head = head = objNames(head, 'C' + , '*');*/
		arrowControl = menu(choose, tempChoose, arrowControl, objCounter(head));
		printScreen(head, 'C', '*', arrowControl);
	}


	return 0;
}