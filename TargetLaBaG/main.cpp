#include <iostream>
#include <fstream> // 讀寫文件
#include <string>
#include <cmath>
#include <iomanip>
#include <nlohmann/json.hpp>  // 引入 JSON 庫
#include "TargetLaBaG.h"
using namespace std;
using json = nlohmann::json;


int main()
{
    srand(time(NULL));
    int Target;
    TargetLaBaG Game;
    cout << "請輸入目標分數: ";
    cin >> Target;
    cout << endl;

    int i = 0;
    int recent_max = 0;

    while (true)
    {
        i++;
        int LOG = (i < 10) ? 2 : static_cast<int>(log10(i)) + 2;

        Game.GameLogic();

        cout << "第" << setw(LOG) << i << "次 分數: " << setw(8) << Game.score << "【目前最大值: " << recent_max << " 】" << endl;
        if (Game.score > recent_max) {
            recent_max = Game.score;
        }
        if (Game.score >= Target) { // 檢查是否達到目標
            break; // 如果達到目標，則退出迴圈
        }

    }

    try {
        ofstream file(to_string(Game.score) + ".json");  // output file 使用 Game.score 作為文件名
        if (file.is_open()) {
            json j = Game.AllData;  // 轉換 map 為 json
            file << j.dump(4);  // 使用縮排格式 (4 個空格)
            file.close();
            cout << "數據已保存到 " << to_string(Game.score) + ".json" << endl;
        }
        else {
            cerr << "無法打開文件來寫入數據。" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "發生錯誤: " << e.what() << endl;
    }

    return 0;
}