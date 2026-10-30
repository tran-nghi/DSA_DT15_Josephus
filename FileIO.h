# pragma once
#include <iostream>
#include "CircularList.h"
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

bool realWord(istream& in, char* buf){
	char c;
	while (in.get(c) && isspace(static_cast<unsigned char>(c))) {}
	if (!in) return false;
	int i=0;
	do{
		if (i<29) buf[i++]=c;
	} while (in.get(c)&&c!=' '&&c!='\n'&&c!='\t'&&c!='\r');
	buf[i] ='\0';
	return true;
	}
int loadPlayers(CircularList& L, istream& in) {
    char line[64];
    int count = 0;
    while (in.getline(line, sizeof(line))) {
        int n = (int)strlen(line);
        while (n > 0 && (line[n - 1] == '\r' || line[n - 1] == ' ')) line[--n] = '\0';
        if (line[0] == '\0' || isDuplicate(L, line)) continue;
        addPlayer(L, line);
        count++;
    }
    return count;
}

void saveHistory(int n, int k, const char* winner) {
    ofstream f("history.csv", ios::app);
    if (!f) return;
    f << n << "," << k << "," << winner << "\n";
}
void savePlayers(const CircularList& L, ostream& out){
	if (L.tail == nullptr) return;
	Node* p=L.tail->next;
	do{
		out<< p->name <<"\n";
		p = p->next;
	} while (p!= L.tail->next);
}
void saveResult(const CircularList& L, ostream& out){
	if (L.tail == nullptr) return;
	out<< "Nguoi may man: "<< L.tail->name<<"\n";
}
