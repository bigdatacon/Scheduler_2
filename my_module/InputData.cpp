// CMachine.cpp
#include "InputData.h"
#include <iostream>
#include <algorithm> // Для std::random_shuffle
#include <random> // Для std::default_random_engine

CMachine::CMachine() : m_nDischarge(0), m_nCost(0) {}

CMachine::CMachine(std::string sName, int nDischarge, int nCost, std::vector<std::string> vOperationsNames)
        : m_sName(sName), m_nDischarge(nDischarge), m_nCost(nCost), m_vOperationsNames(vOperationsNames) {}

CMachine::~CMachine() {}

std::string CMachine::GetName() const {
    return m_sName;
}

void CMachine::SetDischarge(int discharge) {
    this->m_nDischarge= discharge;
}

int CMachine::GetDischarge() const {
    return m_nDischarge;
}

int CMachine::GetCost() const {
    return m_nCost;
}

const std::vector<std::string>& CMachine::GetOperationsNames() const {
    return m_vOperationsNames;
}

void CMachine::Print() const {
    std::cout << "Name: " << m_sName << std::endl;
    std::cout << "Discharge: " << m_nDischarge << std::endl;
    std::cout << "Cost: " << m_nCost << std::endl;
    std::cout << "Operations: ";
    for (const auto& operation : m_vOperationsNames) {
        std::cout << operation << " ";
    }
    std::cout << std::endl;
}

/////////////////////////OPERATION
COperation::COperation() : m_nID(0), m_nDuration(0), m_nDischarge(0) {}

COperation::COperation(int nID, std::string sName, int nDuration, int nDischarge)
        : m_nID(nID), m_sName(sName), m_nDuration(nDuration), m_nDischarge(nDischarge) {}

COperation::~COperation() {}

int COperation::GetID() const { return m_nID; }
std::string COperation::GetName() const { return m_sName; }
int COperation::GetDuration() const { return m_nDuration; }
int COperation::GetDischarge() const { return m_nDischarge; }

void COperation::SetRelevantMachines(const std::vector<CMachine*>& vAllMachines) {
    // Этот метод предполагает, что вы уже как-то определили, какие машины релевантны
    m_vRelevantMachines.clear();
    for (size_t i = 0; i < vAllMachines.size(); ++i) {
        if (vAllMachines[i]->GetDischarge() == this->m_nDischarge) {
            m_vRelevantMachines.push_back(i);
        }
    }
}

void COperation::GetRandPermOfRelevantMachines(std::vector<int>* pMachinesIndexes) const {
    // if (!pMachinesIndexes) return; // Добавьте проверку на nullptr для безопасности
    // *pMachinesIndexes = m_vRelevantMachines; // Копирование списка через разыменование указателя
    // std::random_device rd; // Получение случайного зерна
    // std::mt19937 g(rd()); // Генератор
    // std::shuffle(pMachinesIndexes->begin(), pMachinesIndexes->end(), g); // Перемешивание
}


void COperation::SaveToFileTXT(std::ofstream &file) const {
    file << "Operation ID: " << m_nID << ", Name: " << m_sName
         << ", Duration: " << m_nDuration << ", Discharge: " << m_nDischarge << std::endl;
}

void COperation::Print() const {
    std::cout << "Operation ID: " << m_nID << std::endl;
    std::cout << "Name: " << m_sName << std::endl;
    std::cout << "Duration: " << m_nDuration << " minutes" << std::endl;
    std::cout << "Discharge: " << m_nDischarge << std::endl;
    std::cout << "Relevant Machines: ";
    for (const auto& machineIndex : m_vRelevantMachines) {
        std::cout << machineIndex << " ";
    }
    std::cout << std::endl;
}


/////////////////////////////////////////JOBS/////////////////////
CJob::CJob() : m_nDeadline(0) {}

CJob::CJob(std::string sName, int nDeadline, std::vector<int> vOperationsIDs)
        : m_sName(sName), m_nDeadline(nDeadline), m_vOperationsIDs(vOperationsIDs) {}

CJob::~CJob() {}

std::string CJob::GetName() const {
    return m_sName;
}

void CJob::GetOperationsIndexes(const std::vector<COperation*> &vOperations, std::vector<int>* pOperationsIndexes) const {
    if (pOperationsIndexes != nullptr) {
        pOperationsIndexes->clear();
        for (int opId : m_vOperationsIDs) {
            auto it = std::find_if(vOperations.begin(), vOperations.end(),
                                   [opId](COperation* op) { return op->GetID() == opId; });
            if (it != vOperations.end()) {
                pOperationsIndexes->push_back(std::distance(vOperations.begin(), it));
            }
        }
    }
}

void CJob::SaveToFileTXT(std::ofstream &file) const {
    file << "Job Name: " << m_sName << ", Deadline: " << m_nDeadline << ", Operations IDs: ";
    for (auto id : m_vOperationsIDs) {
        file << id << " ";
    }
    file << std::endl;
}

void CJob::Print() const {
    std::cout << "Job Name: " << m_sName << "\nDeadline: " << m_nDeadline << "\nOperations IDs: ";
    for (int id : m_vOperationsIDs) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
}

int CJob::GetDeadline() const {
    return m_nDeadline;
}

std::vector<int> CJob::GetOperationsIDs() const {
    return m_vOperationsIDs;
}