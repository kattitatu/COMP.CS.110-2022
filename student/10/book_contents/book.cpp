/*
 * Ohjelman kirjoittaja
 * Nimi: Heikki Malmirae
 * Opiskelijanumero: 150412373
 * Käyttäjätunnus: mdhema
 * E-Mail: heikki.malmirae@tuni.fi
 *
*/

#include "book.hh"

using namespace std;
Book::Book()
{
    vector<Chapter*> chapters;
}

Book::~Book()
{

}

// Luo uuden kappaleen kirjaan. Antaa sille id:n, koko nimen ja pituuden.
// Tarkistaa myös ettei samalla id:llä ole jo kappaletta olemassa.
void Book::addNewChapter(const std::string &id, const std::string &fullName, int length)
{
    if(check_if_exists(id)){
        cout<<"Error: Already exists."<<endl;
    }
    else{
        Chapter* new_chapter = new Chapter();
        new_chapter->id_ = id;
        new_chapter->fullName_ = fullName;
        new_chapter->length_ = length;
        chapters.push_back(new_chapter);
    }
}
// Lisää kappaleelle suhteet. Eli jos kappaleella on "parent" kappale,
// sekä mahdolliset aliluvut (subchapters).
// subchapter parametri tarkoittaa siis tässä itse kappaletta. Lisätään siis
// vain parent kappaleen osoite sille. Sekä parent kappaleen subchapters
// vektoriin osoite tähän kappaleeseen.
void Book::addRelation(const std::string &subchapter, const std::string &parentChapter)
{
    Chapter* current_chapter = nullptr;
    Chapter* parent_chapter = nullptr;
    string own_id = subchapter;
    for(auto itr : chapters){
        Chapter ptr = *itr;
        if(ptr.id_ == subchapter){
            current_chapter = itr;
            break;
        }
    }
    for(auto itr2 : chapters){
        Chapter ptr2 = *itr2;
        if(ptr2.id_ == parentChapter){
            parent_chapter = itr2;
            break;
        }
    }
    if(current_chapter!=nullptr){
        current_chapter->parentChapter_ = parent_chapter;
    }
    if(parent_chapter != nullptr){
        parent_chapter->subchapters_.push_back(current_chapter);
    }
}

// Tulostaa kirjan kappaleiden määrän,
// sekä kaikki kappaleet aakkosjärjestyksessä
void Book::printIds(Params) const
{
    map<string, string> alphabetical_map;
    int amount_of_chapters = chapters.size();
    cout << "Book has " << amount_of_chapters << " chapters:"<< endl;
    for (auto itr : chapters){
        Chapter ptr = *itr;
        alphabetical_map.insert({ptr.fullName_, ptr.id_});
    }
    for (auto itr : alphabetical_map){
        cout << itr.first << " --- "<< itr.second<<endl;
    }


}
// Sisällysluettelon tulostus rekursiivisesti
// Sisennykset syvemmälle mentäessä jne.
// Tarkistaa myös onko tulostettava kappale "suljettu",
// jolloin jättää sen alikappaleet tulostamatta ja "+" eteen
void Book::recursive_contents(vector<Chapter*> chapters, string spaces, set<Chapter*> closed_chapters) const
{
    int count = 1;
    for (auto itr : chapters){
        if (find(closed_chapters.begin(), closed_chapters.end(), itr)!=closed_chapters.end()){
        cout << "+"<< spaces << count << ". "<<itr->fullName_ << " ( "<<itr->length_<< " )"<<endl;
        count++;
        }
        else{
            cout << "-"<< spaces << count << ". "<<itr->fullName_ << " ( "<<itr->length_<< " )"<<endl;
            if (itr->subchapters_.size()!=0){
                recursive_contents(itr->subchapters_, spaces + "  ", closed_chapters);
        }
        count++;
        }
    }
}

// Sisällysluettelon tulostusta kutsuva metodi.
// muodostaa listan ylimmistä "parents" kappaleista,
// joka helpottaa kutsuttua rekursiivista tulostusta.
void Book::printContents(Params) const
{
    vector<Chapter*> parents;
    for(auto itr : chapters){
        if(itr->parentChapter_==nullptr){
            parents.push_back(itr);
        }
    }
    recursive_contents(parents, " ", closed_chapters);
}

// Lisää kappaleita "suljettujen kappaleiden listaan"
// lisää siis myös kaikki parametrina annetun suljettavan kappaleen
// alikappaleet listaan.
void Book::recursive_close(vector<Chapter*> chapters) const{
    for (auto itr : chapters){
        if(itr->subchapters_.size()!=0){
            closed_chapters.insert(itr);
            recursive_close(itr->subchapters_);
        }
    }
}

// Kutsuu rekursiivista kappeleiden sulkemista.
// Tarkastaa onko parametrina annettu kappale olemassa
// ja lisää sen suljettujen kappaleiden listaan
void Book::close(Params params) const
{
    Chapter* given_as_param = nullptr;
    for (auto itr : chapters){
        if(itr->id_==params.at(0)){
            given_as_param = itr;
        }
    }
    if (given_as_param == nullptr){
        cout<<"Error: Not found: " << params.at(0) <<endl;
        return;
    }
    closed_chapters.insert(given_as_param);
    recursive_close(given_as_param->subchapters_);

}

// Avaa parametrina annetun kappaleen, jos se löytyy.
void Book::open(Params params) const
{   Chapter* given_as_param = nullptr;
    for (auto itr : chapters){
        if(itr->id_==params.at(0)){
            given_as_param=itr;

        }
    }
    if(given_as_param == nullptr){
        cout<< "Error: Not found: "<<params.at(0)<<endl;
        return;
    }
    auto it=closed_chapters.find(given_as_param);
    closed_chapters.erase(it);
}
// Tyhjentää koko suljettujen kappaleiden listan eli avaa kaiken
void Book::openAll(Params) const
{
    closed_chapters.clear();
}

// Tulostaa rekursiivisesti aakkosjärjestyksessä kaikki parametrina annetun kappaleen
// "parent" kappeleet n-korkeuteen asti
void Book::recursive_print_parents(Chapter* root, std::vector<Chapter*> parents,
                                   int depth, int numb_of_parents=1) const
{
    int n = parents.size();
    Chapter* last_element = parents[n-1];
    if(depth>1 && last_element->parentChapter_!=nullptr){
            parents.push_back(last_element->parentChapter_);
            numb_of_parents++;
            recursive_print_parents(root, parents, depth-1, numb_of_parents);
    }
    else{
        vector<string>sorted_parents={};
        for(auto itr : parents){
            sorted_parents.push_back(itr->id_);
        }
        sort(sorted_parents.begin(), sorted_parents.end());
        cout << root->id_ << " has " << numb_of_parents << " parent chapters:"<<endl;
        for (auto itr : sorted_parents){
            cout<< itr<<endl;
        }
    }
}

// Tarkastaa virhetilanteet.
// Kutsuu "parents" tulostusta, jos annetut parametrit kelpaavat
void Book::printParentsN(Params params) const
{
    int N = std::stoi(params.at(1));
    if (N<1){
        cout<<"Error. Level can't be less than 1."<<endl;
        return;
    }
    Chapter* given_as_param = nullptr;
    for(auto itr : chapters){
       if(itr->id_==params.at(0)){
            given_as_param = itr;
       }
    }
    if (given_as_param == nullptr) {
        cout<<"Error: Not found: "<< params.at(0)<<endl;
        return;
    }
    if (given_as_param->parentChapter_ == nullptr){
        cout<< given_as_param->id_ << " has no parent chapters."<<endl;
        return;
    }
    vector<Chapter*> parents;
    parents.push_back(given_as_param->parentChapter_);
    recursive_print_parents(given_as_param, parents, N);
}
// Tulostaa annetut "subchapterit" aakkosjärjestyksessä
void Book::print(set<Chapter*> children, Chapter* origin) const{
    vector<string>sorted_children={};
    for(auto itr : children){
        sorted_children.push_back(itr->id_);
    }
    sort(sorted_children.begin(), sorted_children.end());
    cout << origin->id_ << " has " << sorted_children.size() << " subchapters: "<<endl;
    for(auto itr : sorted_children){
        cout << itr<<endl;
    }
}

// Kerää settiin parametrina annetun kappaleen alikappaleet
// n-syvyyteen asti.
void Book::collect_sub_chapters(vector<Chapter*> current_level_children, set<Chapter*>& children,
                                       int depth, Chapter* origin, int level=0) const
{
    if(level<depth && current_level_children.size()!=0){
        vector<Chapter*> tmp = {};
        for(auto itr : current_level_children){
            children.insert(itr);
            for(auto ptr : itr->subchapters_){
                tmp.push_back(ptr);
                collect_sub_chapters(tmp, children, depth, origin, level +1);
            }
        }
    }
}

// Tarkistaa virhetilanteet.
// Kutsuu alikappaleiden keräystä ja sen jälkeen itse tulostusta
void Book::printSubchaptersN(Params params) const
{
    int N = std::stoi(params.at(1));
    if (N<1){
        cout<<"Error. Level can't be less than 1."<<endl;
        return;
    }
    Chapter* given_as_param = nullptr;
    for(auto itr : chapters){
       if(itr->id_==params.at(0)){
            given_as_param = itr;
       }
    }
    if (given_as_param == nullptr) {
        cout<<"Error: Not found: "<< params.at(0)<<endl;
        return;
    }
    if(given_as_param->subchapters_.size()==0){
        cout<<params.at(0)<< " has no subchapters."<<endl;
        return;
    }
    vector<Chapter*> current_level_children=given_as_param->subchapters_;
    set<Chapter*> children;
    collect_sub_chapters(current_level_children, children, N, given_as_param);
    print(children, given_as_param);
}

// Kerää parametrina annetun kappaleen sisarkappaleet
// ja tulostaa ne aakkosjärjestyksessä.
void Book::printSiblingChapters(Params params) const
{
    Chapter* given_as_param = nullptr;
    for(auto itr : chapters){
       if(itr->id_==params.at(0)){
            given_as_param = itr;
       }
    }
    if (given_as_param == nullptr) {
        cout<<"Error: Not found: "<< params.at(0)<<endl;
        return;
    }
    if(given_as_param->parentChapter_==nullptr){
        cout << given_as_param->id_ << " has no sibling chapters."<<endl;
        return;
    }
    Chapter* parent = given_as_param->parentChapter_;
    if (parent->subchapters_.size()==1){
        cout<<params.at(0)<<" has no sibling chapters."<<endl;
    }
    vector<Chapter*> siblings;
    for(auto itr : parent->subchapters_){
        if(itr != given_as_param){
            siblings.push_back(itr);
        }
    }
    sort(siblings.begin(), siblings.end());
    cout << params.at(0) << " has "<< siblings.size() << " sibling chapters: "<<endl;
    for (auto itr : siblings){
          cout << itr->id_<<endl;
    }
}

// Laskee komennon parametrina annetun kappaleen koko pituuden
void Book::recursive_length(Chapter*, int& length, vector<Chapter*> children) const
{
    for(auto itr : children){
        length = length + itr->length_;
        if (itr->subchapters_.size()!=0){
            recursive_length(itr, length, itr->subchapters_);
        }
    }
}

// Tarkistaa virhetilanteet.
// Kutsuu kokonaispituuden laskua
// Tulostaa kappaleen pituuden
void Book::printTotalLength(Params params) const
{
    Chapter* given_as_param = nullptr;
    for(auto itr : chapters){
       if(itr->id_==params.at(0)){
            given_as_param = itr;
       }
    }
    if (given_as_param == nullptr) {
        cout<<"Error: Not found: "<< params.at(0)<<endl;
        return;
    }
    int length = given_as_param->length_;
    cout<< "Total length of "<< given_as_param->id_ << " is ";
    recursive_length(given_as_param, length, given_as_param->subchapters_);
    cout << length << "."<<endl;
}

// Tulostaa joko pisimmän tai lyhyimmän kappaleen, riippuen kumpaa halutaan.
void Book::print_longest_or_shortest(bool want_longest, Chapter* chapter, Chapter* root) const
{
    if(want_longest){
        if(chapter == root){
            cout <<"With the length of " <<chapter->length_<<", "<<chapter->id_<<
                   " is the longest chapter in their hierarchy."<< endl;
        }
        else{
            cout <<"With the length of " <<chapter->length_<<", "<<chapter->id_<<
                   " is the longest chapter in " << root->id_<< "'s hierarchy."<< endl;
        }
    }
    else{
        if(chapter == root){
            cout <<"With the length of " <<chapter->length_<<", "<<chapter->id_<<
                   " is the shortest chapter in their hierarchy."<< endl;
        }
        else{
            cout <<"With the length of " <<chapter->length_<<", "<<chapter->id_<<
                   " is the shortest chapter in " << root->id_<< "'s hierarchy."<< endl;
        }
     }
}

// Selvittää annetun kappaleen pisimmän yksittäisen alikappaleen
void Book::solve_longest(vector<Chapter*> subs, int& length, Chapter*& longest_chap) const
{
    for(auto itr : subs){
        if (itr->length_>length){
            length = itr->length_;
            longest_chap = itr;
        }
        if(itr->subchapters_.size()!=0){
            solve_longest(itr->subchapters_, length, longest_chap);
        }
        else{
            continue;
        }
    }
}

// Tarkistaa virhetilanteet,
// Kutsuu pisimmän alikappaleen selvittämistä
// Kutsuu printtausta
void Book::printLongestInHierarchy(Params params) const
{
    bool want_longest = true;
    Chapter* given_as_param = nullptr;
    for(auto itr : chapters){
       if(itr->id_==params.at(0)){
            given_as_param = itr;
       }
    }
    if (given_as_param == nullptr) {
        cout<<"Error: Not found: "<< params.at(0)<<endl;
        return;
    }
    if(given_as_param->subchapters_.size()==0){
        cout <<"With the length of " <<given_as_param->length_<<", "<<given_as_param->id_<<
               " is the longest chapter in their hierarchy."<<endl;
        return;
    }
    Chapter* longest = given_as_param;
    vector<Chapter*> subs = given_as_param->subchapters_;
    solve_longest(given_as_param->subchapters_, given_as_param->length_, longest);
    print_longest_or_shortest(want_longest, longest, given_as_param);
}

// Selvittää kommennossa annetun kappeleen lyhyimmän alikappaleen
void Book::solve_shortest(vector<Chapter*> subs, int& length, Chapter*& shortest) const
{
    for(auto itr : subs){
        if (itr->length_<length){
            length = itr->length_;
            shortest = itr;
        }
        if(itr->subchapters_.size()!=0){
            solve_shortest(itr->subchapters_, length, shortest);
        }
        else{
            continue;
        }
    }
}

// Tarkistaa virhetilanteet
// Kutsuu lyhyimmän alikappaleen selvitystä
// Kutsuu printtausta
void Book::printShortestInHierarchy(Params params) const
{
    bool want_longest = false;
    Chapter* given_as_param = nullptr;
    for(auto itr : chapters){
       if(itr->id_==params.at(0)){
            given_as_param = itr;
       }
    }
    if (given_as_param == nullptr) {
        cout<<"Error: Not found: "<< params.at(0)<<endl;
        return;
    }
    if(given_as_param->subchapters_.size()==0){
        cout <<"With the length of " <<given_as_param->length_<<", "<<given_as_param->id_<<
               " is the shortest chapter in their hierarchy."<<endl;
        return;
    }
    Chapter* shortest = given_as_param;
    vector<Chapter*> subs = given_as_param->subchapters_;
    if(shortest->length_!=1){
        solve_shortest(subs, given_as_param->length_, shortest);
    }
    print_longest_or_shortest(want_longest, shortest, given_as_param);
}

void Book::printParent(Params) const
{

}

void Book::printSubchapters(Params) const
{

}

// Tarkistaa onko id:llä olemassa jo kappale
bool Book::check_if_exists(const std::string &id)
{
    for(auto itr : chapters){
        Chapter ptr = *itr;
        if(ptr.id_ == id){
            return true;
        }
    }
    return false;
}


