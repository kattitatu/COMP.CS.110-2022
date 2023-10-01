#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    int numberCubed = number * number * number;
    int cbrtNumber = numberCubed / number / number;
    if ( cbrtNumber == number){
        cout << "The cube of " << number << " is " << numberCubed << "." << endl;
    }
    else{
        cout << "Error! The cube of " <<  number << " is not " << numberCubed << "." << endl;
    }
}
