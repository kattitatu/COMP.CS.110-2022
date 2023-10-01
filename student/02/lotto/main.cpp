#include <iostream>

using namespace std;

void probability( int totalballs, int drawnballs){
    unsigned long int upper = 1;
    int i;
    for (i=1; i <= totalballs; i++){
        upper = upper * i;
    }
    unsigned long int lower_pt1 = 1;
    int j;
    for (j=1; j <= (totalballs - drawnballs); j++){
        lower_pt1 = lower_pt1 * j;
    }
    unsigned long int lower_pt2 = 1;
    int k;
    for (k=1; k <= drawnballs; k++){
        lower_pt2  = lower_pt2 * k;
    }
    unsigned long int alakerta = lower_pt1 * lower_pt2;

    cout << "The probability of guessing all "<< drawnballs <<" balls correctly is 1/"<< (upper/alakerta) << endl;
}


void errorcheck( int totalballs, int drawnballs){
    if ( totalballs <= 0 or drawnballs <= 0){
        cout << "The number of balls must be a positive number." << endl;
    }
    else if( drawnballs > totalballs){
        cout << "The maximum number of drawn balls is the total amount of balls."<< endl;
    }
    else{
        probability(totalballs, drawnballs);
    }


}

int main()
{
    cout << "Enter the total number of lottery balls: ";
    int totalballs = 0;
    cin >> totalballs;
    cout << "Enter the number of drawn balls: ";
    int drawnballs = 0;
    cin >> drawnballs;
    errorcheck(totalballs, drawnballs);

}
