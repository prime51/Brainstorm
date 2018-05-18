#pragma once

#include <string>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

class Question
{
public:
    Question();
    ~Question();
    void set_question_answer(char);
    void set_question_type(string);
    void set_question_body(string);
    void set_question_option_A(string);
    void set_question_option_B(string);
    void set_question_option_C(string);
    void set_question_option_D(string);
    void set_question_number(int);

    char get_question_answer();
    string get_question_type();
    string get_question_body();
    string get_question_option_A();
    string get_question_option_B();
    string get_question_option_C();
    string get_question_option_D();

  private:
    int number;
    char question_answer;
    string question_type;
    string question_body;
    string option_A;
    string option_B;
    string option_C;
    string option_D;
};