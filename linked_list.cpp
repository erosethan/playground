#include <stdio.h>

typedef int Element;

struct Node {
    Node(const Element& _value)
        : next(nullptr), value(_value) {}

    Node* next;
    Element value;
};

struct LinkedList {

    LinkedList() : head(nullptr), tail(nullptr) {}

    bool IsEmpty() const {
        return head == nullptr;
    }

    void Append(const Element& value) {
        Node* node = new Node(value);
        if (IsEmpty()) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    Node* head, *tail;
};

int main() {
    LinkedList list;
    list.Append(1);
    list.Append(2);
    list.Append(3);
    return 0;
}
