//
//  main.cpp
//  Project6_1
//
//  Created by Devansh Mishra on 23/11/23.
//

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void problemA () {
    int arr[3] = { 5, 10, 15 };
    int* ptr = arr;

    *ptr = 30;          // set arr[0] to 30
    *(ptr + 1) = 20;      // set arr[1] to 20
    ptr += 2;
    ptr[0] = 10;        // set arr[2] to 10

    ptr -= 2;
    while (ptr < arr +3)
    {
        cout << *ptr << endl;    // print values
        ptr++;
    }
}

void findMax(int arr[], int n)
{
    int* pToMax = nullptr;
    if (n <= 0)
        return;      // no items, no maximum!
    
    pToMax = arr;
    
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > *pToMax) {
            pToMax = &arr[i];
        }
    }
}

void problemB () { // the original function changed the pointer address pToMax and not the value contained by the pointer itself
    int nums[4] = { 5, 3, 15, 6 };
    int* ptr = &nums[0];

    findMax(nums, 4);
    cout << "The maximum is at address " << ptr << endl;
    cout << "It's at position " << ptr - nums << endl;
    cout << "Its value is " << *ptr << endl;
}

void computeCube(int n, int* ncubed)
{
    *ncubed = n * n * n;
}

void problemC () { // the pointer did not point to an object initialially and thus there was a runtime error as computeCube could not assign the value to a memory location
    int result;
    int* ptr = &result;
    computeCube(5, ptr);
    cout << "Five cubed is " << *ptr << endl;
}

// return true if two C strings are equal
bool strequal(const char str1[], const char str2[]) // the function initially compared the pointers of str1 and str2 instead of the content of the two strings, in the loop condition also it checked whether the addresses of the pointers were not null and not the content of the pointers themselves
{
    while (*str1 != '\0' && *str2 != '\0')  // zero bytes at ends
    {
        if (*str1 != *str2)  // compare corresponding characters
            return false;
        str1++;            // advance to the next character
        str2++;
    }
    return *str1 == *str2;   // both ended at the same time?
}

void problemD () {
    char a[15] = "Chen, Y.";
    char b[15] = "Chen, Y.";

    if (strequal(a,b)) {
        cout << "They're the same person!\n";
    }
}

int* nochange(int* p)
{
    return p;
}

int* getPtrToArray(int& m)
{
    int anArray[100];
    for (int j = 0; j < 100; j++)
        anArray[j] = 100-j;
    m = 100;
    for (int i = 0; i < m; i++){
        cout << anArray[i] << endl;
    }
    return nochange(anArray);
}

void f()
{
    int junk[100];
    for (int k = 0; k < 100; k++)
        junk[k] = 123400000 + k;
    junk[50]++;
}

void problemE () { // the program is subscripting the pointer when it should be using it as a method that points to an object
    int n;
    int* ptr = getPtrToArray(n);
    for (int i = 0; i < 3; i++) {
        cout << *ptr << ' ';
        ptr++;
    }
    for (int i = n-3; i < n; i++) {
        cout << ptr[i] << ' ';
    }
    cout << endl;
}

const char* findTheChar(const char str[], char ch) {
    for (int k = 0; str+k!=0; k++) {
        if (*(str+k)==ch) {
            return str+k;
        }
    }
    return nullptr;
}

const char* findTheCharAlt(const char* str, char chr)
{
    const char* ptr = str;

    while (*ptr != 0 && *ptr != chr)
        ++ptr;

    if (*ptr == chr){
        return ptr;
    }
    else return nullptr;
}

void problem3 () {
    cout << findTheCharAlt("HELLO", 'E') << endl;
}


int* maxwell(int* a, int* b)
{
    if (*a > *b)
        return a;
    else
        return b;
}

void swap1(int* a, int* b)
{
    int* temp = a;
    a = b;
    b = temp;
}

void swap2(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void problem4 ()
{
    int array[6] = { 5, 3, 4, 17, 22, 19 };

    int* ptr = maxwell(array, &array[2]); // compares the value of array[0] and array[2] to return the greater value (array[0] in this case)
    *ptr = -1; // array[0] is set to -1
    ptr += 2; // pointer incremented
    ptr[1] = 9; // ptr+1 (array[3]) is set to 9
    *(array+1) = 79; // array[1] is set to 79 --> array = {-1,79,4,9,22,19}

    cout << &array[5] - ptr << endl; // prints the difference between the addresses of the pointers - ptr points to array[2] so &array[5] - &array[2] prints 3

    swap1(&array[0], &array[1]); // swaps the pointers of array[0] and array[1] - values of the array remain the same
    swap2(array, &array[2]); // swaps the values of array[0] and array[2] - array is modified to {4,79,-1,9,22,19}

    for (int i = 0; i < 6; i++) {
        cout << array[i] << endl; // prints the contents of the array chronologically on separate lines resulting in 4,79,-1,9,22,19
    }
}

void removeS (char* str) {
    for (char* ptr = str; *ptr!=0; ptr++){
        if ((*ptr=='s') or (*ptr=='S')){
            while (*ptr!=0) {
                *ptr = *(ptr+1);
                ptr++;
            }
            *ptr = '\0';
            ptr = str;
        }
    }
}

void problem5 ()
{
    char msg[50] = "She'll blossom like a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll bloom like a male prince.
}

int main() {
    //problemA();
    //problemB();
    //problemC();
    //problemD();
    //problemE();
    //problem3();
    //problem4();
    //problem5();
}
