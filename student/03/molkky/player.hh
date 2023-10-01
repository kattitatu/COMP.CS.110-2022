#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

class Player
{
public:
    Player(const std::string name, int points = 0);
    std::string get_name();
    int get_points();
    bool has_won();
    void add_points(int points_toadd);
private:
    const std::string name;
    int points = 0;
};

#endif // PLAYER_HH
