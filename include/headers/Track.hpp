#pragma once
#include <string>
#include <filesystem>
#include <deque>

namespace fs = std::filesystem;
class Track{
public:
    Track();

    bool enqueue(const std::string& song);
    void pushToFront(const std::string& song);
    void dequeue();
    fs::path front() const;
    bool isEmpty() const;
    int size() const;
    void clear();
    void deleteFromQueue(const std::string& song);
    void showQueue() const;
private: 
    std::deque<fs::path> queue;
};