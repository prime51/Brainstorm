#include "GameRecord.h"
GameRecord::GameRecord(){}

GameRecord::GameRecord(Time t1, Time t2, int cost, int id, bool res, int q_num, int r_num) {
    this->start_time = t1;
    this->end_time = t2;
    this->time_cost = cost;
    this->player_id = id;
    this->result = res;
    this->qestion_num = q_num;
    this->right_num = r_num; 
}

GameRecord::~GameRecord(){}

Time GameRecord::get_start_time() {
    return this->start_time;
}

Time GameRecord::get_end_time() {
    return this->end_time;
}

int GameRecord::get_time_cost() {
    return this->time_cost;
}

int GameRecord::get_player_id() {
    return this->player_id;
}

bool GameRecord::get_result() {
    return this->result;
}

int GameRecord::get_question_num() {
    return this->question_num;
}

int GameRecord::get_right_num() {
    return this->right_num;
}

vector<RoundRecord> GameRecord::get_round_list() {
    return this->round_list;
}

RoundRecord GameRecord::get_round_record(int round_index) {
    return this->round_list[round_index];
}