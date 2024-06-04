#pragma once
#include <vector>

struct MSOperation
{
    int nJobIndex;
    int nOperationIndex;
    int nStartTime;
    int nFinishTime;
};

class DataContainer {
public:
    void add(int number) {
        data.push_back(number);
    }

    void add_2(MSOperation* mo) {
        data_2.push_back(mo);
    }

    std::vector<int> getData() const {
        return data;
    }
    std::vector<MSOperation*> getData_2() const {
        return data_2;
    }


private:
    std::vector<int> data;
    std::vector<MSOperation*> data_2;
};
