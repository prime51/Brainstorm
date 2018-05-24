#include "player.h"

Player::Player(int player_id = 0) {
    num = player_id;
}

~Player() {}

void push_record(Record rec){ //add a record into the vector
    myrecord.push_back(rec);
}

char select_answer() {  //the function for player to select the respond
    char sel;
    cin >> sel;
    return sel;
}
int get_number(){ return number; }      //the function to get the number of the player
string get_name(){ return name; }     //the function to get the name of the player
int get_right_sum() { return right_sum; }  //the function to get the number of question that the player respond rightly
Time get_start_time() { return game_start_time; } //the function to get the start time
int get_time_cost() { return game_time_cost; }   //the function to get the time cost