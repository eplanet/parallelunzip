#include "syncqueue.hpp"

SyncQueue::SyncQueue() {
}

void SyncQueue::push(std::string& s) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_queue.find(s) == _queue.end()) {
        _queue.insert(s);
    }
}

bool SyncQueue::pop(std::string& s) {
    std::lock_guard<std::mutex> lock(_mutex);
    std::set<std::string>::iterator it = _queue.begin();
    if (it == _queue.end()) {
        return false;
    } else {
        s = *it;
        _queue.erase(it);
        return true;
    }
}

void SyncQueue::lock() {
    _mutex.lock();
}

void SyncQueue::unlock() {
    _mutex.unlock();
}
