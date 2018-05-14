#include "queue.h"
Queue::Queue(bool &running){
    this->running = running;
    this->operationPointId = -1;
    for(int i = 0; i <= 5; i++){
        this->queueIds[i] = -1;
    }
}

void Queue::customer(int id)
{
    int position = 5;
    while (running)
    {
        std::unique_lock<std::mutex> l(m_mutex);
        if (position >= 0)
        {
            this->queueCond[position].wait(l, [this, position] { return this->queueIds[position] == -1; });
            if (position == 5)
            {
                this->queueIds[position] = id;
                position--;
                l.unlock();
            }
            else
            {
                this->queueIds[position] = id;
                this->queueIds[position+1] = -1;
                l.unlock();
                queueCond[position + 1].notify_one();
                position--;
            }
        }
        else
        {
            this->operationPointCond.wait(l, [this]() { return this->operationPointId == -1; });
            this->operationPointId = id;
            l.unlock();
            // Make This Thread sleep for 3 Second
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            this->operationPointId = -1;
            this->operationPointCond.notify_one();
            position = 5;
        }
    }
}