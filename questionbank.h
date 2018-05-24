#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <cstring>
#include "question.h"

using namespace std;

class Questionbank::publci:class Question
{
public:
    Questionbank();
    ~Questionbank();
    Question get_question(int question_num);
    void put_question(const Question* new_question);
private:
    const string file_addr = "questionbank.txt"; 
    int question_num;
};