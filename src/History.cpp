#include <iostream>
#include "History.hpp"
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;
History::History() {}

void History::push(const std::string& song){
    history.push_back(song);
    std::cout << "Added the music: " << song;
}

void History::pop(){
    if(history.empty()){
        history.pop_back();
        std::cout << "No song has been played";
        return;
    }
}

void History::delFromStack(const std::string& song){
    auto it = std::remove(history.begin(), history.end(), song);
    if (it != history.end()) {
        history.erase(it, history.end());
    }
}

int History::size() const{
    return static_cast<int>(history.size());  
}

void History::clear() {
    history.clear();  
}

std::string History::top() const{
    if (history.empty()) return "";
    return history.back();  
}

void History::showHistory() const{
    if(history.empty()) {
        std::cout << "History is empty\n";
        return;
    }

    for (const auto& song : history){
        std::string name = fs::path(song).filename().string();
        std::cout << name << "\n";  
    }
}

bool History::isEmpty() {
    return history.empty();
}
