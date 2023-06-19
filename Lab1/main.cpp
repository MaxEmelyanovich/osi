#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

DWORD WINAPI worker(LPVOID array)
{
    srand(unsigned(time(0)));
    int x, count = 0;
    x = rand()%20;
    cout << x << '\n';
    Sleep(200);
    for (int i = 1; i < ((int*)array)[0] + 1; i++)
    {
        if (((int*)array)[i] > x)
        {
            count++;
        }
    }
    cout << count;
    return 0;
}

int main()
{
    srand(unsigned(time(0)));
    int size = rand()%20 + 1;
    int* array = new int[size + 1];
    array[0] = size;
    cout << "Array: ";
    for (int i = 1; i < size + 1; i++)
    {
        array[i] = rand() %20;
        cout << array[i] << " ";
    }
    cout << '\n';
	HANDLE	hThread;
	DWORD	IDThread;
	hThread = CreateThread(NULL, 0, worker, (void*)array, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();
    SuspendThread(hThread);
   // Sleep(5000);
    ResumeThread(hThread);
	//WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	return 0;
}