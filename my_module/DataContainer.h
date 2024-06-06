#pragma once
#include <vector>

struct MSOperation {
    int nJobIndex;
    int nOperationIndex;
    int nStartTime;
    int nFinishTime;
};

class DataContainer {
public:
    void add_2(int index, MSOperation* mo) {
        if (index >= data_2.size()) {
            data_2.resize(index + 1);
        }
        data_2[index].push_back(mo);
    }

    std::vector<MSOperation*> getData_2(int nNum) const {
        return data_2[nNum];
    }

private:
    std::vector<std::vector<MSOperation*>> data_2;
};

class MyClass {
public:
    MyClass(DataContainer* pDataContainer) : m_pDataContainer(pDataContainer) {}

    void Solve() {
        // calculations...
    }

    DataContainer* GetDataContainer() const {
        return m_pDataContainer;
    }

private:
    DataContainer* m_pDataContainer;
};
