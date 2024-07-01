#include <iostream>
#include <vector>
#include <string>
#include "../json/include/nlohmann/json.hpp"
#include <map> // Для использования std::map

//g++ -o parsesetup ParseSetup.cpp
//./parsesetup

using json = nlohmann::json;
using namespace std;

int main() {
    // Пример JSON строки
    string jsonString = R"({
        "SetupTimes": {
            "1": {
                "1": 0,
                "2": 36,
                "3": 20,
                "4": 20,
                "5": 10,
                "6": 24,
                "7": 20,
                "8": 10,
                "9": 40,
                "10": 26
            },
            "2": {
                "1": 15,
                "2": 30,
                "3": 10,
                "4": 45,
                "5": 25,
                "6": 35,
                "7": 5,
                "8": 20,
                "9": 50,
                "10": 40
            }
        }
    })";

    // Парсинг JSON строки
    json jsonData = json::parse(jsonString);

    // Контейнер для хранения данных
    vector<vector<int>> m_vvSetupTimes;

    // Обход элементов в разделе "SetupTimes"
    for (auto& entry : jsonData["SetupTimes"].items()) {
        // Используем std::map для сортировки по ключам
        map<int, int> sortedTimes;

        for (auto& timeEntry : entry.value().items()) {
            int key = stoi(timeEntry.key());
            int value = timeEntry.value();
            sortedTimes[key] = value;
        }

        vector<int> setupTimesRow;

        for (auto& [key, value] : sortedTimes) {
            setupTimesRow.push_back(value);
        }

        m_vvSetupTimes.push_back(setupTimesRow);
    }

    // Вывод данных для проверки
    for (const auto& row : m_vvSetupTimes) {
        for (int time : row) {
            cout << time << " ";
        }
        cout << endl;
    }

    return 0;
}