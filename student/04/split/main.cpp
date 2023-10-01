#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(std::string text, char separator, bool ignore_empty = false){
    std::vector<std::string> parts;
    std::string::size_type count = text.size();
    int lenght = count;
    std::string text_part = "";
    if (ignore_empty == false){
        for (int index = 0; index < lenght; index++){
            if (text.at(index) != separator){
                text_part += text.at(index);
                if (index == lenght - 1){
                    parts.push_back(text_part);
                }
            }
            else if ( index != 0 and text.at(index) == separator and text.at(index - 1) == separator){
                parts.push_back(text_part);
                if (index == lenght - 1){
                    parts.push_back(text_part);
                }
            }


            else{
                parts.push_back(text_part);
                text_part = "";
                if (index == lenght - 1){
                    parts.push_back(text_part);
                }

            }
        }
        return parts;
    }

    else{
        for (int index = 0; index < lenght; index++){
            if (text.at(index) != separator){
                text_part += text.at(index);
                if (index == lenght - 1){
                    parts.push_back(text_part);
                }
            }
            else{
                std::string::size_type count2 = text_part.size();
                int length2 = count2;
                if ( length2 != 0){
                    parts.push_back(text_part);
                    text_part = "";
                }
            }
        }
        return parts;
    }
}
int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
