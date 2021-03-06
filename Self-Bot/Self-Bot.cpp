// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <processthreadsapi.h>
#include <winnt.h>
#include <shellapi.h>
#include <sstream>
#include <vector>
#include <time.h> 
#include <iterator>

using namespace std; // using namespace called std. without this, you will have to use std::

void DisplayError(LPCTSTR errorDesc, DWORD errorCode)
{
	TCHAR errorMessage[1024] = TEXT("");

	DWORD flags = FORMAT_MESSAGE_FROM_SYSTEM
		| FORMAT_MESSAGE_IGNORE_INSERTS
		| FORMAT_MESSAGE_MAX_WIDTH_MASK;

	FormatMessage(flags,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		errorMessage,
		sizeof(errorMessage) / sizeof(TCHAR),
		NULL);
	wcerr << L"Error : " << errorDesc << endl;
	wcerr << L"Code    = " << errorCode << endl;
	wcerr << L"Message = " << errorMessage << endl;

}

template<typename Out>
void split(const std::string &s, char delim, Out result)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

#define MST (-7)
#define UTC (0)
#define CCT (+8)

int main()
{
	cout << "Welcome" << endl;
	string Answers;// varible 
	while (1)
	{
		cout << "How May I Help You Today?" << endl; // console out
		cout << "> "; // Extra

					  // get line gets the whole line. Just now, it was getting only the first word,
		getline(cin, Answers); // varible to store answers

		std::vector<std::string> x = split(Answers, ' ');

		std::transform(Answers.begin(), Answers.end(), Answers.begin(), ::tolower); // makes it lower case
		if (x[0] == "t")
		{
			cout << endl;
			if (x[1] == "china")
			{
				time_t rawtime;
				struct tm * ptm;

				time(&rawtime);

				ptm = gmtime(&rawtime);

				printf("Beijing (China) :     %2d:%02d\n", (ptm->tm_hour + CCT) % 24, ptm->tm_min);
				Sleep(5000);
			}
			else if (x[1] == "iceland")
			{
				time_t rawtime;
				struct tm * ptm;

				time(&rawtime);

				ptm = gmtime(&rawtime);

				printf("Reykjavik (Iceland) : %2d:%02d\n", (ptm->tm_hour + UTC) % 24, ptm->tm_min);
			}
			else if(x[1] == "us")
			{
				time_t rawtime;
				struct tm * ptm;

				time(&rawtime);

				ptm = gmtime(&rawtime);

				printf("Phoenix, AZ (U.S.) :  %2d:%02d\n", (ptm->tm_hour + MST) % 24, ptm->tm_min);
			}
			else
			{
				time_t rawtime;
				struct tm * timeinfo;

				time(&rawtime);
				timeinfo = localtime(&rawtime);
				printf("%s", asctime(timeinfo));

			}
			Sleep(5000);
		}
		if (x[0] == "o")
		{
			if (x[1] == "discord")
			{
				STARTUPINFO StartupInfo = { sizeof(StartupInfo) };
				PROCESS_INFORMATION ProcessInfo;
				ZeroMemory(&StartupInfo, sizeof(StartupInfo));
				ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
				if (!CreateProcess(L"C:\\Users\\user\\AppData\\Local\\Discord\\app-0.0.299\\Discord.exe", L"C:\Users\user\AppData\Local\Discord\Update.exe --processStart Discord.exe", NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo)
					)
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					cout << "Program Opened!" << endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "ac")
			{
				STARTUPINFO StartupInfo = { sizeof(StartupInfo) };
				PROCESS_INFORMATION ProcessInfo;
				ZeroMemory(&StartupInfo, sizeof(StartupInfo));
				ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
				if (!CreateProcess(L"C:\\Users\\user\\Desktop\\Content Manager.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo)
					)
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					cout << "Program Opened!" << endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "anime")
			{
				if (!ShellExecute(0, 0, L"http://kissanime.ru/", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					cout << "Website Launched" << endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "github")
			{
				if (x[2] == "")
				{
					if (!ShellExecute(0, 0, L"https://github.com/SagaanTheEpic", 0, 0, SW_SHOW)) // shell code 
					{
						DWORD errorCode = GetLastError();
						DisplayError(TEXT("Unable to execute."), errorCode);
					}
					else
					{
						cout << "Website Launched" << endl;
					}
					Sleep(3000);
				}
				else
				{
					string Link = "https://github.com/" + x[2];

					std::wstring stemp = s2ws(Link);
					LPCWSTR LinkFinal = stemp.c_str();
					if (!ShellExecute(0, 0, LinkFinal, 0, 0, SW_SHOW)) // shell code 
					{
						DWORD errorCode = GetLastError();
						DisplayError(TEXT("Unable to execute."), errorCode);
					}
					else
					{
						cout << "Website Launched" << endl;
					}
					Sleep(3000);
				}
			}
			else if (x[1] == "youtube")
			{
				if (x[2] == "")
				{
					if (!ShellExecute(0, 0, L"https://www.youtube.com/", 0, 0, SW_SHOW)) // shell code 
					{
						DWORD errorCode = GetLastError();
						DisplayError(TEXT("Unable to execute."), errorCode);
					}
					else
					{
						cout << "Website Launched" << endl;
					}
					Sleep(3000);
				}
				else
				{
					string Link = "https://www.youtube.com/user/" + x[2] + "/videos";

					std::wstring stemp = s2ws(Link);
					LPCWSTR LinkFinal = stemp.c_str();
					if (!ShellExecute(0, 0, LinkFinal, 0, 0, SW_SHOW)) // shell code 
					{
						DWORD errorCode = GetLastError();
						DisplayError(TEXT("Unable to execute."), errorCode);
					}
					else
					{
						cout << "Website Launched" << endl;
					}
					Sleep(3000);
				}
			}
			else if (x[1] == "uc")
			{
				if (!ShellExecute(0, 0, L"https://www.unknowncheats.me/forum/index.php", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					cout << "Website Launched" << endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "music")
			{
				//C:\Users\user\AppData\Roaming\Spotify
				STARTUPINFO StartupInfo = { sizeof(StartupInfo) };
				PROCESS_INFORMATION ProcessInfo;
				ZeroMemory(&StartupInfo, sizeof(StartupInfo));
				ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
				if (!CreateProcess(L"C:\\Users\\user\\AppData\\Roaming\\Spotify\\Spotify.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo)
					)
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					cout << "Program Opened!" << endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "steam")
			{
				//C:\Users\user\AppData\Roaming\Spotify
				STARTUPINFO StartupInfo = { sizeof(StartupInfo) };
				PROCESS_INFORMATION ProcessInfo;
				ZeroMemory(&StartupInfo, sizeof(StartupInfo));
				ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
				if (!CreateProcess(L"C:\\Program Files (x86)\\Steam\\Steam.exe", NULL, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo)
					)
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					cout << "Program Opened!" << endl;
				}
				Sleep(3000);
			}
			else if (x[1] == "setup")
			{
				if (!ShellExecute(0, 0, L"https://www.unknowncheats.me/forum/index.php", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else if (!ShellExecute(0, 0, L"https://www.youtube.com/", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else if (!ShellExecute(0, 0, L"https://github.com/SagaanTheEpic", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else if (!ShellExecute(0, 0, L"https://www.speedrun.com/Assetto_Corsa", 0, 0, SW_SHOW)) // shell code 
				{
					DWORD errorCode = GetLastError();
					DisplayError(TEXT("Unable to execute."), errorCode);
				}
				else
				{
					cout << "Website Launched" << endl;
				}
				Sleep(3000);
			}
			else
			{
				cout << "Unclear Inst" << endl;
				Sleep(1000);
			}
		}

		system("CLS");
		Answers = ""; // remember to clear answers so that it doesnt repeat




	}
}