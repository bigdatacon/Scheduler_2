#include <iostream>
#include <vector>
#include <sstream>
#include <nlohmann/json.hpp>
#include "httplib.h"

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

std::string serialize_operations(const std::vector<std::vector<MSOperation*>>& ms_operations, const std::vector<std::vector<JSOperation*>>& js_operations) {
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

    return data.dump(4);
}

int main() {
    httplib::Server svr;

    std::vector<std::vector<MSOperation*>> ms_operations = {
            {new MSOperation{1, 1, 10, 30}, new MSOperation{1, 2, 40, 70}},
            {new MSOperation{2, 1, 50, 90}, new MSOperation{2, 2, 100, 140}},
            {new MSOperation{3, 1, 110, 150}, new MSOperation{3, 2, 160, 200}}
    };

    std::vector<std::vector<JSOperation*>> js_operations = {
            {new JSOperation{1, 1, 10, 30}, new JSOperation{1, 2, 40, 70}},
            {new JSOperation{2, 1, 50, 90}, new JSOperation{2, 2, 100, 140}},
            {new JSOperation{3, 1, 110, 150}, new JSOperation{3, 2, 160, 200}}
    };

    std::string json_data = serialize_operations(ms_operations, js_operations);

//    svr.Get("/operations_data", [&json_data](const httplib::Request&, httplib::Response& res) {
//        res.set_content(json_data, "application/json");
//    });

    svr.Get("/operations_data", [&json_data](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(json_data, "application/json");
    });

    svr.listen("localhost", 8080);
    return 0;
}
