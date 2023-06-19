#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
mutex mutex_thread;
condition_variable work_condition;
condition_variable count_element_condition;
bool work_ready = false;
bool count_element_ready = false;
int k = 0;
int vowel_number;

void Work(char* array){
    mutex_thread.lock();
    int count = 0;
    for (int i = 0; ((char*)array)[i] != '\0'; i++)
    {
        char c = ((char*)array)[i];
        if ((int(c) >= 65 && int(c) <= 90) ||
            (int(c) >= 97 && int(c) <= 122))
        {
            ((char*)array)[count++] = c;
            if (count == k)
            {
                work_ready = true;
                work_condition.notify_all();

            }
        }
    }

    for (int i = count; ((char*)array)[i] != '\0'; i++)
    {
        ((char*)array)[i] = ' ';
        if (i + 1 == k)
        {
            work_ready = true;
            work_condition.notify_all();
        }
    }
    mutex_thread.unlock();
}

void CountElement(char* array){
    unique_lock<mutex> lck(mutex_thread);
    while (!work_ready){
        work_condition.wait(lck);
    }
    for (int i = 0; i < k; i++)
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
                ++vowel_number;
                break;
        }
    }
    count_element_ready = true;
    count_element_condition.notify_one();
}


int main() {
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
    mutex_thread.lock();
    thread work_thread(Work, array);
    thread count_element_thread(CountElement, array);
    cout << "\nEnter K: ";
    cin >> k;
    mutex_thread.unlock();
    unique_lock<mutex> lck(mutex_thread);
    while (!work_ready){
        work_condition.wait(lck);
    }
    cout << "Elements of the array till K: ";
    for (int i = 0; i < k; i++)
    {
        cout << array[i] << " ";
    }
    while(!count_element_ready){
        count_element_condition.wait(lck);
    }
    cout << "\nNumber of vowel characters in the array before K: " << vowel_number << '\n';
    cout << "Elements of the array after K: ";
    work_thread.join();
    for (int i = k; i < n + 1; i++)
    {
        cout << array[i] << " ";
    }
    return 0;
}