#include<Windows.h>
#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Usage: "<< argv[0] <<" <sessionID>" << endl;
		return 1;
	}

	auto sessionID = atoi(argv[1]);


	typedef HANDLE(WINAPI* WinStationOpenServerW_t)(_In_ PWSTR ServerName);
	typedef BOOL(WINAPI* WinStationReset_t)(_In_opt_ HANDLE hServer, _In_ ULONG SessionId, _In_ BOOLEAN bWait);

	HMODULE hModule = LoadLibrary(L"winsta.dll");

	if (hModule == NULL)
	{
		cout << "Error [-]: failed loading winsta.dll" << endl;
		return 1;
	}

	WinStationOpenServerW_t WinStationOpenServerW = (WinStationOpenServerW_t)GetProcAddress(hModule, "WinStationOpenServerW");
	if (WinStationOpenServerW == NULL)
	{
		cout << "Error [-]: failed getting WinStationOpenServerW function address" << endl;
		return 1;
	}

	wchar_t serverName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(serverName) / sizeof(serverName[0]);
	GetComputerNameW(serverName, &size);
	if (serverName[0] == L'\0')
	{
		cout << "Error [-]: failed getting server name" << endl;
		return 1;
	}

	HANDLE hServer = WinStationOpenServerW(serverName);
	if (hServer == NULL)
	{
		cout << "Error [-]: failed opening server" << endl;
	}

	WinStationReset_t WinStationReset = (WinStationReset_t)GetProcAddress(hModule, "WinStationReset");
	if (WinStationReset == NULL)
	{
		cout << "Error [-]: failed getting WinStationReset function address" << endl;
        return 1;
	}
	

	if (WinStationReset(hServer, sessionID, TRUE))
	{
            cout << "Success [+]: session " << sessionID << " reset" << endl;
	}

	return 0;
}