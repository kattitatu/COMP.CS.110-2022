#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string input_file;
    string output_file;
    cout << "Input file: ";
    cin >> input_file;
    cout << "Output file: ";
    cin >> output_file;
    ifstream file_object(input_file);
    if (not file_object){
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return 1;
    }
    else{
        string row;
        ofstream write_file(output_file);
        int row_number = 1;
        while ( getline(file_object, row)){
            write_file << row_number << " "<< row << endl;
            row_number++;
        }

    }
}
