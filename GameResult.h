#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class GameResult
{
private:
    int exp;
    int goldcoin;
public:
    void add_exp(int dexp);
    void dec_exp(int dexp);
    void add_goldcoin(int dgoldcoin);
    void dec_goldcoin(int dgoldcoin);
};