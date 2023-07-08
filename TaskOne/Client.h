#pragma once
#include <algorithm>
#include <vector>

#include "StudentInfo.h"

class Client
{
    
private:

    std::vector<StudentInfo> Data;
    
public:

    void AddNewInfo(const StudentInfo& Info)
    {
        Data.emplace_back(Info);
        std::stable_sort(Data.begin(), Data.end(),
            [](const StudentInfo& lhs, const StudentInfo& rhs)
        {
            return lhs.Progress < rhs.Progress;
        });

        PrintInfo();
    }

private:

    void PrintInfo()
    {
        printf("Show data Updated!! \n");
        
        for (auto& Info : Data)
        {
            printf("Student Info: ID = %d, Name = %s, Age = %d, Progress = %d\n",
                Info.ID, Info.Name.c_str(), Info.Age, Info.Progress);
        }
        printf("Show data ended!! \n");
    }
};
