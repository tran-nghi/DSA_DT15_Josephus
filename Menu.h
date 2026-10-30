#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <cstring>
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
inline void inputString(const char* msg, char* buf, int size) {
    cout << msg;
    cin.getline(buf, size);
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); buf[0] = '\0'; }
    trim(buf);
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
    inputString("Nhap ten nguoi choi: ", name, 30);
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
    CircularList C = copyList(L);
    cout << "\n--- BAT DAU (dem tu nguoi dau tien: " << C.tail->next->name << ") ---\n";
    josephus(C, k);
    clear(C); 
}
inline void showMenu() {
    cout << "\n=========== TRO CHOI JOSEPHUS ===========\n"
         << "1. Them nguoi choi\n"
         << "2. Hien thi vong tron\n"
         << "3. Bat dau tro choi\n"
         << "4. Xoa toan bo danh sach\n"
         << "0. Thoat\n"
         << "=========================================\n";
}
inline void runMenu() {
    CircularList L;
    int choice;
    do {
        showMenu();
        choice = inputInt("Chon chuc nang: ", 0, 4);
        switch (choice) {
            case 1: menuAddPlayer(L); break;
            case 2: cout << "Vong tron (" << L.size << " nguoi): "; display(L); break;
            case 3: menuPlay(L); break;
            case 4: clear(L); cout << "Da xoa toan bo danh sach.\n"; break;
            case 0: cout << "Tam biet!\n"; break;
        }
    } while (choice != 0);
    clear(L); 
}
#endif
