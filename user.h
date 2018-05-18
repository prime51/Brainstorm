#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <cstring>

using namespace std;

class User
{
public:
    user(int);
    ~user();
    void set_name(string);
    void set_avatar(string);
    void level_up();
    void gain_expe();
    void gain_goldcoin();
    void select_interface_style();

    void show_info();       //print the information of the user
    void show_user_id();
    void show_name();
    void show_avatar();
    void show_level();
    void show_expe();
    void show_max_expe();
    void show_goldcoin();
    void show_win_rate();
    void show_total_sum();
    void show_win_sum();

    int select_game_type();
    int select_interface_style();
    void submit_new_question();
    void invite_friend();

private:
    string user_id;         //users' id
    string name;            //user's name
    string avatar;          //user's avatar
    int level;              //user's level
    int expe;               //user's current experience value
    int max_expe;           //the maximum experience user to level up 
    int goldcoin;           //user's money
    int interface_style;    //the interface style user choosed
    double win_rate         //user's rate to win a game
    int total_sum;          //user has played total_sum games
    int win_sum;            //user has wined win_sum games
};