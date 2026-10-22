#pragma once
#include <iostream>
using namespace std;

struct Node {
    char name[30];
    Node* next;
};

struct CircularList {
    Node* tail = NULL;  
    int size = 0;
};

void addPlayer(CircularList& L, const char* nameInput) {
    Node* p = new Node;
    int i = 0;
    for (; nameInput[i] != '\0' && i < 29; i++) p->name[i] = nameInput[i];
    p->name[i] = '\0';

    if (L.tail == NULL) {
        p->next = p;           
        L.tail = p;
    } else {
        p->next = L.tail->next; 
        L.tail->next = p;
        L.tail = p;             
    }
    L.size++;
}


void display(const CircularList& L) {
    if (L.tail == NULL) { cout << "(rong)\n"; return; }
    Node* p = L.tail->next;     
    do {
        cout << p->name;
        p = p->next;
        if (p != L.tail->next) cout << " -> ";
    } while (p != L.tail->next);
    cout << " -> (quay ve " << L.tail->next->name << ")\n";
}
void clear(CircularList& L) {
    if (L.tail == NULL) return;
    Node* head = L.tail->next;
    L.tail->next = NULL;     
    while (head !=NULL) {
        Node* t = head;
        head = head->next;
        delete t;
    }
    L.tail = NULL;
    L.size = 0;
}
