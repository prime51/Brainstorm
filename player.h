#pragma once

#include <string>
#include <vector>
#include "mytime.h"

using namespace std;

class Player
{
struct Record //  the struct to record the information of one question
{
    int question_num;       //record the question number
    Time start_time;        //record the start time
    Time end_time;          //record the end time
    int time_cost;          //record the time player cost on responding this question
    char respond;           //record the player's respond
    char answer;            //record the answer of the question
    bool result;            //record the result of the question
    Record(int,Time);
    void set_start_time(Time);
    void set_end_time(Time);
    void set_respond(char);
    void set_answer(char);
    void set_result(bool);
    void set_time_cost(int);
};
public:
    Player(int);
    ~Player();
    void push_record();     //add a record into the vector

    void select_answer();   //the function for player to select the respond
    int get_number();       //the function to get the number of the player
    string get_name();      //the function to get the name of the player
    int get_right_sum();    //the function to get the number of question that the player respond rightly
    Time get_start_time();  //the function to get the start time
    int get_time_cost();    //the function to get the time cost

private:
    int number;             //players' id
    int right_sum;          //the number of question that player respond rightly
    Time game_start_time;   //the sart time player start the game
    int game_time_cost;     //the time player cost on the game
    vector<Record> myrecord;
};