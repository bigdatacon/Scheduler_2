#include <iostream>
#include <vector>
#include <fstream>
#include "../json/include/nlohmann/json.hpp"


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

void serialize_operations(const std::vector<std::vector<MSOperation*>>& ms_operations, const std::vector<std::vector<JSOperation*>>& js_operations) {
    nlohmann::json ms_operations_data = nlohmann::json::array();
    nlohmann::json js_operations_data = nlohmann::json::array();

    for (const auto& job_ops : ms_operations) {
        for (const auto& op : job_ops) {
            ms_operations_data.push_back({
                                                 {"Machine", "M" + std::to_string(op->operationIndex)},
                                                 {"Start", op->startTime},
                                                 {"Finish", op->finishTime},
                                                 {"Job", std::to_string(op->jobIndex)}
                                         });
        }
    }

    for (const auto& job_ops : js_operations) {
        for (const auto& op : job_ops) {
            js_operations_data.push_back({
                                                 {"Job", "J" + std::to_string(op->operationIndex)},
                                                 {"Start", op->startTime},
                                                 {"Finish", op->finishTime},
                                                 {"Machine", "M" + std::to_string(op->machineIndex)}
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
//    std::vector<std::vector<MSOperation*>> ms_operations = {
//            {new MSOperation{1, 1, 10, 30}, new MSOperation{1, 2, 40, 70}},
//            {new MSOperation{2, 1, 50, 90}, new MSOperation{2, 2, 100, 140}},
//            {new MSOperation{3, 1, 110, 150}, new MSOperation{3, 2, 160, 200}}
//    };
//
//    std::vector<std::vector<JSOperation*>> js_operations = {
//            {new JSOperation{1, 1, 10, 30}, new JSOperation{1, 2, 40, 70}},
//            {new JSOperation{2, 1, 50, 90}, new JSOperation{2, 2, 100, 140}},
//            {new JSOperation{3, 1, 110, 150}, new JSOperation{3, 2, 160, 200}}
//    };


    std::vector<std::vector<MSOperation*>> ms_operations = {
            {new MSOperation{1, 1, 0, 36}, new MSOperation{1, 5, 144, 166}},
            {new MSOperation{1, 2, 36, 64}, new MSOperation{1, 3, 64, 107}, new MSOperation{1, 4, 107, 144}}
    };

    std::vector<std::vector<JSOperation*>> js_operations = {
            {new JSOperation{1, 1, 0, 36}, new JSOperation{2, 2, 36, 64}, new JSOperation{3, 2, 64, 107}, new JSOperation{4, 2, 107, 144}, new JSOperation{5, 1, 144, 166}}
    };

    serialize_operations(ms_operations, js_operations);

    for (auto& job_ops : ms_operations) {
        for (auto& op : job_ops) {
            delete op;
        }
    }

    for (auto& job_ops : js_operations) {
        for (auto& op : job_ops) {
            delete op;
        }
    }

    return 0;
}
