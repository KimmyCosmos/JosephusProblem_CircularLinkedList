#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    Node* next;
    Node(const string& n) : name(n), next(nullptr) {}
};

int main() {
    int n, k;
    cin >> n >> k;
    cin.ignore();

    // Build list of first n names
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);
        Node* node = new Node(s);
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    tail->next = head; // make it circular

    Node* curr = head;
    Node* prev = tail;

    // Continue until only one person is left
    while (curr != curr->next) {
        // Move (k-1) times to find the person who will vote out the next
        for (int i = 1; i < k; ++i) {
            prev = curr;
            curr = curr->next;
        }
        // curr votes out curr->next (the next person)
        Node* eliminated = curr->next;
        curr->next = eliminated->next;
        // If we're about to eliminate head, update head
        if (eliminated == head) {
            head = eliminated->next;
        }
        delete eliminated;
        curr = curr->next;
    }

    cout << curr->name << " wins!" << endl;
    delete curr;
    return 0;
}