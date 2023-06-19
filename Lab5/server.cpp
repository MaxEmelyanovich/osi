#include <iostream>
#include <windows.h>
#pragma comment(lib, "kernel32.lib")

using namespace std;

int main() {

    STARTUPINFOW *si;
    PROCESS_INFORMATION *pi;
    HANDLE hWritePipe, hReadPipe, hServerEvent, hSimpleEvent, hSimpleEndedEvent;
    SECURITY_ATTRIBUTES sa;

    hServerEvent = CreateEventW(nullptr, FALSE, FALSE, L"ServerEvent");
    if (!hServerEvent) {
        cout << "ServerEvent was not created\n";
        return 1;
    }

    hSimpleEvent = CreateEventW(nullptr, FALSE, FALSE, L"SimpleEvent");
    if (!hSimpleEvent) {
        cout << "SimpleEvent was not created\n";
        return 1;
    }

    hSimpleEndedEvent = CreateEventW(nullptr, FALSE, FALSE, L"SimpleEndedEvent");
    if (!hSimpleEndedEvent) {
        cout << "SimpleEndedEvent was not created\n";
        return 1;
    }

    HANDLE hEvents[] = {hServerEvent, hSimpleEndedEvent};

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = nullptr;
    sa.bInheritHandle = TRUE;

    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        cout << "Pipe was not created\n";
        return 1;
    }

    int size;
    cout << "Enter array size: ";
    cin >> size;

    si = new STARTUPINFOW;
    ZeroMemory(si, sizeof(STARTUPINFOW));
    si->cb = sizeof(STARTUPINFOW);
    pi = new PROCESS_INFORMATION;
    wstring temp;
    temp = to_wstring(reinterpret_cast<intptr_t>(hWritePipe)) + L" " + 
        to_wstring(reinterpret_cast<intptr_t>(hReadPipe));
    wchar_t* commLine = new wchar_t[temp.length()];
    wcscpy_s(commLine, temp.length() + 1, temp.c_str());

    if (!CreateProcessW(L"simple.exe", commLine, nullptr, nullptr, TRUE, 
    CREATE_NEW_CONSOLE, nullptr, nullptr, si, pi)) {
        cout << "Process creation failed\n";
        cout << GetLastError() << "\n";
        return 1;
    }

    DWORD dwBytesWritten;
    if (!WriteFile(hWritePipe, &size, sizeof(int), &dwBytesWritten, nullptr)) {
        cout << "Info was not written\n";
        return 1;
    }

    SetEvent(hSimpleEvent);

    DWORD dwBytesRead = 0;
    __int32 res;
    while (true)
    {
        int eventIndex = WaitForMultipleObjects(2, hEvents, FALSE, INFINITE) - WAIT_OBJECT_0;
        if (eventIndex == 1)
        {
            break;
        }

        if (!ReadFile(hReadPipe, &res, sizeof(__int32), &dwBytesRead, nullptr)) {
            cout << "Info was not read\n";
            return 1;
        }

        cout << res << " " << "\n";
        SetEvent(hSimpleEvent);
    }

    CloseHandle(hWritePipe);
    CloseHandle(hReadPipe);
    CloseHandle(hServerEvent);
    CloseHandle(hSimpleEvent);
    CloseHandle(hSimpleEndedEvent);
    WaitForSingleObject(pi->hProcess, INFINITE);
    CloseHandle(pi->hProcess);
    CloseHandle(pi->hThread);
    delete[] commLine;
    return 0;
}