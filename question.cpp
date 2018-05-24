#include "question.h"

Question::Question(){}
Question::~Question(){}
void Question::set_question_answer(const char ans) {
    this->answer = ans;
}

void Question::set_question_type(const string *type) {
    this->question_type = type;
}

void Question::set_question_body(const string *body) {
    this->question_body = body;
}

void Question::set_question_option_A(const string *A) {
    this->option_A = A;
}

void Question::set_question_option_B(const string *B) {
    this->option_B = B;
}

void Question::set_question_option_C(const string *C) {
    this->option_C = C;
}

void Question::set_question_option_D(const string *D) {
    this->option_D = D;
}

void Question::set_question_number(int num) {
    this->question_num = num;
}

char Question::get_question_answer() { return this->question_answer; }
string Question::get_question_type() { return this->question_type; }
string Question::get_question_body() { return this->question_body; }
string Question::get_question_option_A() { return this->option_A; }
string Question::get_question_option_B() { return this->option_B; }
string Question::get_question_option_C() { return this->option_C; }
string Question::get_question_option_D() { return this->option_D; }
