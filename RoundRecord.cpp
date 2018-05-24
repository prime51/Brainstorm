#include "RoundRecord.h"

RoundRecord::RoundRecord(){}

RoundRecord::RoundRecord(Time start, Time end, int ques_id, int id, char resp, bool isCor) {
    start_time = start;
    end_time = end;
    time_cost = start - end;
    question_id = ques_id;
    player_id = id;
    response = resp;
    isCorrect = isCor;
}

RoundRecord::~RoundRecord(){}