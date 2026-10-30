#ifndef MENU_H
#define MENU_H

#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "CircularList.h"
#include "Josephus.h"
#include "FileIO.h"

using namespace std;

inline void trim(char* s) {
    int n = (int)strlen(s);
    while (n > 0 && (s[n - 1] == '\r' || s[n - 1] == '\n' || s[n - 1] == ' ')) s[--n] = '\0';
    int start = 0;
    while (s[start] == ' ') start++;
    if (start > 0) memmove(s, s + start, strlen(s + start) + 1);
}

inline bool inputString(const char* msg, char* buf, int size) {
    cout << msg;
    cin.getline(buf, size);
    bool ok = true;
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); buf[0] = '\0'; ok = false; }
    trim(buf);
    return ok;
}

inline int inputInt(const char* msg, int lo, int hi) {
    char buf[50];
    while (true) {
        inputString(msg, buf, 50);
        char* end;
        long x = strtol(buf, &end, 10);
        if (buf[0] != '\0' && *end == '\0' && x >= lo && x <= hi) return (int)x;
        cout << "  Gia tri khong hop le, nhap so tu " << lo << " den " << hi << ".\n";
    }
}

inline void menuAddPlayer(CircularList& L) {
    char name[30];
    if (!inputString("Nhap ten nguoi choi: ", name, 30)) { cout << "Ten qua dai (toi da 29 ky tu)!\n"; return; }
    if (name[0] == '\0') { cout << "Ten khong duoc de trong!\n"; return; }
    if (isDuplicate(L, name)) { cout << "Ten \"" << name << "\" da ton tai!\n"; return; }
    addPlayer(L, name);
    cout << "Da them \"" << name << "\". Tong so nguoi: " << L.size << "\n";
}

inline CircularList copyList(const CircularList& L) {
    CircularList C;
    if (L.tail == NULL) return C;
    Node* p = L.tail->next;
    do {
        addPlayer(C, p->name);
        p = p->next;
    } while (p != L.tail->next);
    return C;
}

inline void menuPlay(const CircularList& L) {
    if (L.size < 1) { 
        cout << "Danh sach trong, can it nhat 1 nguoi de choi!\n"; 
        return; 
    }
    int k = inputInt("Nhap buoc nhay k (loai nguoi thu k): ", 1, 1000000);
    int n0 = L.size;
    CircularList C = copyList(L);
    cout << "\n--- BAT DAU (dem tu nguoi dau tien: " << C.tail->next->name << ") ---\n";
    josephus(C, k);
    if (C.tail != NULL) saveHistory(n0, k, C.tail->name);
    clear(C);
}

// Đưa menuSave và menuLoad lên TRƯỚC runMenu()
inline void menuSave(const CircularList& L) {
    if (L.size < 1) { cout << "Danh sach rong, khong co gi de luu!\n"; return; }
    ofstream f("players.txt");
    if (!f) { cout << "Khong mo duoc file de ghi!\n"; return; }
    savePlayers(L, f);
    cout << "Da luu " << L.size << " nguoi vao players.txt\n";
}

inline void menuLoad(CircularList& L) {
    ifstream f("players.txt");
    if (!f) { cout << "Khong tim thay file players.txt\n"; return; }
    clear(L);
    int c = loadPlayers(L, f);
    cout << "Da doc " << c << " nguoi tu players.txt\n";
}

inline void showMenu() {
    cout << "\n=========== TRO CHOI JOSEPHUS ===========\n"
         << "1. Them nguoi choi\n"
         << "2. Hien thi vong tron\n"
         << "3. Bat dau tro choi\n"
         << "4. Xoa toan bo danh sach\n"
         << "5. Luu file\n"
         << "6. Doc file\n"
         << "0. Thoat\n"
         << "=========================================\n";
}

inline void runMenu() {
    CircularList L;
    int choice;
    do {
        showMenu();
        choice = inputInt("Chon chuc nang: ", 0, 6);
        switch (choice) {
            case 1: menuAddPlayer(L); break;
            case 2: cout << "Vong tron (" << L.size << " nguoi): "; display(L); break;
            case 3: menuPlay(L); break;
            case 4: clear(L); cout << "Da xoa toan bo danh sach.\n"; break;
            case 5: menuSave(L); break;
            case 6: menuLoad(L); break;
            case 0: cout << "Tam biet!\n"; break;
        }
    } while (choice != 0);
    clear(L); 
}

#endif
