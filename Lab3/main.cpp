#include <iostream>
#include <windows.h>
#include <synchapi.h>
using namespace std;

CRITICAL_SECTION cs;
HANDLE hEvent1, hEvent2;
int K, vowelNumber = 0;

DWORD WINAPI work(LPVOID array)
{
    EnterCriticalSection(&cs);
    int count = 0;
    for (int i = 0; ((char*)array)[i] != '\0'; i++)
    {
        char c = ((char*)array)[i];
        if ((int(c) >= 65 && int(c) <= 90) ||
            (int(c) >= 97 && int(c) <= 122))
        {
            ((char*)array)[count++] = c;
            if (count == K)
            {
                PulseEvent(hEvent1);
            }
        }
    }
    for (int i = count; ((char*)array)[i] != '\0'; i++)
    {
        ((char*)array)[i] = ' ';
        if (i + 1 == K)
        {
            PulseEvent(hEvent1);
        }
    }
    LeaveCriticalSection(&cs);
    return 0;
}

DWORD WINAPI CountElement(LPVOID array)
{
    WaitForSingleObject(hEvent1, INFINITE);
    for (int i = 0; i < K; i++)
    {
        char c = ((char*)array)[i];
        switch (tolower(c))
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'y':
            ++vowelNumber;
            break;
        }
    }
    SetEvent(hEvent2);
    return 0;
}

int main()
{
    int n;
    cout << "Enter size of the array: ";
    cin >> n;
    char* array = new char[n + 1];
    cout << "Enter elements of the array: ";
    for (int i = 0; i < n; i++)
    {
        cin >> array[i];
    }
    array[n] = '\0';
    cout << "Size of the array is " << n << '\n';
    cout << "Elements of the array: ";
    for (int i = 0; i < n; i++)
    {
        cout << array[i] << " ";
    }
    HANDLE	hThreadWork, hThreadCount;
    DWORD	IDThreadWork, IDThreadCount;
    InitializeCriticalSection(&cs);
    hEvent1 = CreateEvent(NULL, true, false, NULL);
    hEvent2 = CreateEvent(NULL, false, false, NULL);
    hThreadCount = CreateThread(NULL, 0, CountElement, array, 0, &IDThreadCount);
    hThreadWork = CreateThread(NULL, 0, work, array, 0, &IDThreadWork);
    EnterCriticalSection(&cs);
    cout << "\nEnter K: ";
    cin >> K;
    LeaveCriticalSection(&cs);
    WaitForSingleObject(hEvent1, INFINITE);
    cout << "Elements of the array till K: ";
    for (int i = 0; i < K; i++)
    {
        cout << array[i] << " ";
    }
    WaitForSingleObject(hEvent2, INFINITE);
    cout << "\nNumber of vowel characters in the array before K: " << vowelNumber << '\n';
    WaitForSingleObject(hThreadWork, INFINITE);
    cout << "Elements of the array after K: ";
    for (int i = K; i < n + 1; i++)
    {
        cout << array[i] << " ";
    }
    DeleteCriticalSection(&cs);
    CloseHandle(hThreadWork);
    CloseHandle(hThreadCount);
    CloseHandle(hEvent1);
    CloseHandle(hEvent2);
    return 0;
}