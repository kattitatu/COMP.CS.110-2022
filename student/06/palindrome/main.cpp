#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------

  std::string::size_type lenght = s.length();
  int size = lenght;
  if( size == 1){
      return true;
  }
  else if (s.at(0) == s.at(size - 1)){
    if (size != 2){
        if (palindrome_recursive(s.substr(1, size - 2))){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return true;
    }
  }

  else{
      return false;
  }
}
// 0 1 2 3 4 5 6 7 8
// d e l e v e l e d
// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
