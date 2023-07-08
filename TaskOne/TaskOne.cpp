#include <memory>
#include <mutex>

#include "Client.h"
#include "Producer.h"



int GlobalIDCounter = 0;
std::mutex ApplyIdMutex;
std::mutex AddInfoMutex;

void ApplyGlobalIDToInfo(StudentInfo& Info)
{
    ApplyIdMutex.lock();

    Info.ID = GlobalIDCounter++;

    ApplyIdMutex.unlock();
}

void AddNewInfoToClient(Client* client, const StudentInfo& Info)
{
    if(!client)
    {
        printf("Client is null\n");
        return;
    }

    AddInfoMutex.lock();
    client->AddNewInfo(Info);
    AddInfoMutex.unlock();
}

int main(int argc, char* argv[])
{

    printf("Core thread count: %d\n", std::thread::hardware_concurrency());
    
    auto client = std::make_shared<Client>();
    std::vector<Producer> producers(std::thread::hardware_concurrency() - 1, Producer{});

    std::vector<std::thread*> threads;
    for (const auto& producer : producers)
    {
        threads.emplace_back(new std::thread{[&]()
        {
            int counter = 0;
            const int maxCounter = 10;
            while (counter != maxCounter)
            {
                printf("Id Thread %d \t Producer DoWork\n", std::this_thread::get_id());
                auto Info = producer.GenerateInfo();
                ApplyGlobalIDToInfo(Info);
                AddNewInfoToClient(client.get(), Info);
                counter++;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }});
    }


    for (int i = 0; i < 10; i++)
    {
        printf("Id Thread %d \t Main DoWork. Tick number #%d\n", std::this_thread::get_id(), i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    
    for (const auto thread : threads)
    {
        thread->join();
    }
    


    for (auto thread : threads)
    {
        delete thread;
        thread = nullptr;
    }

    printf("Program finished");
    return 0;
}
