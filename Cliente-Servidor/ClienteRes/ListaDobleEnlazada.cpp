#pragma once
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

void deleteNode(Node** head_ref, Node* del)
{
    if (*head_ref == nullptr || del == nullptr)
        return;
    if (*head_ref == del)
        *head_ref = del->next;
    if (del->next != nullptr)
        del->next->prev = del->prev;
    if (del->prev != nullptr)
        del->prev->next = del->next;

    free(del);
    return;
}

void clearDLList(Node** head_ref)
{
    Node* ptr = *head_ref;
    Node* next;

    while (ptr != nullptr)
    {
        next = ptr->next;
        deleteNode(head_ref, ptr);
        ptr = next;
    }
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