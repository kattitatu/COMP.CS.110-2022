#include "row.hh"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
/*
Ohjelman kirjoittaja
 * Nimi: Heikki Malmirae
 * Opiskelijanumero: 150412373
 * Käyttäjätunnus: mdhema
 * E-Mail: heikki.malmirae@tuni.fi
*/

string full_state = "";

Row::Row(const vector<char> colors):
    colors(colors)

{

}
void Row::result_for_guess(const Row& secret){
    vector<char> already_rewarded_colors_removed = secret.colors;
    vector<char> already_rewarded_colors_removed_guess = colors;
    int correct = 0;
    int correct_color = 0;    
    vector<char> temporary_for_storing = {};
    vector<char> temporary_for_storing_guess = {};
    for (int index = 0; index < 4; index++){
        char element = already_rewarded_colors_removed_guess.at(index);
        if(find(already_rewarded_colors_removed.begin(), already_rewarded_colors_removed.end(), element) != already_rewarded_colors_removed.end()){
            if (already_rewarded_colors_removed_guess.at(index) == already_rewarded_colors_removed.at(index)){
                correct += 1;                
                for (int i = 0; i < 4; i++){
                    if ( i != index ){                        
                        temporary_for_storing.push_back(already_rewarded_colors_removed.at(i));
                        temporary_for_storing_guess.push_back(already_rewarded_colors_removed_guess.at(i));
                    }
                    else{
                        temporary_for_storing.push_back('A');
                        temporary_for_storing_guess.push_back('C');
                    }
                }
                if ( temporary_for_storing.size() != 0){
                    already_rewarded_colors_removed = temporary_for_storing;
                    temporary_for_storing = {};
                    already_rewarded_colors_removed_guess = temporary_for_storing_guess;
                    temporary_for_storing_guess = {};
            }           
         }
     }
    }
    for (int i = 0; i < 4;i++){
        char element = already_rewarded_colors_removed_guess.at(i);
        if (find(already_rewarded_colors_removed.begin(), already_rewarded_colors_removed.end(), element) != already_rewarded_colors_removed.end()){
            correct_color++;
            auto it = find(already_rewarded_colors_removed.begin(), already_rewarded_colors_removed.end(), element);
            int index_where_found = distance(already_rewarded_colors_removed.begin(), it);
            for (int i2 = 0; i2 < 4; i2++){
                if( i2 == i and i2 != index_where_found  ){
                    temporary_for_storing.push_back(already_rewarded_colors_removed.at(i2));
                    temporary_for_storing_guess.push_back('C');
                }
                else if (i2 == i and i2 == index_where_found){
                    temporary_for_storing.push_back('A');
                    temporary_for_storing_guess.push_back('C');
                }
                else if(i2 != i and i2 == index_where_found){
                    temporary_for_storing.push_back('A');
                    temporary_for_storing_guess.push_back(already_rewarded_colors_removed_guess.at(i2));
                }
                else{
                    temporary_for_storing_guess.push_back(already_rewarded_colors_removed_guess.at(i2));
                    temporary_for_storing.push_back(already_rewarded_colors_removed.at(i2));
                }

            }

            if ( temporary_for_storing.size() != 0){
                already_rewarded_colors_removed = temporary_for_storing;
                temporary_for_storing = {};
                already_rewarded_colors_removed_guess = temporary_for_storing_guess;
                temporary_for_storing_guess = {};
            }
        }

    }
    print_state(colors, correct, correct_color);
}

void Row::print_state(vector<char> colors, int correct, int correct_color){
    full_state += "\n| ";

    for ( char c : colors){
        string s{c};
        full_state += s + " ";
    }
    full_state += "| " + to_string(correct) + " | " + to_string(correct_color) + " |" ;
    cout << full_state << endl;;

}
