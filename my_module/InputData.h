// CMachine.h
#ifndef INPUTDATA_H
#define INPUTDATA_H

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "../json/include/nlohmann/json.hpp"
#include <fstream>


// using json = nlohmann::json;
using json = nlohmann::ordered_json;

class CMachine {
public:
    CMachine();
    CMachine(std::string sName, int nDischarge, int nCost, std::vector<std::string> vOperationsNames);
    ~CMachine();

    std::string GetName() const;
    void SetDischarge(int discharge);
    int GetDischarge() const;
    int GetCost() const;
    const std::vector<std::string>& GetOperationsNames() const;
    void Print() const;
    void SaveToFileTXT(std::ofstream &file) const;

protected:
    std::string m_sName;
    int m_nDischarge;
    int m_nCost;
    std::vector<std::string> m_vOperationsNames;
};


/////////////////////////////////////////////////////////////////////////////
// COperation

class COperation
{
public:
    COperation();
    COperation(int nID, std::string sName, int nDuration, int nDischarge);
    ~COperation();

    int GetID() const;
    std::string GetName() const;
    int GetDuration() const;
    int GetDischarge() const;
    void SetRelevantMachines(const std::vector<CMachine*> &vAllMachines);
    void GetRandPermOfRelevantMachines(std::vector<int>* pMachinesIndexes) const;

    void SaveToFileTXT(std::ofstream &file) const;
    void Print() const;


protected:
    int m_nID;
    std::string m_sName;
    int m_nDuration;
    int m_nDischarge;
    // vector<int> m_vPrevOperations;      // IDs
    std::vector<int> m_vRelevantMachines;    // indexes
};

/////////////////////////////////////////////////////////////////////////////

// CJob

class CJob
{
public:
    CJob();
    CJob(std::string sName, int nDeadline, std::vector<int> vOperationsIDs);
    ~CJob();

    std::string GetName() const;
    void GetOperationsIndexes(const std::vector<COperation*> &vOperations, std::vector<int>* pOperationsIndexes) const;

    void SaveToFileTXT(std::ofstream &file) const;
    void Print() const;

    int GetDeadline() const ;

    std::vector<int>  GetOperationsIDs() const ;


protected:
    std::string m_sName;
    int m_nDeadline;
    std::vector<int> m_vOperationsIDs;
};

#endif