#include "questionbank.h"

Questionbank::Questionbank() {
    question_num = 0;
}

Questionbank::~Questionbank() {}

Question Questionbank::get_question(int k) {
    ifstream fin(this->file_addr);
    if(!fin)
        cout << "OPEN FILE FAILED." << endl;
        fin.close();
        return Question();
    else
    {
        string str;
        for(int i = 0; i < k; i++)
            getline(fin,str);
        fin.close();
        size_t last = 0, found;
        string str_tem[5];
        char ans;
        for(int i = 0; i < 5; i ++) {
            found = str.find_first_of(" ");
            str_tem[i] = str.substr( last, found - last);
            last = found + 1;
            str[found] = '*';
        }
        ans = str[str.size() - 1];
        Question tem_ques(str[0], str[1], str[2], str[3], str[4], ans);
        return tem_ques;
    }
}


void Question::put_question(Question ques) {
    ofstream fout(this->file_addr,ios::app|ios::out);
    if(!fout) cout << "OPEN FILE FAILED." <<endl;
    fout << ques.question_body << " " << ques.option_A << " " << ques.option_B << " " << ques.option_C << " " << ques.option_D << " " << ques.answer;
    fout.close();
}