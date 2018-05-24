#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include "mytime.h"

using namespace std;

class RoundRecord
{
private:
    Time start_time;
    Time end_time;
    int time_cost;
    int question_id;
    int player_id;
    char response;
    bool isCorrect;

public:
    RoundRecord();
    RoundRecord(Time start_time, Time end_time, int question_id, int player_id, char response, bool isCorrect);
    ~RoundRecord();
};