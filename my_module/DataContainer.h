#pragma once
#include <vector>

class DataContainer {
public:
    void add(int number) {
        data.push_back(number);
    }

    std::vector<int> getData() const {
        return data;
    }

private:
    std::vector<int> data;
};
