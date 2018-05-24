# include "user.h"

User::User(){}

User::~User(){}

void User::set_name(string name) {
    this->nick_name = nam;
    cout << "You have already reset your nick_name." << endl;
}

void User::set_avatar(string rute) {
    this->avatar = rute;
    cout << "You have already reset your avatar." << endl;
}

int User::select_game_type() {
    int select;
    cin >> select;
    
    /* switch (select)
    {
        case 1:
            // 训练模式
            
            break;
        case 2:
            // PK对战模式
            break;
        default:
            break;
    } */
    return select;
}

int User::select_interface_style() {
    int select;
    cin >> select;
    /* switch (select)
    {
        case 1:
            // style 1
            
            break;
        case 2:
            // style 2
            break;
        default:
            break;
    } */
    return select;
}

void User::show_avatar() {

}

void User::show_exp() const {
    cout << this->exp << endl;
}

void User::show_goldcoin() const {
    cout << this->goldcoin << endl;
}

void User::show_level() const {
    cout << this->level << endl;
}

void User::show_max_exp() const {
    cout << this->max_exp << endl;
}

void User::show_name() const {
    cout << this->nick_name << endl;
}

void User::show_total_sum() const {
    cout << this->total_sum << endl; 
}

void User::show_user_id() const {
    cout << this->user_id << endl;
}

void User::show_win_rate() const {
    cout << this->win_rate << endl;
}

void User::show_win_sum() const {
    cout << this->win_sum << endl;
}

bool User::start_game() const {
    return true;
}

Question User::submit_new_question() const {
    Question new_ques;
    string ques_body, option_A, option_B, option_C, option_D;
    char answer;
    cout << "Please enter your question here." << endl;
    getline(cin, ques_body);
    getline(cin, option_A);
    getline(cin, option_B);
    getline(cin, option_C);
    getline(cin, option_D);
    getchar();
    answer = getchar();
    new_quess.set_question_answer(answer);
    new_quess.set_question_body(question_body);
    new_quess.set_question_option_A(option_A);
    new_quess.set_question_option_B(option_B);
    new_quess.set_question_option_C(option_C);
    new_quess.set_question_option_D(option_D);
    new_quess.set_question_number(question_num);

    return new_ques;
}
