#include "window.h"
#include "config.h"
#include "queue.h"
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <unistd.h>
#include <vector>
Window *window;
AppConfig *config;
Queue *queue;
bool running = true;

void exitListener()
{
    while (running)
    {
        char c = getchar();
        if(c == 'x')
            running = false;
    }
}


void updateWindowFct()
{
    while (running)
    {
        usleep(500);
        window->updateWindow(queue->queueIds,queue->operationPointId);
    }
    delete window;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    window = new Window();
    queue = new Queue(running);    
    //config init
    config = new AppConfig();
    
    //create control threads
    std::thread windowThread(updateWindowFct);    
    std::thread exitThread(exitListener); 
    std::vector<std::thread> threads;
    for(int i = 0; i < 50; i++){
        threads.push_back(std::thread(&Queue::customer, queue, i));
    }   
   
    windowThread.join();
    exitThread.join();
    for (int i = 0; i < 50; i++)
    {
        threads[i].join();
    }
    
    return 0;
    
}