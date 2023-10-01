/*
#############################################################################
# COMP.CS.110 Programming 2, Autumn 2022                                    #
# Project3: Book contents                                                   #
# Program description: Queries user for CSV file and allows simple searches #
#       based on the data.                                                  #
# File: main.cpp                                                            #
# Description: Main-module performs the followin operations:                #
#       * Queries for input file                                            #
#       * Parses the CSV data                                               #
#       * Passes the parsed data to Book class                              #
#       * Launches Cli module                                               #
# Notes: * This is an exercise program.                                     #
#        * Student's don't touch this file.                                 #
#############################################################################
*/
/* Kirjan sisältö
 * Ohjelma lukee käynnistyessään kirjan lukujen tietoja
 * käyttäjän antamasta syötetiedostosta. Muodostaa näistä
 * tiedoista kirjan jossa kappaleiden välisiä hierarkioita.
 * Kirjan luvuilla siis voi olla alilukuja, joilla voi olla edelleen
 * alilukuja.
 * Käyttäjä voi tehdä kirjaan kohdistuvia hakuja sekä pieniä muutoksia.
 * "QUIT" sulkee ohjelman, "IDS" Tulostaa kaikki ohjelmaan tallennetut
 * kirjan luvut tunnisteineen.
 * "CONTENTS" tulostaa kirjan sisällysluet-
 * telon lukuunottamatta suljettujen lukujen alilukuja.
 * "CLOSE <ID>" sulkee annetun luvun sekä tämän aliluvut
 * "OPEN <ID>" avaa annetun luvun
 * "OPEN_ALL" avaa kaikki kirjan luvut
 * "PARENTS <ID> <N>" Tulostaa ID:n vanhempiluvut tasolle N asti, eli N:n arvolla 1
 * tulostetaan ID:n suora vanhempiluku, N:n arvolla 2 lisäksi myös suoran vanhempiluvun suora
 * vanhempiluku jne.
 * "SUBCHAPTERS <ID> <N>" Tulostaa ID:n aliluvut tasolle N asti,
 * eli N:n arvolla 1 tulostetaan ID:n suorat aliluvut, N:n arvolla 2 lisäksi myös
 * suorien alilukujen suorat aliluvut jne.
 * "SIBLINGS <ID> <N>"  Tulostaa ID:n sisarluvut(eli sellaiset luvut, joilla on sama
 *  suora vanhempiluku kuin ID:llä). Luku ei ole itsensä sisarluku.
 * "LENGTH <ID>" LENGTH <ID> - Tulostaa annetun luvun kokonaispituuden eli luvun ja sen
 * kaikkien alilukujen yhteenlasketun pituuden. Aliluvut huomioidaan niin pitkälle, kuin niitä riittää.
 * "LONGEST <ID>" Tulostaa pisimmän luvun annetun luvun hierarkiassa, eli tarkastelu aloitetaan luvusta
 * ID ja otetaan huomioon myös ID:n kaikki aliluvut.
 * "SHORTEST <ID>" Tulostaa lyhyimmän luvun annetun luvun hierarkiassa, eli tarkastelu aloitetaan luvusta
 * ID ja otetaan huomioon myös ID:n kaikki aliluvut.
 *
 *

 *
 * Ohjelman kirjoittaja
 * Nimi: Heikki Malmirae
 * Opiskelijanumero: 150412373
 * Käyttäjätunnus: mdhema
 * E-Mail: heikki.malmirae@tuni.fi
 *
 *
*/

#include "book.hh"
#include "cli.hh"
#include "utils.hh"
#include <iostream>
#include <string>

int main()
{
    std::string fileName = "";
    std::shared_ptr<Book> database(new Book);

    // File query and opening
    std::cout << "Input file: ";
    std::getline(std::cin, fileName);
    if ( not Utils::readInputFile(fileName, database) )
    {
        return EXIT_FAILURE;
    }

    // Constructing the commandline interpreter with the datastructure
    // formed based on the given input file
    Cli commandline(database);

    // Empty loop that runs the CLI.
    // CLI returns false only on quit command.
    while ( commandline.execPrompt() );

    return EXIT_SUCCESS;
}
