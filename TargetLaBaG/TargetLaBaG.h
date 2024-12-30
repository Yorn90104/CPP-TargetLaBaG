#pragma once

#include "P.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

class TargetLaBaG
{
public:
    int score;
    map<string, map<string, int>> AllData;

    TargetLaBaG();

    bool GameRunning() const;
    void GameLogic();

private:
    int times;
    int played;
    int margin_score;

    map<string, int> OneData;
    int DataIndex;

    map<string, int> score_time_map;
    int score_time;

    map<string, P> P_Map;
    string sequence[6];
    P Ps[3];

    void Reset();
    string NowMod();
    vector<int> acc_rate();
    void Random();
    void GetScore(P p, int typ);
    void CalculateScore();
    void Result();


    bool SuperHHH;
    int SuperRate;
    int SuperTimes;
    int SuperNum;

    void SuperFalse();
    void SuperRandom();
    void JudgeSuper();


    bool GreenWei;
    int GreenRate;
    int GreenTimes;
    int GreenNum;
    int gss_times;

    void GreenFalse();
    void GreenRandom();
    void JudgeGreen();


    bool PiKaChu;
    int kachu_times;

    void KachuFalse();
    void JudgeKaChu();
};
