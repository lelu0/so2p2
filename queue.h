#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include "customer.h"
#include <condition_variable>
#include <mutex>
#include <thread>

class Queue{
    private:
        
    public:
        Queue(bool &running);
        ~Queue();
        std::condition_variable queueCond[6];
        std::condition_variable operationPointCond;
        std::mutex m_mutex;
        bool running;
        void customer(int id);
        int queueIds[6];
        int operationPointId;
        
    
};
#endif