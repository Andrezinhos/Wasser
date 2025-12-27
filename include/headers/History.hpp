#pragma once
#include <string>
#include <vector>

class History{
public:
    History();

    void push(const std::string& song);
    void pop();
    bool isEmpty();
    int size() const;
    void clear();
    void delFromStack(const std::string& song);
    void showHistory() const;

    std::string top() const;    

private:
    std::vector<std::string> history;
};
