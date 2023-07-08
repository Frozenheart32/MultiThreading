#pragma once
#include <random>

#include "Client.h"
#include "StudentInfo.h"


class Producer
{
public:

    const std::vector<std::string> Names{"Alex", "Dima", "Lisa", "Oleg", "Masha", "Vlad", "Nikolay"};


    StudentInfo GenerateInfo() const
    {
        return StudentInfo{0, GenerateName(), GenerateAge(), GenerateProgress()};
    }

private:

    int GenerateAge() const
    {
        int minAge = 18;
        int maxAge = 100;
        
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(minAge, maxAge);
        
        return static_cast<int>(dist6(rng));
    }

    
    int GenerateProgress() const
    {
        int minProgress = 0;
        int maxProgress = 10;
        
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(minProgress, maxProgress);
        
        return static_cast<int>(dist6(rng));
    }

    
    std::string GenerateName() const
    {
        const int size = Names.size();
        
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, size - 1);
        
        std::string name;
        name.append(Names[dist6(rng)]);

        std::random_device dev2;
        std::mt19937 rng2(dev2());
        std::uniform_int_distribution<std::mt19937::result_type> dist61(0, 999);
        name.append("_");
        name.append(std::to_string(dist61(rng2)));
        
        return name;
    }
    
};
