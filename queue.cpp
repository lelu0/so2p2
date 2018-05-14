#include "queue.h"
using namespace std::chrono_literals;
Queue::Queue(bool &running)
{
    this->running = running;
    this->operationPointId = -1;
    for (int i = 0; i <= 5; i++)
    {
        this->queueIds[i] = -1;
    }
}



void Queue::customer(int id)
{
     int position = id > 5 ? 5 : id;
    //int position = 5;
    while (running)
    {
        std::unique_lock<std::mutex> l(m_mutex);
        if (position >= 0)
        {
            this->queueCond[position].wait_for(l,22500ms, [this, position] { return this->queueIds[position] == -1; });
            if (position == 5)
            {
                this->queueIds[position] = id;
                position--; 
                l.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
            else
            {
                this->queueIds[position] = id;
                this->queueIds[position + 1] = -1;
                l.unlock();
                queueCond[position + 1].notify_one();
                position--;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else
        {
            this->operationPointCond.wait_for(l,22000ms, [this]() { return this->operationPointId == -1; });
            this->operationPointId = id;
            this->queueIds[0] = -1;
            // Make This Thread sleep for 2 Second
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            this->operationPointId = -1;
            l.unlock();
            this->operationPointCond.notify_one();
            position = 5;
        }
    }
}