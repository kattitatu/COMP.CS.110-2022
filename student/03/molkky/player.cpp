#include "player.hh"
#include <string>
Player::Player( const std::string name, int points):
    name(name), points(points)


{

}
std::string Player::get_name(){
    return name;
}

int Player::get_points(){
    return points;
}

void Player::add_points(int points_toadd){
    if (points + points_toadd > 50){
        points = 25;
    }
    else{
        points += points_toadd;
    }
}
bool Player::has_won(){
    if (points == 50){
        return true;
    }
    else{
        return false;
    }
}
