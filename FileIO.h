# pragma once
#include <iostream>
#include "CircularList.h"
using namespace std;

bool realWord(istream& in, char* buf){
	char c;
	while (in.get(c)&&(c==' '||c=='\n'||c=='\t'||c=='\r')){}
	if (!n) return false;
	int i=0;
	do{
		if (i<29) buf[i++]=c;
	} while (in.get(c)&&c!=' '&&c!='\n'&&c!='\t'&&c!='\r');
	buf[i] ='\0';
	return true;
	}
int loadPlayers(CircularList& L, istream& in, int n){
	char name[30];
	int count = 0;
	while (count < n&& realWord(in, name)){
		addPlayer(L, name);
		count++;
	}
	return count;
}
void savePlayers(const CircularList& L, ostream& out){
	if (L.tail == nullptr) reutrn;
	Node* p=L.tail->next;
	do{
		out<< p->name <<"\n";
	} while (p!= L.tail->next);
}
void saveResult(const CircularList& L, ostream& out){
	if (L.tail == nullptr) return;
	out<< "Nguoi may man: "<< L.tail->name<<"\n";
}
