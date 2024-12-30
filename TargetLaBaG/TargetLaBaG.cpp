#include "TargetLaBaG.h"
#include <algorithm> // all of(), any_of()
using namespace std;

// 構造函數
TargetLaBaG::TargetLaBaG() :
    DataIndex(0),
    times(30),
    played(0),
    score(0),
    margin_score(0),
    score_time_map({
        {"Normal", 1},
        {"SuperHHH", 1},
        {"GreenWei", 3},
        {"PiKaChu", 1}
        }),
    score_time(1),
    SuperHHH(false),
    SuperRate(15),
    SuperTimes(0),
    SuperNum(0),
    GreenWei(false),
    GreenRate(35), GreenTimes(0),
    GreenNum(0),
    gss_times(0),
    PiKaChu(false),
    kachu_times(0)
{
    int AScores[3] = { 625, 350, 150 };
    map<string, int> ARate = { {"Normal", 36}, {"SuperHHH", 19}, {"GreenWei", 36}, {"PiKaChu", 36} };
    P_Map["A"] = P("A", AScores, ARate);

    int BScores[3] = { 1250, 650, 220 };
    map<string, int> BRate = { {"Normal", 24}, {"SuperHHH", 5}, {"GreenWei", 24}, {"PiKaChu", 24} };
    P_Map["B"] = P("B", BScores, BRate);

    int CScores[3] = { 2100, 1080, 380 };
    map<string, int> CRate = { {"Normal", 17}, {"SuperHHH", 19}, {"GreenWei", 17}, {"PiKaChu", 17} };
    P_Map["C"] = P("C", CScores, CRate);

    int DScores[3] = { 2500, 1250, 420 };
    map<string, int> DRate = { {"Normal", 12}, {"SuperHHH", 19}, {"GreenWei", 12}, {"PiKaChu", 12} };
    P_Map["D"] = P("D", DScores, DRate);

    int EScores[3] = { 10000, 5000, 1250 };
    map<string, int> ERate = { {"Normal", 8}, {"SuperHHH", 19}, {"GreenWei", 8}, {"PiKaChu", 8} };
    P_Map["E"] = P("E", EScores, ERate);

    int FScores[3] = { 20000, 10000, 2500 };
    map<string, int> FRate = { {"Normal", 3}, {"SuperHHH", 19}, {"GreenWei", 3}, {"PiKaChu", 3} };
    P_Map["F"] = P("F", FScores, FRate);

    string seq[6] = { "A", "B", "C", "D", "E", "F" };
    for (int i = 0; i < 6; i++) {
        sequence[i] = seq[i];
    }
}

// 遊戲是否運行
bool TargetLaBaG::GameRunning() const
{
    return played < times;
}

//遊戲內部邏輯流程
void TargetLaBaG::GameLogic()
{   
    Reset();
    AllData.clear();
    DataIndex = 0;
    while (GameRunning())
    {
        OneData.clear();
        Random();
        JudgeSuper();
        CalculateScore();
        JudgeGreen();
        Result();
        JudgeKaChu();
    }
}

//重制
void TargetLaBaG::Reset()
{
    played = 0;
    score = 0;
    margin_score = 0;
    score_time = 1;

    SuperHHH = false;
    SuperTimes = 0;

    GreenWei = false;
    GreenTimes = 0;
    gss_times = 0;

    PiKaChu = false;
    kachu_times = 0;
}

//現在模式
string TargetLaBaG::NowMod() {
    if (SuperHHH)
    {
        return "SuperHHH";
    }
    else if (GreenWei)
    {
        return "GreenWei";
    }
    else if (PiKaChu)
    {
        return "PiKaChu";
    }
    else
    {
        return "Normal";
    }
}

// 累積機率
vector<int> TargetLaBaG::acc_rate()
{
    int acc = 0;
    vector<int> res;
    for (int i = 0; i < 6; i++) {
        acc += P_Map[sequence[i]].Rate[NowMod()];
        res.push_back(acc);
    }
    return res;
}

// 隨機生成
void TargetLaBaG::Random()
{
    int rand_nums[3] = { rand() % 100 + 1, rand() % 100 + 1, rand() % 100 + 1 };

    for (int i = 0; i < 3; ++i) {
        OneData["RandNums[" + to_string(i) + "]"] = rand_nums[i];
    }

    vector<int> rate_range = acc_rate();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            if (rand_nums[i] <= rate_range[j]) {
                Ps[i] = P_Map[sequence[j]];
                break;
            }
        }
    }
}

// 根據情況獲取分數
void TargetLaBaG::GetScore(P p, int typ)
{
    margin_score += P_Map[p.code].Score[typ];
}
// 計算分數
void TargetLaBaG::CalculateScore()
{
    score_time = score_time_map[NowMod()];
   

    if (Ps[0] == Ps[1] && Ps[1] == Ps[2]) {
        GetScore(Ps[0], 0);
        margin_score *= score_time;
    }
    else if (Ps[0] == Ps[1] || Ps[1] == Ps[2] || Ps[2] == Ps[0]) {
        if (Ps[0] == Ps[1]) {
            GetScore(Ps[0], 1);
            GetScore(Ps[2], 2);
        }
        else if (Ps[1] == Ps[2]) {
            GetScore(Ps[1], 1);
            GetScore(Ps[0], 2);
        }
        else if (Ps[2] == Ps[0]) {
            GetScore(Ps[2], 1);
            GetScore(Ps[1], 2);
        }
        margin_score = margin_score * score_time * 10 / 13;
    }
    else {
        GetScore(Ps[0], 2);
        GetScore(Ps[1], 2);
        GetScore(Ps[2], 2);
        margin_score = margin_score * score_time / 3;
    }


}

// 輸出結果
void TargetLaBaG::Result()
{
    played++;
    DataIndex++;
    score += margin_score;
    margin_score = 0;
    AllData[to_string(DataIndex)] = OneData;
}

void TargetLaBaG::SuperFalse()
{
    SuperHHH = false;
}

void TargetLaBaG::SuperRandom()
{
    SuperNum = rand() % 100 + 1;
    OneData["SuperHHH"] = SuperNum;
}

void TargetLaBaG::JudgeSuper()
{
    if (!GameRunning())
    {
        SuperFalse();
        return;
    }

    SuperRandom();
    string mod = NowMod();
    if (mod.compare("SuperHHH") == 0)
    {
        SuperTimes -= 1;

        if (all_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "B";})) // & 表示以引用的方式傳遞參數
        {
            SuperTimes += 2;
        }
        if (SuperTimes <= 0)
        {
            SuperFalse();
        }
    }
    else if (mod.compare("Normal") == 0 || mod.compare("PiKaChu") == 0)
    {
        bool hhh_appear = false;
        if (any_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "B";}))
        {
            hhh_appear = true;
        }
        if (SuperNum <= SuperRate && hhh_appear)
        {
            SuperHHH = true;
            SuperTimes += 6;
            if (PiKaChu)
            {
                KachuFalse();
            }
            // 超級阿禾加倍
            if (all_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "B";}))
            {
                int double_score = score * score_time / 2;
                margin_score += double_score;
            }
        }
    }
}

void TargetLaBaG::GreenFalse()
{
    GreenWei = false;
}

void TargetLaBaG::GreenRandom()
{
    GreenNum = rand() % 100 + 1;
    OneData["GreenWei"] = GreenNum;
}

void TargetLaBaG::JudgeGreen()
{
    if (!GameRunning())
    {
        GreenFalse();
        return;
    }
    // 累積咖波累積數
    for (P p : Ps) {
        if (p.code.compare("A") == 0)
        {
            gss_times += 1;
        }
    }
    GreenRandom();
    string mod = NowMod();
    if (mod.compare("GreenWei") == 0)
    {
        GreenTimes -= 1;

        if (all_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "A";})) // & 表示以引用的方式傳遞參數
        {
            GreenTimes++;
        }
        if (GreenTimes <= 0)
        {
            GreenFalse();
            JudgeSuper();
        }
    }
    else if (mod.compare("Normal") == 0 || mod.compare("PiKaChu") == 0)
    {
        bool all_gss = false;
        if (all_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "A";}))
        {
            all_gss = true;
        }
        if (GreenNum <= GreenRate && all_gss)
        {
            GreenWei = true;
            GreenTimes += 2;
            if (PiKaChu)
            {
                KachuFalse();
            }

        }
        else if (gss_times >= 20)
        {
            GreenWei = true;
            GreenTimes += 2;
            gss_times = 0;
            if (PiKaChu)
            {
                KachuFalse();
            }
        }
    }
}

void TargetLaBaG::KachuFalse()
{
    PiKaChu = false;
}

void TargetLaBaG::JudgeKaChu()
{
    if (!GameRunning() && any_of(begin(Ps), end(Ps), [](const P& p) {return p.code == "E";}))
    {
        PiKaChu = true;
        played -= 5;
        kachu_times++;
        // 關掉其他模式
        SuperFalse();
        GreenFalse();
    }
    else
    {
        KachuFalse();
    }
}
