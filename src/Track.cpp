#include <iostream>
#include <algorithm>
#include <filesystem>
#include "Track.hpp"
#include "states.hpp"

namespace fs = std::filesystem;
Track::Track() {}

bool Track::enqueue(const std::string& songPath){
    fs::path fullpath = "C:/Wasser/songs/" + songPath;
    if (!std::filesystem::exists(songPath)) { 
        std::cout << "Failed to enqueue: file not found -> " << fullpath << "\n"; 
        return false; 
    } 
    queue.push_back(fullpath);
    state.clearScreen(); 
    std::cout << fullpath.filename().string() << " has been added to the playlist\n" << "\n";
    return true;
}

void Track::dequeue(){
    if (!queue.empty()){
        queue.pop_front();
    }
}

bool Track::isEmpty() const{
    return queue.empty();
}

void Track::pushToFront(const std::string& song){
    queue.push_front(song);
    std::cout << song << " has been added back to the front of the queue\n";  
}

fs::path Track::front() const{
    if(queue.empty()) return {};
    return queue.front();
}

void Track::deleteFromQueue(const std::string& song){
    auto it = std::remove(queue.begin(), queue.end(), song);
    if (it != queue.end()){
        queue.erase(it, queue.end());   
    }
}

void Track::showQueue() const{ 
    if(queue.empty()) {
        std::cout << "Queue is empty\n" << "\n";
        return;
    }

    for (const auto& song : queue){
        std::string name = fs::path(song).filename().string();
        std::cout << name << "\n";  
    }
}

void Track::clear(){    
    queue.clear();
}

int Track::size() const{
    return static_cast<int>(queue.size());
}
