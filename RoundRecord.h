#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class RoundRecord
{
private:
    Time start_time;
    Time end_time;
    int time_cost;
    int question_id;
    int player_1;
    int player_2;
    char response_1;
    char response_2;

public:
    RoundRecord( Time, Time, int, int, int, int, char, char);
    ~RoundRecord();
};