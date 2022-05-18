#include <exception>
#include <fstream>
#include <ios>
#include <map>
#include <mutex>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <thread>
#include <iostream>


std::map<std::string, nlohmann::json> writebuffer;
std::mutex writebufferlock;

std::map<std::string, nlohmann::json> cache;

int quitdb = 0;

void writethreadfunc() {
    std::cout << "writethread called\n";
    while (!quitdb) {
        writebufferlock.lock();
        for(auto item: writebuffer) {
            std::string filename = item.first;
            nlohmann::json jsondata = item.second;
            std::string exportdata = (std::string)jsondata;
            std::ofstream file(std::string("db/") + filename + std::string("/data.json"), std::ios::trunc);

            file << exportdata;
            file.close();

            writebuffer.erase(item.first);
        }
        writebufferlock.unlock();
    }
}

nlohmann::json readentry() {

}

bool updateentry() {

}

bool deleteentry() {
    try {

    } catch (std::exception e) {
        std::cerr << "Something went wrong while deleting an entry from the database!\n"
            << "error: " << e.what();
            return false;
    }
    return true;
}

void readthreadfunc() {
    
}

int main() {
    std::thread writethread(writethreadfunc);
    quitdb = 1;
    while (quitdb) {
        writethread.join();
        exit(0);
    }
    return 0;
}





