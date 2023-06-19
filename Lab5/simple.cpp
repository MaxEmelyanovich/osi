#include <iostream>
#include <windows.h>
#include <time.h>
#include <cmath>
#pragma comment(lib, "kernel32.lib")

using namespace std;

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }

    int sqrtn = sqrt(n);

    bool prime[n + 1];
    for (int i = 2; i <= n; i++) {
        prime[i] = true;
    }

    for (int i = 2; i <= sqrtn; i++) {
        if (prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }

    return prime[n];
}

int main(int argc, char* argv[]) {
	srand(time(0));
	HANDLE hWritePipe = (HANDLE)(atoi(argv[0]));
	HANDLE hReadPipe = (HANDLE)(atoi(argv[1]));


	if (hReadPipe == INVALID_HANDLE_VALUE || hWritePipe == INVALID_HANDLE_VALUE) {
		printf("Error: Invalid handle value\n");
		return 1;
	}

	HANDLE hServerEvent = OpenEventW(EVENT_MODIFY_STATE, FALSE, L"ServerEvent");
	if (!hServerEvent) {
		cout << "ServerEvent was not read\n";
        return 1;
	}

    HANDLE hSimpleEvent = OpenEventW(EVENT_MODIFY_STATE, FALSE, L"SimpleEvent");
	if (!hSimpleEvent) {
		cout << "ServerEvent was not read\n";
        return 1;
	}

    HANDLE hSimpleEndedEvent = OpenEventW(EVENT_MODIFY_STATE, FALSE, L"SimpleEndedEvent");
    if (!hSimpleEndedEvent) {
        cout << "SimpleEndedEvent was not created\n";
        return 1;
    }

    WaitForSingleObject(hSimpleEvent, INFINITE);

	int size;
	DWORD dwBytesRead;
	if (!ReadFile(hReadPipe, &size, sizeof(int), &dwBytesRead, NULL)) {
		cout << "Info was not read";
		cout << GetLastError();
        return 1;
	}

    cout << "Array: ";
	__int32* arr = new __int32[size];
	for (int i = 0; i < size; ++i) {
	    cout << (arr[i] = rand() % 100 + 1) << " ";
	}
	cout << '\n';

    cout << "Prime numbers:\n";
    DWORD dwBytesWritten;
    ungetc('a', stdin);
    for (int i = 0; i < size; ++i)
    {
        if (isPrime(arr[i]))
        {
            getchar();
            if (!WriteFile(hWritePipe, &arr[i], sizeof(__int32), &dwBytesWritten, NULL)) {
                cout << "Number was not written";
            }
            cout << arr[i];
            SetEvent(hServerEvent);
            WaitForSingleObject(hSimpleEvent, INFINITE);
        }
    }

    cout << '\n';

	SetEvent(hSimpleEndedEvent);
    system("pause");
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);
	CloseHandle(hServerEvent);
    CloseHandle(hSimpleEvent);
    CloseHandle(hSimpleEndedEvent);
    delete[] arr;
	return 0;
}