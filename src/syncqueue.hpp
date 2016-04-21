#ifndef __SYNCQUEUE__
#define __SYNCQUEUE__

#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <set>

class SyncQueue {
public:
    SyncQueue();
    void push(std::string& s);
    bool pop(std::string& s);
    
    void lock();
    void unlock();
private:
    std::mutex _mutex;
    std::condition_variable _condition;
    std::set<std::string>   _queue;
};

#endif

