#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include <string>
#include <dirent.h>
#include <stdio.h>

#include "syncqueue.hpp"


void unzip(int id, SyncQueue& queue) {
    std::string fn;
    while(queue.pop(fn)) {
        cout << "[" << id << "] Poping: " << fn << endl;
    }
}

void fillQueue(const char* dirname, SyncQueue& queue) {
    DIR *dir;
    struct dirent *dp;
    char * file_name;
    dir = opendir(dirname);
    while ((dp=readdir(dir)) != NULL) {
        std::string fn = dirname;
        fn.append("/");
        fn.append(dp->d_name);
        queue.push(fn);
        cout << "Pushing: " << fn << endl;
    }
    closedir(dir);
}

int main(int argc, char** argv) {
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " <dir>" << endl;
        return 1;
    }

    SyncQueue queue;
    fillQueue(argv[1], queue);

    const int NB_THREADS = 10;
    std::vector<std::thread> workers;
    for (int i = 0; i < NB_THREADS; i++) {
        workers.push_back(std::thread(unzip, i, std::ref(queue)));
    }

    for (int i = 0; i < NB_THREADS; i++) {
        workers.at(i).join();
    }

    return 0;
}
