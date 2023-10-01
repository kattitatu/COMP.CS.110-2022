#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

int checkText(string text){

    int indexi;
    string::size_type lengthi = text.length();
    int textLengthi = lengthi;
    for (indexi=0; indexi < textLengthi; ++indexi){
        if (isupper(text[indexi])){
            cout << "Error! The text to be encrypted must contain only lower case characters."<< endl;
            return 1;
        }
    }
    return 0;
}
int encrypt(string key, string text){

    int index;
    string encryptedText;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string::size_type length = text.length();
    int textLength = length;
    for(index=0; index < textLength; index++){
        encryptedText += key[alphabet.find(text[index])];
    }
    cout << "Encrypted text: "<< encryptedText << endl;
    return 0;
}



int keyCheck(string key){
    if( key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters."<< endl;
        return 1;
    }
    int index;
    string::size_type length = key.length();
    int keyLength = length;
    for (index=0; index < keyLength; ++index){
        if (isupper(key[index])){
            cout << "Error! The encryption key must contain only lower case characters."<< endl;
            return 1;
        }
    }
    for (char letter = 'a'; letter <= 'z'; ++letter){
        if (key.find(letter) == string::npos){
            cout << "Error! The encryption key must contain all alphabets a-z."<< endl;
            return 1;
        }
    }
    return 0;

}

int main()
{
    cout << "Enter the encryption key: ";
    string encryptionKey = "";
    cin >> encryptionKey;
    if (keyCheck(encryptionKey) == 1){
        return 1;
    }
    string text;
    cout << "Enter the text to be encrypted: ";
    cin >> text;
    if (checkText(text) == 1){
        return 1;
    }
    encrypt(encryptionKey, text);

}
