#include "pch.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <iomanip>
#include <tchar.h>
#include <io.h>
#include <direct.h>

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
const short RED = 4;
const short LIGHT_GRAY = 7;
const short WHITE = 15;
FILE *pFile;

//SetConsoleTextAttribute(hConsole, (WORD)((/*фон*/BLACK << 4) |/*текст*/ BLUE));

using namespace std;

struct ObjList
{
	int index;
	WCHAR objName[MAX_PATH];
	ObjList* prev;
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

void printScreen(ObjList obj, wstring disk, wstring dir, short ptr)
{	
	system("mode con cols=224");
	system("cls");
	setcur(0, 0);
	hidecursor();
	ObjList* p = &obj;
	wstring nameDisk, nameDir, path;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	nameDisk = disk;
	nameDir = dir;
	int cur = 0;
	while (ptr > cur + 115)
	{
		while (p->index != cur + 116)
			p = p->next;
		cur += 115;
	}

	path = nameDisk + L":" + L"\\" + nameDir;
	{
		SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | BLUE));
		cout << '\xC9';
		for (short i = 0; i < 40; i++)
			cout << "\xCD";
		SetConsoleTextAttribute(hConsole, (WORD)((BLUE << 4) | LIGHT_GRAY));
		wcout << path;
		for (int i = 30 - size(path); i > 0; i--)
			cout << " ";
		if (size(path) > 30)
		{
			setcur(67, 0);
			cout << "..";
			SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | BLUE));
			cout << "\xCD\xCD";
		}
		SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | BLUE));
		for (short i = 0; i < 40; i++)
			cout << "\xCD";
		cout << '\xBB';
		cout << '\xC9';
		for (short i = 0; i < 110; i++)
			cout << "\xCD";
		cout << '\xBB' << endl;
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
			
			wcout << left << setw(110) << p->objName;
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
				SetConsoleTextAttribute(hConsole, (WORD)((LIGHT_GRAY << 4) | BLACK));
			else
				SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | WHITE));
			setlocale(LC_ALL, "Russian");
			wcout << left << setw(110) << p->objName;
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

	SetConsoleTextAttribute(hConsole, (WORD)((BLUE << 4) | LIGHT_GRAY));
	setcur(1, 59);
	cout << "1 -- Rename";
	setcur(13, 59);
	cout << "2 -- Create folder";
	setcur(32, 59);
	cout << "3 -- Copy Folder";
	setcur(49, 59);
	cout << "4 -- Delete Folder";
	setcur(68, 59);
	cout << "5 -- Create File";
	setcur(85, 59);
	cout << "6 -- Copy File";
	setcur(100, 59);
	cout << "7 -- Delete File";
	setcur(117, 59);
	cout << "8 -- View File";
	setcur(132, 59);
	cout << "9 -- Open";
	setcur(142, 59);
	cout << "0 -- Change Drive";
	SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | BLUE));
}

bool isGoodDir(ObjList obj, wstring disk, wstring dir)
{
	ObjList* p;
	WIN32_FIND_DATAW wfd;
	wstring nameDisk, nameDir, path;
	short i = 0;
	wchar_t ansi[400];
	nameDisk = disk;
	nameDir = dir;
	path = nameDisk + L":" + L"\\" + nameDir;
	char sPath[260];
	while (path[i] != 0)
	{
		sPath[i] = path[i];
		i++;
	}
	sPath[i] = 0;

	int num = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)sPath, -1, ansi, 400);
	LPCTSTR lpDir = ansi;
	HANDLE const hFind = FindFirstFileW(lpDir, &wfd);
	if (INVALID_HANDLE_VALUE != hFind)
		return true;
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | RED));
		setcur(113, 0);
		cout << "Error! Can't open this folder!";
		_getch();
		return false;
	}
}

ObjList objNames(ObjList obj, wstring disk, wstring dir)
{
	ObjList* p;
	WIN32_FIND_DATAW wfd;
	wstring nameDisk, nameDir, path;
	
	wchar_t ansi[400];
	nameDisk = disk;
	nameDir = dir;
	path = nameDisk + L":" + L"\\" + nameDir + L"*";
	short i = 0;
	char tPath[260];
	while (path[i] != 0)
	{
		tPath[i] = path[i];
		i++;
	}
	tPath[i] = path[i];

	int num = MultiByteToWideChar(CP_UTF8, 0, tPath, -1, ansi, 400);
	LPCTSTR lpDir = ansi;
	HANDLE const hFind = FindFirstFileW(lpDir, &wfd);
	
	p = &obj;
	while (wfd.cFileName[i - 1] != 0)
	{
		p->objName[i] = wfd.cFileName[i];
		i++;
	}
	if (p->next != NULL)
	{
		while (p->next->next != NULL)
			p = p->next;
		while (p->index != 0)
		{
			delete p->next;
			p = p->prev;
		}
	}
	p->next= NULL;
	if (INVALID_HANDLE_VALUE != hFind)
	{
		p->next = new ObjList;
		while (NULL != FindNextFileW(hFind, &wfd))
		{
			i = 0;
			while (wfd.cFileName[i-1] != 0)
			{
				p->objName[i] = wfd.cFileName[i];
				i++;
			}

			p->next = new ObjList;
			p->next->next = NULL;
			p->next->index = p->index + 1;
			p->next->prev = p;
			p = p->next;
			
		} 
		p->next = NULL;
		FindClose(hFind);
	}
	return obj;
}

wstring upperDir(wstring dir)
{
	short i = 0;
	short a = dir.rfind(L"\\"), b = 0;
	while (dir[i] != L'*')
	{
		if (dir[i] == L'\\')
		{
			a = b;
			b = i;
		}
		i++;
	}
	dir = dir.substr(0, a);
	dir = dir + L"\\*";
	return dir;
}

wstring newDir(ObjList NewDir, wstring dir, short ptr)
{
	ObjList* p = &NewDir;
	while (p->index != ptr)
		p = p->next;
	if ((p->objName[0] == L'.') && (p->objName[1] == L'.'))
	{
		dir = upperDir(dir);
		return dir;
	}
	wstring temp;
	dir.erase(dir.rfind(L"*")+1, 250);
	temp = temp + p->objName + L"\\";
	dir = dir.insert(dir.rfind(L"*"), temp);
	return dir;
}

void renameObj(wstring disk, wstring dir)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	wstring path, newName;
	short i = 0;
	short a = dir.rfind(L"\\"), b = 0;
	while (dir[i] != L'*')
	{
		if (dir[i] == L'\\')
			a = i;
		i++;
	}
	i = 0;
	dir[a] = 0;
	path = disk + L":\\" + dir;

	setcur(113, 0);
	SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | LIGHT_GRAY));
	cout << "New name of file: D:\\                                                                                         ";
	setcur(134, 0);
	getline(wcin, newName);

	newName = L"D:\\" + newName;
	char tPath[260], tNewName[260];
	i = 0;
	while (path[i] != 0)
		tPath[i++] = path[i];
	tPath[i] = 0;
	i = 0;
	while (newName[i] != 0)
		tNewName[i++] = newName[i];
	tNewName[i] = 0;

	int c = rename(tPath, tNewName);
	setcur(113, 0);
	if (c)
		cout << "Err";
	else
		cout << "OK";
}

void createFolder()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	wstring path, newPath;
	short i = 0;
	setcur(113, 0);
	SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | LIGHT_GRAY));
	cout << "Path to folder: D:\\                                                                                           ";
	setcur(132, 0);
	getline(wcin, newPath);
	newPath = L"D:\\" + newPath;
	
	i = 0;
	TCHAR tNew[260];
	while (newPath[i] != 0)
	{
		tNew[i] = newPath[i];
		i++;
	}
	tNew[i] = 0;

	if (_tmkdir(tNew) != 0) {
		return;
	}
}

void copyFolder(wstring disk, wstring dir)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	wstring path, newPath;
	short i = 0;
	short a = dir.rfind(L"\\"), b = 0;

	while (dir[i] != L'*')
	{
		if (dir[i] == L'\\')
			a = i;
		i++;
	}
	i = 0;
	dir[a + 2] = 0;
	path = disk + L":\\" + dir + L"*";
	path[path.rfind(L"*")] = 0;

	setcur(113, 0);
	SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | LIGHT_GRAY));
	cout << "Path to copy of folder: D:\\                                                                                     ";
	setcur(140, 0);
	getline(wcin, newPath);
	newPath = L"D:\\" + newPath;
	
	TCHAR tNew[260];
	while (newPath[i] != 0)
	{
		tNew[i] = newPath[i];
		i++;
	}
	tNew[i] = 0;
	TCHAR copy[260] = L"xcopy ";
	a = 0;
	i = 6;
	while (path[a] != 0)
	{
		if ((path[a] == L'\\') && (path[a + 1] == L'\\'))
			a++;
		copy[i] = path[a];
		i++;
		a++;
	}
	if (copy[i - 1] == L'*')
		i -= 2;
	copy[i] = L' ';
	a = 0;
	i++;
	while (newPath[a] != 0)
	{
		copy[i] = newPath[a];
		i++;
		a++;
	}
	copy[i] = L' ';
	copy[++i] = L'/';
	copy[++i] = L'I';
	copy[++i] = L' ';
	copy[++i] = L'/';
	copy[++i] = L'E';

	_tmkdir(tNew);
		//return;*/

	char sCopy[256];
	i = 0;
	while (copy[i] != 0)
	{
		sCopy[i] = copy[i];
		i++;
	}
	sCopy[i] = 0;
	//if ((FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(copy)) == FILE_ATTRIBUTE_DIRECTORY)
		system(sCopy);
}

void deleteFolder(wstring disk, wstring dir)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	wstring path, newPath;
	short i = 0;
	short a = dir.rfind(L"\\"), b = 0;

	while (dir[i] != L'*')
	{
		if (dir[i] == L'\\')
			a = i;
		i++;
	}
	i = 0;
	dir[a + 2] = 0;
	path = disk + L":\\" + dir + L"*";
	path[path.rfind(L"*")] = 0;

	TCHAR tNew[260];
	while (newPath[i] != 0)
	{
		tNew[i] = newPath[i];
		i++;
	}
	tNew[i] = 0;
	TCHAR copy[260] = L"RMDIR /S /Q ";
	char sPath[260];
	a = 0;
	i = 12;
	while (path[a] != 0)
	{
		if ((path[a] == L'\\') && (path[a + 1] == L'\\'))
			a++;
		sPath[a] = copy[i] = path[a];
		i++;
		a++;
	}
	if (copy[i - 1] == L'*')
		i -= 2;
	copy[i] = L' ';
	a = 0;
	i++;

	char sCopy[256];
	i = 0;
	while (copy[i + 1] != L'*')
	{
		sCopy[i] = copy[i];
		i++;
	}
	sCopy[i] = 0;

	//if ((FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(copy)) == FILE_ATTRIBUTE_DIRECTORY)
	system(sCopy);
	system(sCopy);
	//system(sCopy);
}

void createFile()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	wstring path, newPath;
	short i = 0;
	short a =0, b = 0;

	setcur(113, 0);
	SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | LIGHT_GRAY));
	cout << "Name of file: D:\\                                                                                             ";
	setcur(130, 0);
	getline(wcin, newPath);
	newPath = L"D:\\" + newPath;

	char sPath[256];
	i = 0;
	while (newPath[i] != 0)
	{
		sPath[i] = newPath[i];
		i++;
	}
	sPath[i] = 0;
	pFile = fopen(sPath, "w");
	if (pFile != NULL)
		fclose(pFile);
}

void copyFile(wstring disk, wstring dir)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	wstring path, newPath;
	short i = 0;
	short a = dir.rfind(L"\\"), b = 0;

	while (dir[i] != L'*')
	{
		if (dir[i] == L'\\')
			a = i;
		i++;
	}
	i = 0;
	dir[a + 2] = 0;
	path = disk + L":\\" + dir;
	path[path.rfind(L"*")] = 0;

	setcur(113, 0);
	SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | LIGHT_GRAY));
	cout << "Path to copy of file: D:\\                                                                                     ";
	setcur(138, 0);
	getline(wcin, newPath);
	newPath = L"D:\\" + newPath;
	
	TCHAR tNew[260];
	while (newPath[i] != 0)
	{
		tNew[i] = newPath[i];
		i++;
	}
	tNew[i] = 0;
	_tmkdir(tNew);
	TCHAR copy[260] = L"copy /Y ";
	a = 0;
	i = 8;
	while (path[a] != 0)
	{
		copy[i] = path[a];
		i++;
		a++;
	}
	
	copy[i-1] = L' ';
	a = 0;
	while (newPath[a] != 0)
	{
		copy[i] = newPath[a];
		i++;
		a++;
	}
	copy[i] = 0;

	char sCopy[256];
	i = 0;
	while (copy[i] != 0)
	{
		sCopy[i] = copy[i];
		i++;
	}
	sCopy[i] = 0;

	//if ((FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(path)) != FILE_ATTRIBUTE_DIRECTORY)
	system(sCopy);
}

void deleteFile(wstring disk, wstring dir)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	wstring path, newPath;
	short i = 0;
	short a = dir.rfind(L"\\"), b = 0;

	while (dir[i] != L'*')
	{
		if (dir[i] == L'\\')
			a = i;
		i++;
	}
	i = 0;
	dir[a + 2] = 0;
	path = disk + L":\\" + dir;
	path[path.rfind(L"*")] = 0;

	TCHAR tNew[260];
	while (newPath[i] != 0)
	{
		tNew[i] = newPath[i];
		i++;
	}
	tNew[i] = 0;
	TCHAR copy[260] = L"erase ";
	a = 0;
	i = 6;
	while (path[a] != 0)
	{
		if ((path[a] == L'\\') && (path[a + 1] == L'\\'))
			a++;
		copy[i] = path[a];
		i++;
		a++;
	}
	while (path[a] != 0)
	{
		copy[i] = path[a];
		i++;
		a++;
	}

	copy[i - 1] = 0;

	char sCopy[256];
	i = 0;
	while (copy[i] != 0)
	{
		sCopy[i] = copy[i];
		i++;
	}
	sCopy[i] = 0;

	//if ((FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(copy)) != FILE_ATTRIBUTE_DIRECTORY)
		system(sCopy);
}

void viewFile(wstring disk, wstring dir)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	TCHAR ps[FILENAME_MAX];
	TCHAR ds[FILENAME_MAX];
	long fp;
	_tfinddata_t fi;
	char buff[260];

	wstring nameDisk, nameDir, path;
	short i = 0;
	char dPath[260];
	
	nameDisk = disk;
	nameDir = dir;
	path = nameDisk + L":" + L"\\" + nameDir;
	while (path[i] != 0)
		dPath[i++] = path[i];
	dPath[i - 2] = dPath[i - 1] = 0;
	const short N = 256;
	char S;


	ifstream f(dPath);
	//i = 0;
	if (!f.is_open())
		return;
	system("color 70");
	setlocale(LC_ALL, "Russian");
	char buf[200];
	do
	{
		i++;
		f.read(buf, sizeof(buf));
		cout.write(buf, f.gcount());
	} while (f);
	f.close();
	SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | BLUE));
	setlocale(LC_ALL, "C");
	_getch();
}

void openObj(wstring disk, wstring dir)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	wstring path, newPath;
	short i = 0;
	short a = dir.rfind(L"\\"), b = 0;

	while (dir[i] != L'*')
	{
		if (dir[i] == L'\\')
			a = i;
		i++;
	}
	i = 0;
	dir[a + 2] = 0;
	path = disk + L":\\" + dir;
	if (path.rfind(L'.') == wstring::npos)
		path = L"explorer " + path;
	else
		path[path.rfind(L"*")-1] = 0;

	i = 0;

	TCHAR tNew[260];
	while (newPath[i] != 0)
	{
		tNew[i] = newPath[i];
		i++;
	}
	tNew[i] = 0;
	TCHAR copy[260];
	a = 0;
	i = 0;
	while (path[a] != 0)
	{
		copy[i] = path[a];
		i++;
		a++;
	}
	if(path.rfind(L'.') == wstring::npos)
	if (copy[i - 1] == L'*')
		i-=2;
	copy[i] = 0;
	a = 0;
	i++;

	char sCopy[256];
	i = 0;
	while (copy[i] != 0)
	{
		sCopy[i] = copy[i];
		i++;
	}
	sCopy[i] = 0;

	system(sCopy);
}

wstring changeDrive(wstring disk)
{
	wstring temp = disk;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	TCHAR buf[50];
	int sz = GetLogicalDriveStrings(sizeof(buf), (LPWSTR)buf);
	if (sz > 0)
	{
		short i = 0;
		setcur(113, 0);
		SetConsoleTextAttribute(hConsole, (WORD)((BLACK << 4) | LIGHT_GRAY));
		while ((buf[i] != 0) || (buf[i + 1] != 0))
		{
			if (buf[i] != 0)
				wcout << buf[i];
			else
				cout << " ";
			i++;
		}
		cout << " |New drive:                                                                                       ";
		
		setcur(136, 0);
		getline(wcin, disk);
		i = 0;
		while ((buf[i] != 0) || (buf[i + 1] != 0))
		{
			if (buf[i] == disk[0])
				return disk = disk[0];
			i++;
		}
		return temp;
	}
	else
	{
		setcur(113, 0);
		DWORD dwError = GetLastError();
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, dwError, 0, buf, sizeof(buf), 0);
		printf("%s\n", buf);

	}
	return disk = disk[0];
}

int main()
{
	ObjList head;
	ObjList* p = &head;
	short choose = 0, tempChoose = 0, arrowControl = 0;
	head.index = 0;
	head.prev = NULL;
	head.next = NULL;
	system("mode con cols=224");
	wstring disk = L"D";
	wstring dir = L"*";
	system("color 08");

	head = objNames(head, disk, dir);
	printScreen(head, disk, dir, arrowControl);
	while(choose != ESC_KEY)
	{
		choose = _getch();
		if (choose == SPEC_KEY)
			tempChoose = _getch();
		
		switch (choose)
		{
			case ENTER_KEY:
				if (isGoodDir(head, disk, newDir(head, dir, arrowControl)))
				{
					head = objNames(head, disk, dir = newDir(head, dir, arrowControl));
					arrowControl = 0;
					choose = 0;
					tempChoose = 0;
				}
				break;
			case NUM_1_KEY:
				{
					renameObj(disk, newDir(head, dir, arrowControl));
					head = objNames(head, disk, dir);
					arrowControl = 0;
					choose = 0;
					tempChoose = 0;
				}
				break;
			case NUM_2_KEY:
				{
					createFolder();
					head = objNames(head, disk, dir);
					arrowControl = 0;
					choose = 0;
					tempChoose = 0;
				}
				break;
			case NUM_3_KEY:
				{
					copyFolder(disk, newDir(head, dir, arrowControl));
					head = objNames(head, disk, dir);
					arrowControl = 0;
					choose = 0;
					tempChoose = 0; 
				}
				break;
			case NUM_4_KEY:
				{
					deleteFolder(disk, newDir(head, dir, arrowControl));
					head = objNames(head, disk, dir);
					arrowControl = 0;
					choose = 0;
					tempChoose = 0; 
				}
				break;
			case NUM_5_KEY:
				{
					createFile();
					head = objNames(head, disk, dir);
					arrowControl = 0;
					choose = 0;
					tempChoose = 0;
				}
				break;
			case NUM_6_KEY:
				{
					copyFile(disk, newDir(head, dir, arrowControl));
					head = objNames(head, disk, dir);
					arrowControl = 0;
					choose = 0;
					tempChoose = 0;
				}
				break;
			case NUM_7_KEY:
				{
					deleteFile(disk, newDir(head, dir, arrowControl));
					head = objNames(head, disk, dir);
					arrowControl = 0;
					choose = 0;
					tempChoose = 0;
					break;
				}
			case NUM_8_KEY:
				viewFile(disk, newDir(head, dir, arrowControl));
				break;
			case NUM_9_KEY:
				openObj(disk, newDir(head, dir, arrowControl));
				break;
			case NUM_0_KEY:
				{
					disk = changeDrive(disk);
					dir = L"*";
					head = objNames(head, disk, dir);
					arrowControl = 0;
					choose = 0;
					tempChoose = 0;
				}
				break;
		}
		arrowControl = menu(choose, tempChoose, arrowControl, objCounter(head));
		printScreen(head, disk, dir, arrowControl);
	}
	return 0;
}
