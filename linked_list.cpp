#include <stdio.h>
#include <iostream>
using namespace std;

typedef int Element;
const int PRIME_BASE = 29;
const int MAXTAM = 100000;

void Reverse(string* str){
    int n = (*str).size() - 1;
    for(int i = 0; i < (*str).size() / 2; i++){
        swap( (*str)[i], (*str)[n] );
        n--;
    }
}

string IntToString(int number){
    string new_string = "";
    while(number != 0){
        new_string += char( (number % 10) + '0');
        number /= 10;
    }
    
    Reverse(&new_string);

    return new_string;
}

unsigned int Pow(int value, int power){
    unsigned int new_value = 1;
    for(int i = 0; i < power; i++){
        new_value *= value;
    }
    return new_value;
}

struct HashTable{
    HashTable(int size): size_of(size) { table = new int[size]; Clear(); }

    void Destroy(){
        delete table;
    }

    void Clear(){
        for(int i = 0; i < size_of; i++){
            table[i] = 0;
        }
    }

    int Hash(int value){
        int power = 0;
        unsigned int new_value = 0;
        string value_str = IntToString(value);
        for(int i = value_str.size() - 1; i >= 0; i--){
            new_value += Pow(PRIME_BASE, power) * int(value_str[i]);
            power++;
        }
        return new_value % size_of;
    }

    bool Find(Element value){
        if(table[Hash(value)] == 0) 
            return true;
        return false;
    }

    void InsertElement(Element value){
        table[Hash(value)] += 1;
    }

    int* table;
    int size_of;
};

struct Node {
    Node(const Element& _value)
        : next(nullptr), value(_value) {}

    Node* next;
    Element value;
};

struct LinkedList {
    LinkedList() : size_of(0), head(nullptr), tail(nullptr) {}

    const int Size(){
        return size_of;
    }

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
        size_of++;
    } 
    
    void DeleteElement(Node* pointer){
        Node* to_delete = pointer;
        Node* next_element = pointer->next;

        pointer->value = next_element->value;
        pointer->next = next_element->next;
                
        delete to_delete;
    }

    //Exercise 
    void RemoveDuplicates(){
        HashTable hash_table(MAXTAM);

        Node* last_node = head;
        Node* actual_node = head;
        while(actual_node != nullptr){
            Node* copy = actual_node;
            if(hash_table.Find(actual_node->value)){
                hash_table.InsertElement(actual_node->value);
                actual_node = actual_node->next;
            } else {
                if(actual_node->next == tail){
                    tail = last_node;
                    tail->next = nullptr;
                    break; 
                }
                DeleteElement(actual_node);
            }
            last_node = copy;
        } 
        hash_table.Destroy();
    }

    int size_of;
    Node* head, *tail;
};

int main() {
    LinkedList list;
    list.Append(1);
    list.Append(2);
    list.Append(3);
    list.Append(1);
    list.Append(4);
    list.Append(3);
    list.Append(1);
    list.RemoveDuplicates();
    return 0;
}
