/*
#############################################################################
# COMP.CS.110 Programming 2: Autumn 2022                                    #
# Project3: Book contents                                                   #
# File: book.hh                                                             #
# Description: Class describing book chapter hierarchy                      #
#       Datastructure is populated with Chapter-structs and provides some   #
#       query-functions.                                                    #
# Notes: * This is a part of an exercise program                            #
#        * Student's aren't allowed to alter public interface!              #
#        * All changes to private side are allowed.                         #
#############################################################################
*/
/*
Ohjelman kirjoittanut valmiiksi
 * Nimi: Heikki Malmirae
 * Opiskelijanumero: 150412373
 * Käyttäjätunnus: mdhema
 * E-Mail: heikki.malmirae@tuni.fi
*/
#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <map>
#include <algorithm>


// Named constants to improve readability in other modules
const std::string EMPTY = "";
const int NO_LENGTH = -1;

// Command parameters have been collected into a vector. In this way each
// method implementing a command has the same parameters (amount and type).
// If a command has no parameters, the vector is empty.
using Params = const std::vector<std::string>&;

// Struct for a book chapter
struct Chapter
{
    std::string id_ = EMPTY;
    std::string fullName_ = EMPTY;
    int length_ = 0;
    Chapter* parentChapter_ = nullptr;
    std::vector<Chapter*> subchapters_;
};

using IdSet = std::set<std::string>;

// Book class, a datastucture for Chapter structs
class Book
{
public:
    // Constructor
    Book();

    // Destructor
    ~Book();

    // Adds a new Chapter to the datastructure.
    void addNewChapter(const std::string& id, const std::string& fullName,
                       int length);

    // Adds a new chapter-subchapter relation.
    void addRelation(const std::string& subchapter,
                     const std::string& parentChapter);

    // Prints all stored chapters: ID, full name and length
    void printIds(Params params) const;

    // Prints the contents page of the book. Chapters are printed in the order,
    // they are in the book, subchapters are indented appropriately.
    // Either '-' or '+' is printed before each chapter, '-' for open chapters
    // and '+' for closed one. If a chapter is open, its subchapters are
    // also listed.
    void printContents(Params params) const;

    // Closes the given chapter and its subchapters.
    void close(Params params) const;

    // Opens the given chapter.
    void open(Params params) const;

    // Opens all chapters.
    void openAll(Params params) const;

    // Prints the amount and names of parent chapters in given distance from
    // the given chapter. Parent chapters are printed in alphabethical order.
    void printParentsN(Params params) const;

    // Prints the amount and names of subchapters in given distance from
    // the given chapter. Subchapters are printed in alphabethical order.
    void printSubchaptersN(Params params) const;

    // Prints the sibling chapters of the given chapter, i.e. the chapters
    // sharing the parent chapter with the given one.
    void printSiblingChapters(Params params) const;

    // Prints the total length of the given chapter, i.e. the sum of lengths
    // of the given chapter and its subchapters.
    void printTotalLength(Params params) const;

    // Prints the longest chapter in the hierarchy of the given chapter.
    void printLongestInHierarchy(Params params) const;

    // Prints the shortest chapter in the hierarchy of the given chapter.
    void printShortestInHierarchy(Params params) const;

    // Prints the direct parent chapter of the given chapter.
    // Students will not implement this method.
    void printParent(Params params) const;

    // Prints the direct subchapters of the given chapter.
    // Students will not implement this method.
    void printSubchapters(Params params) const;

private:
    mutable std::set<Chapter*>closed_chapters;
    std::vector<Chapter*> chapters;
    // tulostaa sisällysluettelon
    void recursive_contents(std::vector<Chapter*>, std::string spaces, std::set<Chapter*> to_close) const;
    // sulkee kaikki kappaleen alikappeleet
    void recursive_close(std::vector<Chapter*>) const;
    // tulostaa kappeleen vanhemmat tiettyyn tasoon asti
    void recursive_print_parents(Chapter*, std::vector<Chapter*>, int depth, int numb_of_parents) const;
    // kerää talteen alikappaleet
    void collect_sub_chapters(std::vector<Chapter*>, std::set<Chapter*>&, int depth, Chapter*, int level) const;
    // tulostaa edellisessä kerätyt alikappaleet aakkosjärjestyksessä
    void print(std::set<Chapter*>, Chapter*) const;
    // laskee jostain kappaleesta lähtien sen koko pituuden. eli alikappaleiden pituuksien summan
    void recursive_length(Chapter*, int& length, std::vector<Chapter*>) const;
    // ratkaisee pisimmän kappaleen parametrina annetun kappaleen alikappaleista
    void solve_longest(std::vector<Chapter*> subs, int& length, Chapter*& longest) const;
    // tulostaa pisimmän tai lyhyimmän kappaleen
    void print_longest_or_shortest(bool, Chapter*, Chapter*)const;
    // ratkaisee lyhyimmän kappaleen parametrina annetun kappaleen alikappaleista
    void solve_shortest(std::vector<Chapter*> subs, int& length, Chapter*& shortest) const;
    // tarkastaa onko kappale jo olemassa
    bool check_if_exists(const std::string& id);

};

#endif // BOOK_HH
