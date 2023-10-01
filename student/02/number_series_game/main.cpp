#include <iostream>
using namespace std;

int main()
{
    int numberAmount = 0;
    cout << "How many numbers would you like to have? ";
    cin >> numberAmount;

    for ( int turn = 1; turn <= numberAmount; ++turn){
        if ( turn % 3 == 0 && turn % 7 == 0 ){
            cout << "zip boing" << endl;
        }

        else if ( turn % 3 == 0 ){
            cout << "zip" << endl;
        }
        else if ( turn % 7 == 0 ){
            cout << "boing" << endl;
        }
        else {
            cout << turn << endl;
        }
    }
    // Write your code here

    return 0;
}
