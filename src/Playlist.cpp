#include <iostream>
#include <filesystem>
#include "Playlist.hpp"

namespace fs = std::filesystem;

Playlist::Playlist() : head(nullptr), curr(nullptr), songCount(0) {}

Playlist::~Playlist(){
    if (!head) return;

    Node* temp = head->next;
    while(temp != head){
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    delete head;
    head = nullptr;
    curr = nullptr;
}

void Playlist::addMediaAtLast(const fs::path& songPath){
    Node* newNode = new Node(songPath);

    if(!head){
        head = newNode;
        curr = head;
        head->next = head;
        head->prev = head;
    } else {
        Node* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
    songCount++;
}

void Playlist::nextTrack(){
    if (curr) curr = curr->next;
}

void Playlist::previousTrack(){
    if (curr) curr = curr->prev;
}

void Playlist::showPlaylist() const{
    if(!head){
        std::cout << "Empty Playlist\n";
        return;
    }

    Node* ptr = head;
    do{
        if(ptr == curr) std::cout << "The current song is: ";

        std::string temp = fs::path(ptr->songPath).filename().string();
        std::cout << temp << "\n";
        ptr = ptr->next;
    } while(ptr!=head);
}

bool Playlist::deleteMedia(const std::string& song) {
    if(!head) return false;

    Node* temp = head;
    do {
        if(temp->songPath == song){
            if (temp == head) head = head->next;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            if (curr == temp) curr = temp->next; 
            delete temp;
            return true;
        }
        temp = temp->next;
    } while(temp != head);
    return false;
}

void Playlist::getCurrentSong() const{
    if(!curr){
        std::cout << "No song is playing\n" << "\n";
        return;
    }
    std::string temp = fs::path(curr->songPath).filename().string();
    std::cout << temp << "\n";
    return;
}

int Playlist::numberOfSongs() const{
    if (!head) return 0;
    int count = 0 ;
    Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while(temp != head);
    return count;
}

int Playlist::getSize() const {
    return numberOfSongs();
}
