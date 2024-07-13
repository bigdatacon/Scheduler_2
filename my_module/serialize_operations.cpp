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


// Функция для сериализации данных операций
void serialize_operations(const std::vector<std::vector<MSOperation*>>& ms_operations, const std::vector<std::vector<JSOperation*>>& js_operations) {
    nlohmann::json ms_operations_data = nlohmann::json::array();
    nlohmann::json js_operations_data = nlohmann::json::array();

    // Сериализация данных для ms_operations
    for (int i = 0; i <  ms_operations.size(); ++ i) {
        for (const auto& op : ms_operations[i]) {
            ms_operations_data.push_back({
                                                 {"Job", op->jobIndex},
                                                 {"Machine", i+1},
                                                 {"Start", op->startTime},
                                                 {"Finish", op->finishTime}
                                         });
        }
    }


    // Сериализация данных для js_operations
    for (int i = 0; i < js_operations.size(); ++i) {
        for (const auto& op : js_operations[i]) {
            js_operations_data.push_back({
                                                 {"Job", i+1},
                                                 {"Machine", op->machineIndex},
                                                 {"Start", op->startTime},
                                                 {"Finish", op->finishTime}
                                         });
        }
    }

    // Создание общего JSON объекта
    nlohmann::json data;
    data["ms_operations"] = ms_operations_data;
    data["js_operations"] = js_operations_data;

    // Запись JSON данных в файл
    std::ofstream file("operations_data.json");
    if (file.is_open()) {
        file << data.dump(4); // Форматированный вывод JSON
        file.close();
    } else {
        std::cerr << "Не удалось открыть файл для записи" << std::endl;
    }
}


int main() {

//    std::vector<std::vector<MSOperation*>> ms_operations = {
//            {new MSOperation{0, 1, 71, 102}, new MSOperation{0, 1, 169, 204}},
//            {new MSOperation{0, 2, 102, 129}, new MSOperation{0, 2, 129, 169}},
//            {new MSOperation{2, 4, 0, 38}, new MSOperation{0, 4, 38, 71}, new MSOperation{1, 4, 71, 109}, new MSOperation{2, 4, 109, 173}},
//            {new MSOperation{2, 5, 65, 107}},
//            {new MSOperation{1, 6, 14, 35}, new MSOperation{2, 6, 38, 65}, new MSOperation{2, 6, 227, 254}},
//            {new MSOperation{1, 7, 0, 14}},
//            {new MSOperation{1, 8, 109, 150}, new MSOperation{2, 8, 173, 227}}
//    };
//
//    std::vector<std::vector<JSOperation*>> js_operations = {
//            {new JSOperation{1, 3, 38, 71}, new JSOperation{1, 0, 71, 102}, new JSOperation{1, 1, 102, 129}, new JSOperation{1, 1, 129, 169}, new JSOperation{1, 0, 169, 204}},
//            {new JSOperation{2, 6, 0, 14}, new JSOperation{2, 5, 14, 35}, new JSOperation{2, 3, 71, 109}, new JSOperation{2, 7, 109, 150}},
//            {new JSOperation{3, 3, 0, 38}, new JSOperation{3, 5, 38, 65}, new JSOperation{3, 4, 65, 107}, new JSOperation{3, 3, 109, 173}, new JSOperation{3, 7, 173, 227}, new JSOperation{3, 5, 227, 254}}
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
