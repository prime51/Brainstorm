#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <cstring>
#include "question.h"

using namespace std;

class Questionbank::class Question
{
public:
    Question get_question(int);
    void put_question(Question);
private:
    int question_num;
    const string file_addr;
};