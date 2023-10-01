#include <iostream>

using namespace std;

int main()
{
    int positiveNumber = 0;
    cout << "Enter a positive number: ";
    cin >> positiveNumber;

    if ( positiveNumber <= 0){
        cout << "Only positive numbers accepted" << endl;
    }
    else{
        int firstInt = 0;
        int secondInt = 0;
        int startingInt = 1;
        while ( startingInt <= positiveNumber ){
            if ( positiveNumber % startingInt == 0 ){
                if ( firstInt == 0 and secondInt == 0){
                    firstInt = startingInt;
                    secondInt = positiveNumber / startingInt;

                }
                else if ((positiveNumber / startingInt) - startingInt < (secondInt - firstInt) and (positiveNumber / startingInt) - startingInt >= 0){
                    firstInt = startingInt;
                    secondInt = positiveNumber / startingInt;
                }
            }
            ++startingInt;
        }
        cout << positiveNumber << " = " << firstInt << " * " << secondInt << endl;
        }
    return 0;
    }



