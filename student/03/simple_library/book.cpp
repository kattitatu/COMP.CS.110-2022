#include "book.hh"
#include <iostream>

Book::Book( const std::string author, const std::string name, bool is_available):
    author(author), name(name), is_available(is_available)
{

}
void Book::print() const{
    std::cout << author << " : " << name << std::endl;
    if ( is_available){
        std::cout << "- available" << std::endl;
    }
    else{
        std::cout << "- loaned: ";
        date_loaned.print();
        std::cout << "- to be returned: ";
        to_return.print();
    }
}

void Book::loan( Date today)
{
    if ( is_available ){
        date_loaned = today;
        to_return = date_loaned;
        to_return.advance(28);
        is_available = false;
    }
    else{
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
}

void Book::renew(){
    if ( is_available == false){
        to_return.advance(28);
    }
    else{
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    }
}

void Book::give_back(){
    is_available = true;
}


