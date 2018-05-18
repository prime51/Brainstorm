#pragma once
#include <ctime>
#include <iostream>
using namespace std;

class Time
{
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

public:
    Time(int, int, int, int, int, int);
    ~Time();
    void set_Time();
    void show_cur_Time();
};