#include <iostream>
using namespace std;

struct Node {
    char name[30];
    Node* next;
};

struct CircularList {
    Node* tail = nullptr;   // tail->next = head
    int size = 0;
};

// Thêm người chơi vào cuối danh sách vòng
void addPlayer(CircularList& L, const char* nameInput) {
    Node* p = new Node;
    int i = 0;
    for (; nameInput[i] != '\0' && i < 29; i++) p->name[i] = nameInput[i];
    p->name[i] = '\0';

    if (L.tail == nullptr) {
        p->next = p;            // một node tự trỏ vào chính nó
        L.tail = p;
    } else {
        p->next = L.tail->next; // p trỏ về head
        L.tail->next = p;
        L.tail = p;             // tail mới
    }
    L.size++;
}

// Hiển thị danh sách vòng trên console
void display(const CircularList& L) {
    if (L.tail == nullptr) { cout << "(rong)\n"; return; }
    Node* p = L.tail->next;     // head
    do {
        cout << p->name;
        p = p->next;
        if (p != L.tail->next) cout << " -> ";
    } while (p != L.tail->next);
    cout << " -> (quay ve " << L.tail->next->name << ")\n";
}

// Mô phỏng Josephus: cứ đếm đến người thứ k thì bị loại
void josephus(CircularList& L, int k) {
    if (L.tail == nullptr) return;

    Node* prev = L.tail;        // node đứng trước cur
    Node* cur  = L.tail->next;  // bắt đầu đếm từ head
    int round = 1;

    while (L.size > 1) {
        // đi k-1 bước
        for (int i = 1; i < k; i++) {
            prev = cur;
            cur = cur->next;
        }

        cout << "Vong " << round++ << ": loai " << cur->name << "\n";

        // xóa cur khỏi danh sách vòng
        prev->next = cur->next;
        if (cur == L.tail) L.tail = prev;   // cập nhật tail nếu xóa tail
        Node* del = cur;
        cur = cur->next;                    // bắt đầu đếm lại từ người kế tiếp
        delete del;
        L.size--;

        cout << "   Con lai: ";
        display(L);
    }

    cout << "\n>>> Nguoi may man la: " << L.tail->name << " <<<\n";
}

// Giải phóng bộ nhớ
void clear(CircularList& L) {
    if (L.tail == nullptr) return;
    Node* head = L.tail->next;
    L.tail->next = nullptr;     // phá vòng
    while (head != nullptr) {
        Node* t = head;
        head = head->next;
        delete t;
    }
    L.tail = nullptr;
    L.size = 0;
}

int main() {
    CircularList L;
    int n, k;
    char name[30];

    cout << "Nhap so nguoi choi n: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Nhap ten nguoi thu " << i << ": ";
        cin >> name;
        addPlayer(L, name);
    }

    cout << "Nhap buoc nhay k: ";
    cin >> k;

    cout << "\nDanh sach ban dau:\n";
    display(L);
    cout << "\n";

    josephus(L, k);
    clear(L);
    return 0;
}
