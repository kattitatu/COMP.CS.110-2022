
#include <string>
#include <istream>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <cstring>
/* Keikkakalenteri
 * Ohjelma toteuttaa keikkakalenterin. Ohjelma lukee sille annetun tekstitiedoston,
 *  jonka tiedot se tallentaa sopivaan tietorakenteeseen mikäli tekstitiedoston sisältö on oikeassa muodossa (artist;date;city;stage).
 *  Ohjelma myös tarkastaa onko ajankohta mahdollinen ja että onko päällekkäisiä keikkoja.
 *  Onnistuneen tiedoston lukemisen jälkeen ohjelma ottaa vastaan käyttäjän syötteitä.
 *  Käyttäjä voi tulostaa kaikki artistit, tulostaa tietyn artistin keikat, tulostaa kaikki keikkapaikat,
 *  tai tulostaa tietyllä keikkapaikalla esiintyvät artistit. Käyttäjä voi myös halutessaan lopettaa
 *  ohjelman komennolla "QUIT".
 *
 *  Ohjelman kirjoittaja
 * Nimi: Heikki Malmirae
 * Opiskelijanumero: 150412373
 * Käyttäjätunnus: mdhema
 * E-Mail: heikki.malmirae@tuni.fi
 *
 * Huomioita ohjelman toteutuksesta:
 * Split funktio toistuu lähes identtisenä, mikä on hieman laiska ratkaisu, mutta koska
 * ei ollut kyse isosta funktiosta, annoin asian olla. Luokkia en kokenut tarpeelliseksi/hyödylliseksi
 * tässä tehtävässä. Tietorakenteen läpikäynti tuntui hieman haastavalta joissain kohdin, mutta
 * eiköhän se ollut tehtävän tarkoituskin. Tietorakenne tuskin olisi voinut paljoa yksinkertaisempi olla?
 *
*/
using namespace std;
using Calendar = map<string, map<string, pair<string, string>>>;
// Farthest year for which gigs can be allocated
const string FARTHEST_POSSIBLE_YEAR = "2030";

// Split funktio, palauttaa ";" merkin tai annetun merkin kohdilta osiin jaetun string vektorin.
vector<string> split(const string& str, char delim = ';')
{
    vector<string> result = {""};
    bool inside_quotation = false;
    for ( char current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quotation = not inside_quotation;
        }
        else if ( current_char == delim and not inside_quotation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}


// Tarkistaa onko annettu päivämäärä mahdollinen
bool is_valid_date(const string& date_str)
{
    vector<string> date_vec = split(date_str, '-');
    if ( date_vec.size() != 3 )
    {
        return false;
    }

    string year = date_vec.at(0);
    string month = date_vec.at(1);
    string day = date_vec.at(2);
    vector<string> month_sizes
            = { "31", "28", "31", "30", "31", "30",
                "31", "31", "30", "31", "30", "31" };

    if ( month < "01" or month > "12" )
    {
        return false;
    }
    if ( year < "0001" or year > FARTHEST_POSSIBLE_YEAR )
    {
        return false;
    }
    unsigned int year_int = stoi(year);
    bool is_leap_year = (year_int % 400 == 0) or
                        (year_int % 100 != 0 and year_int % 4 == 0);
    if ( day >= "01" and
        (day <= month_sizes.at(stoi(month) - 1) or
        (month == "02" and is_leap_year and day <= "29")) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Lisää tietorakenteeseen yhden artistin keikan tiedot kerrallaan.
// Parametrina syötetiedostosta splitattu string vektori, jossa keikan tiedot. Viittaus tietorakenteeseen,
// sekä viite string vektoriin "places", johon tallennetaan erikseen keikkapaikkojen tiedot myöhempää käyttöä varten.
// Tietorakenne on mappi, missä hyötykuormana toinen mappi, jonka hyötykuormana "pair".
// Tarkastaa myös, jos tietyssä paikassa on jo olemassa keikka samalla päivälle.
// palauttaa main funktiolle 0, jos tapahtuu virhe.
int add_to_data_structure(const vector<string>& split_line, Calendar& gig_calendar, vector<string>& places){
    string artist = split_line.at(0);
    string date = split_line.at(1);
    string city = split_line.at(2);
    string place = split_line.at(3);
    if(not is_valid_date(date)){
        cout << "Error: Invalid date."<<endl;
        return 0;
    }

    places.push_back(place);

    pair<string, string> location_pair (city, place);
    map<string, map<string, pair<string,string>>>::iterator itr;
    map<string, pair<string,string>>::iterator ptr;
    for (itr=gig_calendar.begin(); itr!=gig_calendar.end(); itr++){
        for(ptr=itr->second.begin(); ptr!= itr->second.end();ptr++){
            if (ptr->first == date){
                if(ptr->second.first == location_pair.first && ptr->second.second == location_pair.second){
                    cout<< "Error: Already exists."<<endl;
                    return 0;
                }
            }
        }
    }

    if (gig_calendar.find(artist) == gig_calendar.end()){
        gig_calendar.insert(make_pair(artist, map<string, pair<string, string>>()));
        gig_calendar[artist].insert(make_pair(date, location_pair));
    }
    else{

        if (gig_calendar.at(artist).find(date) == gig_calendar[artist].end()){
            gig_calendar[artist].insert(make_pair(date, location_pair));
        }
        else{
            cout << "Error: Already exists." << endl;
            return 0;
        }
    }
    return 1;
}

// Toinen split-funktio käyttäjän syötteiden osiinjakamista varten
// Mahdollisesti turhaa toistoa, mutta välilyöntiä ei saanut "char" tyypin parametrina
// välitettyä, joten en alkanut enempää säätää.
// Palauttaa string vektorin missä syöte jaettuna osiin
vector<string>split_input(const string& input){
    vector<string> result = {""};
    bool inside_quotation = false;
    char delim = ' ';   
    for ( char current_char : input )
    {
        if ( current_char == '"' )
        {
            inside_quotation = not inside_quotation;
        }
        else if ( current_char == delim and not inside_quotation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Tulostaa kaikki esiintyvät artistit aakkosjärjestyksessä
// parametrina vain viite kalenteriin
void print_artists(Calendar& gig_calendar){
    map<string, map<string, pair<string,string>>>::iterator itr;
    cout << "All artists in alphabetical order:"<< endl;
    for (itr = gig_calendar.begin(); itr!=gig_calendar.end(); itr++){
        cout<< itr->first<<endl;
    }
}

// Tulostaa kaikki parametrina annetun artistin keikat aikajärjestyksessä
// parametrina viite kalenteriin ja artisti stringinä
void print_gigs(Calendar& gig_calendar, string artist){

    map<string, pair<string,string>>::iterator itr;
    cout << "Artist " << artist << " has the following gigs in the order they are listed:"<< endl;
    for (itr = gig_calendar[artist].begin(); itr != gig_calendar[artist].end(); itr++ ){
        cout << " - " << itr->first << " : " << itr->second.first << ", " << itr->second.second<<endl;
    }
}

// pieni funktio aakkosjärjestämiseen
bool my_sort(string a, string b ){
    return a<b;
}

// Tulostaa kaikki keikkapaikat aakkosjärjestyksessä
// Parametrina viite kalenteriin
// hyödyntää my_sort funtkiota
void print_stages(Calendar& gig_calendar){
    map<string, vector<string>> stages;
    map<string, map<string, pair<string, string>>>::iterator itr;
    map<string, pair<string,string>>::iterator ptr;
    for (itr = gig_calendar.begin(); itr != gig_calendar.end(); itr++){
        for(ptr = itr->second.begin(); ptr != itr->second.end(); ptr++){
            string first = ptr->second.first;
            string second = ptr->second.second;
            if (stages.find(first) != stages.end()){
                vector <string> places = stages[first];
                if(find(places.begin(), places.end(), second) == places.end()){
                    stages[first].push_back(second);
                }
            }
            else{
                stages.insert(make_pair(first, vector<string>()));
                stages[first].push_back(second);
                sort(stages[first].begin(), stages[first].end(), my_sort);
            }
        }

    }
    cout << "All gig places in alphabetical order:"<<endl;
    map<string, vector<string>>::iterator itr2;
    vector<string>::iterator ptr2;
    for (itr2 = stages.begin(); itr2 != stages.end(); itr2++){
        for (ptr2 = itr2->second.begin(); ptr2 != itr2->second.end(); ptr2++){
            cout << itr2->first << ", " << *ptr2 <<endl;
        }
    }
}

// Tulostaa kaikki tietyssä paikassa esiintyvät artistit
// parametrina viite kalenteriin ja paikka stringinä
void print_artists_stages(Calendar& gig_calendar, string stage){
    cout << "Stage " << stage << " has gigs of the following artists:"<<endl;
    map<string, map<string, pair<string, string>>>::iterator itr;
    map<string, pair<string,string>>::iterator ptr;
    for(itr = gig_calendar.begin(); itr != gig_calendar.end(); itr++){
        for(ptr = itr->second.begin(); ptr != itr->second.end(); ptr++){
            if (ptr->second.second == stage){
                cout << " - " << itr->first << endl;
            }
        }
    }
}

// Syötetiedoston kysyminen ja sen olemassaolon tarkistaminen.
// Tiedostosta luetaan rivi kerrallaan tietoa ja sitä syötetään
// add_data_to_structure funktiolle, jossa suoritetaan jatkotarkastukset ja
// lisäys tietorakenteeseen.
// Kun tiedosto on käyty onnistuneesti läpi, siirrytään vaiheeseen jossa käyttäjältä
// kysellään käskyjä. Tätä jatkuu kunnes lopetuskäsky syötetään tai kunnes tapahtuu virhe

int main()
{

    Calendar gig_calendar;
    vector<string> places;
    string file;
    cout << "Give a name for input file: ";
    cin >> file;
    ifstream file_object(file);
    if (not file_object){
        cout << "Error: File could not be read."<< endl;
        return EXIT_FAILURE;
    }
    else{
        string line = "";
        while (getline(file_object, line)){
            vector<string> one_line_split = split(line);
            if(one_line_split.size() != 4){
                cout <<"Error: Invalid format in file."<< endl;
                return EXIT_FAILURE;
            }
            else{
                for (int i=0; i < 4; i++){
                    if(one_line_split.at(i) == ""){
                        cout<< "Error: Invalid format in file."<< endl;
                        return EXIT_FAILURE;
                    }
                }
            }
            if (add_to_data_structure(one_line_split, gig_calendar, places) == 0){
               return EXIT_FAILURE;
            }
        }
    }
//käyttäjän syötteiden luku alkaa
    string input = "";
    cout << "gigs> ";
    while (getline(cin, input)){
        if(input == ""){
            continue;
        }
        vector<string> input_vector = split_input(input);
        if (input_vector.at(0) == "QUIT" or input_vector.at(0) == "quit"){
            return EXIT_SUCCESS;
        }
        else if(input_vector.at(0) == "ARTISTS" or input_vector.at(0) == "artists"){
            print_artists(gig_calendar);
        }
        else if(input_vector.at(0) == "ARTIST" or  input_vector.at(0) == "artist"){
            vector<string>::size_type length = input_vector.size();
            int size = length;
            if(size < 2){
                cout << "Error: Invalid input."<<endl;
            }
            else if(gig_calendar.find(input_vector.at(1)) == gig_calendar.end()){
                cout << "Error: Not found."<<endl;
            }
            else{
                string artist = input_vector.at(1);
                print_gigs(gig_calendar, artist);
            }
        }
        else if(input_vector.at(0) == "STAGES" or input_vector.at(0) == "stages"){
            print_stages(gig_calendar);
        }
        else if(input_vector.at(0) == "STAGE" or input_vector.at(0) == "stage"){
            vector<string>::size_type length = input_vector.size();
            int size = length;
            if(size < 2){
                cout << "Error: Invalid input."<<endl;
            }
            else if(find(places.begin(), places.end(), input_vector.at(1)) == places.end()){
                cout << "Error: Not found."<<endl;
            }
            else{
                string stage = input_vector.at(1);
                print_artists_stages(gig_calendar, stage);
            }
        }
        cout << "gigs> ";
    }

    return EXIT_SUCCESS;

}
