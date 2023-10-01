#ifndef ROW_HH
#define ROW_HH
#include <vector>
/* Luokan Row otsikkotiedosto
 * Luokan Row oliot sisältävät merkeistä koostuvan vektorin joka kuvaa arvattua riviä
 *
Ohjelman kirjoittaja
 * Nimi: Heikki Malmirae
 * Opiskelijanumero: 150412373
 * Käyttäjätunnus: mdhema
 * E-Mail: heikki.malmirae@tuni.fi
*/

using namespace std;

class Row
{
public:
    Row(const vector<char> colors);
    // Metodi, joka laskee pelaajan arvaukselle pisteet.
    // Kutsuu sen jälkeen metodia print_state
    // parametrina viittaus vakioon - salaiseen riviin.
    void result_for_guess(const Row& secret);
    // Tulostaa välimerkkirivien väliin kuuluvan merkkijonon
    // jossa pelaajan arvaukset siihen mennessä ja niiden pisteet
    void print_state(vector<char> colors, int correct, int correct_color);
private:
    const vector<char> colors;


};

#endif // ROW_HH
