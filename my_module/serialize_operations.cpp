#include <iostream>
#include <vector>
#include <fstream>
//#include <nlohmann/json.hpp>
#include "../json/include/nlohmann/json.hpp"

// как запускать
//g++ -o serialize_operations serialize_operations.cpp
//./serialize_operations


struct MSOperation {
    int jobIndex;
    int operationIndex;
    int startTime;
    int finishTime;
};

struct JSOperation {
    int operationIndex;
    int machineIndex;
    int startTime;
    int finishTime;
};

void serialize_operations(const std::vector<std::vector<MSOperation>>& ms_operations, const std::vector<std::vector<JSOperation>>& js_operations) {
    nlohmann::json ms_operations_data = nlohmann::json::array();
    nlohmann::json js_operations_data = nlohmann::json::array();

    for (const auto& job_ops : ms_operations) {
        for (const auto& op : job_ops) {
            ms_operations_data.push_back({
                                                 {"Machine", "M" + std::to_string(op.operationIndex)},
                                                 {"Start", op.startTime},
                                                 {"Finish", op.finishTime},
                                                 {"Job", std::to_string(op.jobIndex)}
                                         });
        }
    }

    for (const auto& job_ops : js_operations) {
        for (const auto& op : job_ops) {
            js_operations_data.push_back({
                                                 {"Job", "J" + std::to_string(op.operationIndex)},
                                                 {"Start", op.startTime},
                                                 {"Finish", op.finishTime},
                                                 {"Machine", "M" + std::to_string(op.machineIndex)}
                                         });
        }
    }

    nlohmann::json data;
    data["ms_operations"] = ms_operations_data;
    data["js_operations"] = js_operations_data;

    std::ofstream file("operations_data.json");
    file << data.dump(4);
}

int main() {


    std::vector<std::vector<MSOperation>> ms_operations = {
            {{1, 1, 10, 30}, {1, 2, 40, 70}},
            {{2, 1, 50, 90}, {2, 2, 100, 140}},
            {{3, 1, 110, 150}, {3, 2, 160, 200}}
    };

    std::vector<std::vector<JSOperation>> js_operations = {
            {{1, 1, 10, 30}, {1, 4, 40, 70}},
            {{2, 5, 50, 90}, {2, 8, 100, 140}},
            {{3, 5, 110, 150}, {3, 12, 160, 200}}
    };


//    std::vector<std::vector<MSOperation>> ms_operations = {
//            {{1, 1, 10, 30}, {1, 2, 40, 70}},
//            {{2, 3, 50, 90}}
//    };
//
//    std::vector<std::vector<JSOperation>> js_operations = {
//            {{1, 1, 10, 30}, {1, 2, 40, 70}},
//            {{2, 3, 50, 90}}
//    };

    serialize_operations(ms_operations, js_operations);
    return 0;
}
