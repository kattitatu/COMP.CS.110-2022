#include <iostream>
#include <unordered_map>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif


using namespace std;

void print_vertical(unsigned int num)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------
    int digit = num % 10;
    num = num / 10;
    if (num != 0){
        print_vertical(num);
    }
    cout << digit << endl;
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    unsigned int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    cout << "The given number (" << number << ") written vertically:" << endl;
    print_vertical(number);
    return 0;
}
#endif
