// kConverter.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

//To convert the image file to another image file using IrfanView software
void convert(wstring filename, char cwd[FILENAME_MAX], string to_file) {
	string file(filename.begin(), filename.end());
	string ext = file.substr(file.size() - 4);
	string from(cwd);
	from += "\\" + file;
	string to(cwd);
	size_t pos = file.find(ext);
	if (pos != std::string::npos)
		file.replace(pos, ext.length(), "." + to_file);
	to += "\\" + file;
	string command = "i_view64.exe " + from + " /advancedbatch /convert=" + to;
	const char* cmd = command.c_str();
	if (system(cmd) == -1) {
		system("exit");
	}
}

int main() {
	//Local variables
	char cwd[FILENAME_MAX];
	_getcwd(cwd, FILENAME_MAX);
	cout << "Enter the image file extension that you want to convert" << endl;
	string from, to;
	cin >> from;
	cout << "Enter the extension that you want to convert to" << endl;
	cin >> to;
	from  = (string)cwd + "/*." + from;
	wstring file_extension = wstring(from.begin(), from.end());
	WIN32_FIND_DATA FindFileData;
	HANDLE hFindFile;
	LPCWSTR file = file_extension.c_str();
	//Step 1 : FindFirst .X File function
	hFindFile = FindFirstFile(
		file,
		&FindFileData);

	if (INVALID_HANDLE_VALUE == hFindFile)
	{
		cout << "Error in Finding file" << endl;
		cout << "Error - " << GetLastError() << endl;
		return EXIT_SUCCESS;
	}
	else
	{
		cout << "File Found" << endl;
		wcout << "File Name - " << FindFileData.cFileName << endl;
		wstring temp_file = FindFileData.cFileName;
		convert(temp_file, cwd, to);
	}

	//Step 2 : FindNextFile Function(.x file) 
	while (FindNextFile(hFindFile, &FindFileData))
	{
		wcout << "File Name - " << FindFileData.cFileName << endl;
		wstring temp_file = FindFileData.cFileName;
		convert(temp_file, cwd, to);
	}

	//Step 3 : File Close function
	FindClose(hFindFile);
	system("pause");
	return EXIT_SUCCESS;
}