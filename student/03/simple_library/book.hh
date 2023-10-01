#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include "date.hh"
class Book
{
public:
    Book( const std::string author, const std::string name, bool is_available = true);
    void print() const;
    void loan(Date today);
    void renew();
    void give_back();
private:
    std::string author;
    std::string name;
    bool is_available;
    Date date_loaned;
    Date to_return;

};

#endif // BOOK_HH
