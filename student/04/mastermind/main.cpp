
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctype.h>
#include "row.hh"
/* Mastermind
* Kuvaus:
 *   Ohjelma toteuttaa Mastermind-pelin. Pelissä annetaan tai arvotaan
 * ensin salainen neljän värin sarja. Sama väri voi esiintyä sarjassa
 * useita kertoja, mutta mikään neljästä positiosta ei voi olla tyhjä.
 * Kaikkien annettujen värien pitää löytyä pelissä käytössä olevista väreistä.
 * Käyttäjä yrittää arvata, mitkä värit esiintyvät sarjassa ja missä
 * järjestyksessä. Tätä varten käyttäjä antaa oman neljän värin sarjansa,
 * ja ohjelma ilmoittaa, kuinka monta väriarvausta meni täysin oikein
 * (oikea väri oikeassa positiossa) sekä kuinka monta arvausta meni
 * pelkästään värin osalta oikein (oikea väri väärässä positiossa).
 * Tämän jälkeen käyttäjä voi tehdä uuden arvauksen jne.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla väreillä vai käyttäjän luettelemilla väreillä.
 * (Jälkimmäinen tapa ei ole kovin järkevä, mutta se on hyödyllinen
 * testauksen kannalta.) Ensimmäisessä vaihtoehdossa käyttäjältä kysytään
 * satunnaislukugeneraattorin siemenlukua ja jälkimmäisessä häntä
 * pyydetään syöttämään neljä väriä (värien alkukirjaimet eli neljän
 * merkin mittainen merkkijono).
 *   Joka kierroksella käyttäjältä kysytään uutta arvausta. Peli päättyy
 * pelaajan voittoon, jos arvaus menee jokaisen värin kohdalta täysin
 * oikein. Peli päättyy pelaajan häviöön, jos hän ei ole arvannut oikein
 * maksimimäärällä (10) arvauskertoja.
 *   Ohjelma tarkistaa, että annetut värit kuuluvat sallittujen värien
 * joukkoon. Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 * Ohjelman kirjoittaja
 * Nimi: Heikki Malmirae
 * Opiskelijanumero: 150412373
 * Käyttäjätunnus: mdhema
 * E-Mail: heikki.malmirae@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * Aloin toteuttaa ohjelmaa hyödyntäen valmiiksi annettau templatea,
 * näin jälkikäteen ajatellen olisi pitänyt tehdä toisin.
 * Oma ajatus pelin toteuttamisesta ei ihan täysin istunutkaan template koodiin
 * ja jotkin ratkaisut olisi voinut toteuttaa huomattavasti
 * järkevämminkin. Esimerkiksi funktiot kutsuivat toisiaan vuoron perään,
 * mikä tekee mainista hieman epäselvän kun pelin kulku ei kokonaisuudessaan siellä näkyvillä.
 * Muutama ongelmakin tuli mihin en globaalia muuttujaa parempaa ratkaisua keksinyt. Kun esimerkiksi
 * piti kutsua funktion sisältä toista funktiota, mutta tarvittava parametri ei tälle kutsujafunktiolle
 * ollut tuttu, eikä sitä sille voinut mistään välittää. Tämäkin olisi voinut ratketa suun-
 * nittelemalla mainin paremmin.
 * Ohjelmassa on siis kokoajan vain kaksi "Row" luokan oliota (secret ja guess)
 * guess olion atribuutti-row siis muuttuu jokaisen arvauksen jälkeen.
 * Pisteytyksessä tuloste-stringiin kerätään rivi kerralla muistiin pelin kulkua ja siten vanhat arvaukset
 * pysyvät muistissa. Itse pisteiden laskenta meni myös melko monimutkaiseksi ja pitkäksi metodiksi
 *
 *
*/

using namespace std;
// Maximum number of guesses
const int GUESS_MAX = 10;
// Number of colors in a series
const unsigned int SIZE = 4;

// Length of the suffix part when printing a row.
// The suffix consists of three vertical lines ('|') and two digits, where one
// tells the amount of totally correct colors and the other tells the amount
// of correct colors in incorrect positions.
const unsigned int SUFFIX_LENGTH_IN_PRINT = 5;

// Text printed at the beginning of the program
const string INFO_TEXT = "Colors in use: \
B = Blue, R = Red, Y = Yellow, G = Green, O = Orange, V = Violet";
vector<char> secret_row;


// Generoi satunnaisen salaisen väririvin. Tallentaa sen vektoriin kirjaimina
// ja luo Row-luokan olion.
void generate_random_row(int seed){
    default_random_engine gen(seed);
    uniform_int_distribution<int> distribution(0, 5);
    vector<char> colors_as_characters = {'B', 'R', 'Y', 'G', 'O', 'V'};
    for ( int i = 0; i < 5; i++){
        char color = colors_as_characters.at(distribution(gen));
        secret_row.push_back(color);
    }
    Row secret(secret_row);

}
    //Printtaa rivin joka koostuu annetusta merkistä c
    void print_line_with_char(char c, unsigned int line_length)
    {
        for(unsigned int i = 0; i < line_length; ++i)
        {
            cout << c;
        }
        if (c == '*'){
            cout << endl;
        }
    }

// Tulostaa jokaisen arvauksen jälkeen kaksi riviä välimerkkejä
// Näiden välimerkki rivien väliin tulostetaan pelaajan arvaus ja tulos arvaukselle
void print_all(Row guess, Row secret)
{
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
    guess.result_for_guess(secret);
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);

}

// Tutkii pelaajan syöttämän salaisen rivin laatua ja myös arvausten laatua.
// mikäli syötetty rivi hyväksytään ja se oli arvaus, kutsutaan funktiota print_all()
// Tutkii myös arvausten kohdalla voittiko pelaaja, palauttaa mainille tiedon,
// että jatkuuko peli vielä.
int row_input_check(string colors, bool is_secret=false){
    const vector<char> colors_accepted = {'B', 'R', 'Y', 'G', 'O', 'V'};
    vector<char> row;

    string::size_type number_of_letters = colors.length();
    int length_as_int = number_of_letters;
    if (length_as_int != 4){
        cout << "Wrong size"<< endl;
        return 0;
    }
    for ( int index = 0; index < length_as_int; index++){
        char element = toupper(colors.at(index));
        if (std::find(colors_accepted.begin(), colors_accepted.end(), element) != colors_accepted.end()){
            if(is_secret == true){
                secret_row.push_back(element);
            }
            else{
                row.push_back(element);
            }
        }
        else{
            cout << "Unknown color" <<endl;
            return 0;
        }

    }
    if (row == secret_row){
        Row guess(row);
        Row secret(secret_row);
        print_all(guess, secret);
        cout << "\nYou won: Congratulations!" << endl;
        return 2;
    }
    else{
        if (is_secret == false and row != secret_row){
            Row guess(row);
            Row secret(secret_row);
            print_all(guess, secret);           
        }

        else{
            Row secret(secret_row);           
        }

    }
return 1;
}

// Kysyy pelin alussa haluaako pelaaja satunnaisen salaisen rivin vai haluaako päättää itse
// Tarkastaa myös syötteet ja huomauttaa jos syöte ei kelpaa.
// Jos pelaaja valitsee satunnaisen, niin kutsutaan generate_random_row, jonka parametrina
// pelaajan antama seed.
// Jos pelaaja taas haluaa itse syöttää salaisen rivin, lähettää stringinä rivin
// row_input_check:ille tarkastettavaksi ja eteenpäin mikäli se kelpaa. Jatkaa kysymistä kunnes
// kelpaava rivi on syötetty.
void get_input()
{
    cout << "Enter an input way (R = random, L = list): ";
    string input_str = "";
    cin >> input_str;
    bool is_secret = true;
    if(input_str == "R" or input_str == "r")
    {       
        cout << "Enter a seed value: ";
        int seed = 0;
        cin >> seed;
        generate_random_row(seed);

    }
    else if(input_str == "L" or input_str == "l")
    {
        bool accepted = false;
        while(not accepted)
        {
            cout << "Enter four colors (four letters without spaces): ";
            string colors = "";
            cin >> colors;
            is_secret=true;
            if(row_input_check(colors, is_secret) == 1){
                accepted = true;
            }
        }
    }
    else
    {
        cout << "Bad input" << endl;      
        get_input();
    }
}






//Täällä peli alkaa ja kulkee.
// varsinainen pelin kulku while-loopissa, joka rikkoutuu jos
// kymmeneen vuoroon ei ole arvattu oikein tai jos row_input_check palauttaa
// arvon 2, eli peli on voitettu
// Pelin kulku myös lopetetaan jos käyttäjä söyttää kehotteeseen 'q'.
int main()
{
    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());

    // TODO: Declare an object for a color series (the secret one)
    get_input();
    int turn = 1;
    while (turn <= GUESS_MAX){
        bool check_passed = false;
        while (check_passed != true){
            if (turn == 1){
                cout << "ROW> ";
            }
            else{
                cout << "\nROW> ";
            }
            string guessed_row;
            cin >> guessed_row;

            if (guessed_row == "Q" or guessed_row == "q" ){
                exit(EXIT_SUCCESS);
            }
            else{
                int results = row_input_check(guessed_row);

                if(results == 2) {
                    exit(EXIT_SUCCESS);
                }
                else if (results == 1){
                    turn++;
                    check_passed = true;
                }

            }
        }
    }
    cout << "\nYou lost: Maximum number of guesses done"<<endl;;
    return 0;

}




