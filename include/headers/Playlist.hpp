#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

struct Node{
    fs::path songPath;
    Node* next;
    Node* prev;

    Node(const fs::path& path) : songPath(path), next(nullptr), prev(nullptr) {}
};

class Playlist{
public:
    Playlist();
    ~Playlist();

    void addMediaAtLast(const fs::path& path);
    bool deleteMedia(const std::string& song); 
    void nextTrack(); 
    void previousTrack();
    void showPlaylist() const;
    void getCurrentSong() const; 
    int numberOfSongs() const;
    int getSize() const; 

    Node* head;
    Node* curr;
    int songCount = 0; 
};
