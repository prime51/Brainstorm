#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class GameRecord
{
private:
    Time start_time;
    Time end_time;
    int time_cost;
    int player_id;
    bool result;
    int question_num;
    int right_num;
    vector<RoundRecord> round_list;

public:
    GameRecord( Time, Time, int, int, bool, int, int);
    ~GameRecord();
    Time get_start_time();
    Time get_end_time();
    int get_time_cost();
    int get_player_id();
    bool get_result();
    int get_question_num();
    int get_right_num();
    vector<RoundRecord> get_round_list();
    RoundRecord get_round_record(int round_index);
};