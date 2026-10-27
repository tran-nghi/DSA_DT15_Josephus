#ifndef JOSEPHUS_H
#define JOSEPHUS_H

#include "CircularList.h"

void josephus(CircularList& L, int k) {
    if (L.tail == NULL || k <= 0) return;

    Node* prev = L.tail;
    Node* cur = L.tail->next;
    int round = 1;

    while (L.size > 1) {
        for (int i = 1; i < k; i++) {
            prev = cur;
            cur = cur->next;
        }

        cout << "Vong " << round++
             << ": loai " << cur->name << "\n";

        prev->next = cur->next;

        if (cur == L.tail) {
            L.tail = prev;
        }

        Node* del = cur;
        cur = cur->next;
        delete del;
        L.size--;

        cout << "   Con lai: ";
        display(L);
    }

    if (L.size == 1) {
        cout << "\n>>> Nguoi may man la: "
             << L.tail->name << " <<<\n";
    }
}

#endif