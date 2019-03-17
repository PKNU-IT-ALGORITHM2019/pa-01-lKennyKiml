#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

void DicData();
void fRead(char *fname);
void wordStore(char *line);
void search(char *target);

int find(char *target, int begin, int end);
void search_times(int n);

string word[200000];
string wordClass[200000];
string account[200000];
int index = 0;

int main()
{
	DicData();
}

void DicData()
{
	char text[30];
	while (1) // Q) printf와 cout 사용하는 경우의 차이?
	{
		printf("$ ");
		cin.getline(text, sizeof(text)); // * cin.getline(name, size) : \n 까지 읽기
		char *command = strtok(text, " ");


		if (strcmp(command, "\0") == 0)
			continue;

		else if (strcmp(command, "read") == 0)
		{
			command = strtok(NULL, "\0");
			fRead(command);
		}

		else if (strcmp(command, "size") == 0) // Q)
		{
			cout << index << '\n';
		}

		else if (strcmp(command, "find") == 0)
		{
			command = strtok(NULL, "\0");
			search(command);
		}

		else if (strcmp(command, "exit") == 0)
		{
			break;
		}
	}
}

void fRead(char *fileName)
{
	FILE *fp = fopen(fileName, "r"); // Q) "r", "rt"의 차이?
	char line[10000];

	while (fgets(line, sizeof(line), fp))
	{
		if (fp == NULL)
		{
			cout << "File not found" << endl;
			break;
		}

		if (strcmp(line, "\n") == 0)
			continue;
		wordStore(line);
	}
	fclose(fp);
	cout << "Open file" << endl;
}

void wordStore(char *line)
{
	char *context = NULL;
	char *wTok = strtok_s(line, "(", &context);

	while (wTok != NULL)
	{
		word[index] = wTok;
		word[index] = word[index].substr(0, word[index].length() - 1);

		if (context[0] == ')')
			wordClass[index] = " ";
		else
		{
			wTok = strtok_s(NULL, ")", &context);
			wordClass[index] = wTok;
		}


		if (context[1] == '\0')
			account[index] = " ";
		else
		{
			wTok = strtok_s(NULL, "\0", &context);
			account[index] = wTok;
		}

		index++;
		wTok = strtok(NULL, " ");
	}
}

void search(char *target)
{
	int i = find(target, 0, index - 1);
	char *index_word = (char *)word[i].c_str();
	
	if (_stricmp(index_word, target) != 0)
	{
		cout << "Not found. \n" << word[i] << "(" << wordClass[i] << ")" << account[i] << "No result. \n";
		cout << word[i + 1] << "(" << wordClass[i + 1] << ")" << account[i] << "\n";
	}
	else
		search_times(i);
}

void search_times(int n)
{
	string target_word[30];
	int count = 0;
	int tmp = n;
	target_word[count++] = word[n] + "(" + wordClass[n] + ")" + account[n];
	
	while (1)
	{
		if (n != index && word[n] == word[n + 1])
		{
			target_word[count++] = word[n + 1] + "(" + wordClass[n + 1] + ")" + account[n + 1];
			n--; continue;
		}

		break;
	}

	n = tmp;
	while (1)
	{
		if (n != 0 && word[n] == word[n - 1])
		{
			target_word[count++] = word[n - 1] + "(" + wordClass[n + 1] + ")" + account[n - 1];
			n--; continue;
		}

		break;
	}

	cout << "Found" << count << "times\n";
	for (int i = 0; i < count; i++)
		cout << target_word[i];
}





// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
