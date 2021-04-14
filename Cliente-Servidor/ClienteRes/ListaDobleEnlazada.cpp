#include <iostream>

using namespace std;


class Node{
public:
    std::string data;
    Node* next;
    Node* prev;
};

void insert_end(Node** head, std::string new_data)
{
    Node* newNode = new Node();

    Node* last = *head;

    newNode->data = new_data;
    newNode->next = nullptr;

    if (*head == nullptr)
    {
        newNode->prev = nullptr;
        *head = newNode;
        return;
    }
    while(last->next != nullptr)
        last = last->next;
    last->next = newNode;
    newNode->prev = last;
}
void printList(Node* node)
{
    Node* last;
    while (node != nullptr)
    {
        std::cout << node->data << ", ";
        last = node;
        node = node->next;
    }
}